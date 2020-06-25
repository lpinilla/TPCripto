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

void lsb_1(); //extraer con lsb1
void lsb_4(); //extraer con lsb4
void ladoLSB4aes256ofb(); //estraer con aes256 ofb
void lsb_i(); //extraer con lsbi

int main()
{

    create_suite("Extract ejemplos prueba test");
    add_test(lsb_1);
    add_test(lsb_4);
    add_test(ladoLSB4aes256ofb);
    add_test(lsb_i);
    run_suite();
    clear_suite();
}

void lsb_1(){
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    if(p != NULL){
        char * path = "tests_output/lsb1_extract_test";
        size_t file_name_size = (strlen(path) + 6) * sizeof(char);
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *)&p->content[p->size]);
        //printf("#%s# \n", file_name);
        FILE *f = fopen(file_name, "w");
        //printf("Extensión: $%s$ \n", &p->content[p->size]);
        //FILE *f = fopen("tests_output/lsb1_extract_test.png", "w");
        if (f == NULL){
            printf("Could not create file!\n");
            return;
        }
        fwrite(p->content, sizeof(uint8_t), p->size, f);
        fclose(f);
        free(file_name);
        destroy_payload(p);
    }
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(1 == 1);
}

void lsb_4()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
    if(p != NULL){
        char * path = "tests_output/lsb4_extract_test";
        size_t file_name_size = strlen(path) + 5;
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *) &p->content[p->size]);
        FILE *f = fopen(file_name, "w");
        if (f == NULL)
        {
            printf("Could not create file!\n");
            return;
        }
        fwrite(p->content, sizeof(uint8_t), p->size, f);
        fclose(f);
        free(file_name);
        destroy_payload(p);
    }
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(1 == 1);
}

void ladoLSB4aes256ofb()
{

    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4aes256ofb.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
    if(p != NULL){
        uint8_t *plaintext = malloc(p->size);
        int d=decrypt(plaintext,"secreto",p->content, p->size, ofb, aes256);
        char * path = "tests_output/ladoLSB4aes256ofb_extract_test";
        size_t file_name_size = strlen(path) + 5;
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *) plaintext +d -T - 1);
        FILE *f = fopen(file_name, "w");
        //printf("Extensión: $%s$ \n", plaintext + d - T - 1);
        //FILE *f = fopen("tests_output/ladoLSB4aes256ofb_extract_test.png", "w");
        if (f == NULL){
            printf("Could not create file!\n");
            return;
        }
        //muy importante el +4 para saltear el tamanio de lo encriptado, el -4 para descontar el tamanio y -5 para extension
        fwrite(plaintext + 4, sizeof(uint8_t), d - T, f);
        fclose(f);
        destroy_payload(p);
        free(file_name);
    }
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(1 == 1);
}

void lsb_i()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSBI_corregido.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    payload p = extract_payload_lsbi(c);
    if(p != NULL){
        char * path = "tests_output/lsbi_extract_test";
        size_t file_name_size = strlen(path) + 5;
        char * file_name = malloc(file_name_size * sizeof(char));
        memset(file_name, 0, file_name_size);
        file_name = strcat(file_name, path);
        file_name = strcat(file_name, (char *) &p->content[p->size]);
        //printf("Extensión: $%s$ \n", p->content + p->size);
        //printf("%s \n", file_name);
        FILE *f = fopen(file_name, "w");
        if (f == NULL){
            printf("Could not create file!\n");
            return;
        }
        //escribo el plaintext en el file, sin el tamanio inicial ni la extension al final
        fwrite(p->content, sizeof(uint8_t), p->size + 4, f);
        fclose(f);
        free(file_name);
        destroy_payload(p);
    }
    destroy_carrier(c);
    assert_true(1 == 1);
}
