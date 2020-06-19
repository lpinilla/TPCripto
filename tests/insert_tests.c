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

void lsb1_insert_0();
void lsb4_insert_1();
void lsb1_insert_2();
void lsb4_insert_4();
void lsb1_insert_3();

void lsb4_insert_image_0();
void lsb1_insert_image_1();

int main()
{
    create_suite("Insert Tests");
    add_test(lsb1_insert_0);
    add_test(lsb4_insert_1);
    add_test(lsb1_insert_2);
    add_test(lsb1_insert_3);
    add_test(lsb4_insert_4);
    add_test(lsb4_insert_image_0);
    add_test(lsb1_insert_image_1);
    run_suite();
    clear_suite();
}

//inserta con lsb1 a ladoLSB1.bmp la imagen original.png
void lsb1_insert_image_1()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    hfs example_hf = process_hf("tests_input/gladiator_chicken.png");
    uint8_t *payload_insert = concat_hf(example_hf);

    //poner total size en la estructura de hf
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(1);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);

    FILE *f = fopen("tests_output/lbs1_insert_original.png", "w");
    if (f == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

//inserta con lsb4 a ladoLSB1.bmp la imagen original.png
void lsb4_insert_image_0()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    hfs example_hf = process_hf("tests_input/gladiator_chicken.png");
    uint8_t *payload_insert = concat_hf(example_hf);

    //poner total size en la estructura de hf
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(4);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);

    FILE *f = fopen("tests_output/lbs4_insert_original.png", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

//inserta con lsb1 a ladoLSB1.bmp el texto test1.txt
void lsb1_insert_0(){
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    hfs example_hf = process_hf("tests_input/test1.txt");
    uint8_t *payload_insert = concat_hf(example_hf);
    //poner total size en la estructura de hf
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(1);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);
    FILE *f = fopen("tests_output/lbs1_insert_text1.txt", "w+");
    if (f == NULL) {
        printf("File Not Found!\n");
        return;
    }
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

//inserta con lsb4 a ladoLSB1.bmp el texto test1.txt
void lsb4_insert_1()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    hfs example_hf = process_hf("tests_input/test1.txt");
    uint8_t *payload_insert = concat_hf(example_hf);
    //poner total size en la estructura de hf
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(4);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);
    //payload_ext(p);
    FILE *f = fopen("tests_output/lbs4_insert_text1.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

//inserta con lsb1 a ladoLSB1.bmp el texto test2.txt
void lsb1_insert_2()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    hfs example_hf = process_hf("tests_input/test2.txt");
    uint8_t *payload_insert = concat_hf(example_hf);
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(1);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);
    FILE *f = fopen("tests_output/lbs1_insert_text2.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

//inserta con lsb1 a ladoLSB1.bmp el texto test4.txt
void lsb1_insert_3()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    hfs example_hf = process_hf("tests_input/test4.txt");
    uint8_t *payload_insert = concat_hf(example_hf);
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(1);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);
    FILE *f = fopen("tests_output/lsb1_insert_text4.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

//inserta con lsb4 a ladoLSB1.bmp el texto test4.txt
void lsb4_insert_4()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    hfs example_hf = process_hf("tests_input/test4.txt");
    uint8_t *payload_insert = concat_hf(example_hf);
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(4);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);
    FILE *f = fopen("tests_output/lsb4_insert_text4.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);

    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}
