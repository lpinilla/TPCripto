#include <bmp_header.h>
#include <carrier.h>
#include <encrypt.h>
#include <hidden_file.h>
#include <jobs.h>
#include <lsb.h>
#include <payload.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <rc4.h>

#define T 4 //tamanio del archivo
#define E 5 //tamanio de la exxtension (.png\0)

void roma_test();
void lsb4_test();
void lsbi_test(); //con la imagen budapest

int main(){
    create_suite("Ejemplos Definitivos");
    add_test(roma_test);
    add_test(lsb4_test);
    add_test(lsbi_test);
    run_suite();
    clear_suite();
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
        FILE *f = fopen("tests_output/roma_extracted.png", "w");
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
        FILE *f = fopen("tests_output/hugo4_extracted.pdf", "w+"); //TODO: no hardcodear la extensión
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
    uint8_t *key = malloc(RC4_N); //48bits necesarios para la key
    payload p = extract_payload_lsbi(c, key);
    if(p != NULL){
        FILE *f = fopen("tests_output/budapest_extracted.png", "w+");
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
