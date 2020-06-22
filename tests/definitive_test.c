#include <bmp_header.h>
#include <carrier.h>
#include <encrypt.h>
#include <hidden_file.h>
#include <jobs.h>
#include <lsb.h>
#include <operations.h>
#include <options.h>
#include <payload.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <utils.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <rc4.h>

#define T 4 //tamanio del archivo
#define E 5 //tamanio de la exxtension (.png\0)

void roma_test();
void lsb4_test();
void lsbi_test(); //con la imagen budapest
void simple_inyect_extract_test();
void embed_modifies_file_test();

int main(){
    create_suite("Ejemplos Definitivos");
    // add_test(roma_test);
    // add_test(lsb4_test);
    // add_test(lsbi_test);
    // add_test(embed_modifies_file_test);
    add_test(simple_inyect_extract_test);
    run_suite();
    clear_suite();
}

void embed_modifies_file_test() {
    struct options embed_options;
    
    embed_options.operation = embed;
    strcpy(embed_options.in, "files_for_testing/lsb1_test.png");
    strcpy(embed_options.p, "files_for_testing/sample.bmp");
    strcpy(embed_options.out, "tests_input/sample_inyectado2.bmp");
    embed_options.stego_type = lsb1;
    embed_options.encrypted = false;

    _embed(&embed_options);
    assert_false(filesEqual("files_for_testing/sample.bmp", "tests_input/sample_inyectado2.bmp"));
}

void simple_inyect_extract_test() {
    struct options embed_options;
    struct options extract_options;

    embed_options.operation = embed;
    strcpy(embed_options.in, "tests_input/gladiator_chicken.png");
    strcpy(embed_options.p, "files_for_testing/sample.bmp");
    strcpy(embed_options.out, "tests_output/sample_inyectado2.bmp");
    embed_options.stego_type = lsb1;
    embed_options.encrypted = true;
    embed_options.encription_mode = cbc;
    embed_options.encription_algorithm = aes256;
    strcpy(embed_options.encription_password, "password");

// p size = 236704840
// c size = 3275520

//p size = 181824
//c size = 3275520
    extract_options.operation = extract;
    strcpy(extract_options.p, "tests_output/sample_inyectado2.bmp");
    strcpy(extract_options.out, "tests_output/sample_extraido.png");
    extract_options.stego_type = lsb1;
    extract_options.encrypted = true;
    extract_options.encription_mode = cbc;
    extract_options.encription_algorithm = aes256;
    strcpy(extract_options.encription_password, "password");

    _embed(&embed_options);
    _extract(&extract_options);
    assert_true(filesEqual("tests_input/sample_extraido.png", "tests_input/gladiator_chicken.png"));

}

//analizando roma con lsb1 obtuvimos un buscaminas (extract_roma.png)
//ese buscaminas tenia un .zip con soltxt5 que nos decia el modo y el alogritmo para desencriptar otro archivo
//en strings back.bmp estaba la pass "camuflado"

void roma_test(){
    bmp_file bmp_f = read_bmp("archivos_finales/roma.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    if(p != NULL){
        char * path = "tests_output/roma_extracted";
        size_t file_name_size = (strlen(path) + 6) * sizeof(char);
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *)&p->content[p->size]);
        FILE *f = fopen(file_name, "w");
        if (f == NULL)
        {
            printf("Could not create file!\n");
            return;
        }
        fwrite(p->content, sizeof(uint8_t), p->size, f);
        fclose(f);
        destroy_payload(p);
    }
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(1 == 1);
}

void lsb4_test(){
    bmp_file bmp_f = read_bmp("archivos_finales/hugo4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
    if(p != NULL){
        uint8_t *plaintext = malloc(p->size);
        int d = decrypt(plaintext, "camuflado", p->content, p->size, cfb, des);
        char * path = "tests_output/hugo4_extracted";
        size_t file_name_size = strlen(path) + 5;
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *) plaintext +d -T - 1);
        FILE *f = fopen(file_name, "w");
        if (f == NULL){
            printf("Could not create file!\n");
            return;
        }
        fwrite(plaintext+4, sizeof(uint8_t), d, f);
        fclose(f);
        destroy_payload(p);
    }
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(1 == 1);
}

void lsbi_test(void){
    bmp_file bmp_f = read_bmp("archivos_finales/budapest.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    payload p = extract_payload_lsbi(c);
    if(p != NULL){
        char * path = "tests_output/budapest_extracted";
        size_t file_name_size = strlen(path) + 5;
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *) &p->content[p->size]);
        FILE *f = fopen(file_name, "w");
        if (f == NULL){
            printf("Could not create file!\n");
            return;
        }
        //escribo el plaintext en el file, sin el tamanio inicial ni la extension al final
        fwrite(p->content, sizeof(uint8_t), p->size, f);
        fclose(f);
        destroy_payload(p);
    }
    destroy_carrier(c);
    assert_true(1 == 1);
}
