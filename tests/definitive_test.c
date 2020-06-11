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

void roma_test();
void lsb4_test();



int main(){
    create_suite("Ejemplos Definitivos");
    add_test(roma_test);
    //add_test(lsb4_test);


    run_suite();
    clear_suite();
    //bmp_file bmp_f = read_bmp("../../definitivos/roma.bmp");
    // bmp_file bmp_f = read_bmp("lsb1_unsteg.png");
    // bmp_header bmp_h = bmp_f->header;
    // carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    // lsb l = create_lsb(4);
    // payload p = extract_payload(l, c);
    // FILE *f = fopen("test.txt", "w");
    // fwrite(p->content, sizeof(uint8_t), p->size, f);
    // fclose(f);
    // destroy_lsb(l);
    // destroy_carrier(c);
    // destroy_payload(p);
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
    //  payload_ext(p);

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
   
    FILE *f = fopen("lsb4_test.png", "w");
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
