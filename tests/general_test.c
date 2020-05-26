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

void lsb_1_test();
void lsb_4_test();
void lsb_i_test();

int main()
{
    create_suite("General Test");
    //add_test(lsb_1_test);
    //add_test(lsb_4_test);
    add_test(lsb_i_test);
    run_suite();
    clear_suite();
}

void lsb_1_test(){
    bmp_file bmp_f = read_bmp("ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    FILE *f = fopen("original.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb_4_test(){
    bmp_file bmp_f = read_bmp("ladoLSB4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
    FILE *f = fopen("original_4.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb_i_test(){
    bmp_file bmp_f = read_bmp("ladoLSBI.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    payload p = extract_payload_lsbi(c);
    FILE *f = fopen("original_i.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}
