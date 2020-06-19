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
void lsb_enchanced_check();

int main(){
    create_suite("Ejemplos Definitivos");
    //add_test(roma_test);
    //add_test(lsb4_test);
    add_test(lsbi_test);
    //add_test(lsb_enchanced_check);
    run_suite();
    clear_suite();
}

//analizando roma con lsb1 obtuvimos un buscaminas (extract_roma.png)
//ese buscaminas tenia un .zip con soltxt5 que nos decia el modo y el alogritmo para desencriptar otro archivo
//en strings back.bmp estaba la pass "camuflado"

void roma_test(){
    bmp_file bmp_f = read_bmp("roma.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    FILE *f = fopen("roma_inside/extract_roma.png", "w");
    if (f == NULL)
    {
        printf("Could not create file!\n");
        return;
    }
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb4_test(){
    bmp_file bmp_f = read_bmp("hugo4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    printf("hugo %d %d %d %d\n",bmp_h->size,bmp_h->bits_per_pixel,bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);

    uint8_t *plaintext = malloc(p->size);
    int d = decrypt(plaintext, "camuflado", p->content, p->size, cfb, des);
    FILE *f = fopen("lsb4/magia", "w+");
    if (f == NULL){
        printf("Could not create file!\n");
        return;
    }
    fwrite(plaintext+4, sizeof(uint8_t), d, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);

}

void lsbi_test(void){
    bmp_file bmp_f = read_bmp("budapest.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    uint8_t *key = malloc(RC4_N); //48bits necesarios para la key
    payload p = extract_payload_lsbi(c, key);
    FILE *f = fopen("lsbi/testing", "w+");
    if (f == NULL){
        printf("Could not create file!\n");
        return;
    }
    //escribo el plaintext en el file, sin el tamanio inicial ni la extension al final
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb_enchanced_check(){
    bmp_file bmp_f = read_bmp("back.bmp");
    bmp_header bmp_h = bmp_f->header;
    long size = bmp_h->image_size_bytes;
    carrier c = create_carrier(bmp_f->data, size, bmp_h->width_px, bmp_h->height_px);
    for(int i = 0; i < size; i++){
        bmp_f->data[i] &= 0x01;
        bmp_f->data[i] = bmp_f->data[i] << 7;
    }
    FILE *f = fopen("back_inside/enhancing_lsb", "w");
    if (f == NULL)
    {
        printf("Could not create file!\n");
        return;
    }
    fwrite(bmp_h, sizeof(uint8_t), 54, f);
    fwrite(bmp_f->data, sizeof(uint8_t), size, f);
    fclose(f);
    destroy_carrier(c);
    assert_true(1 == 1);
}
