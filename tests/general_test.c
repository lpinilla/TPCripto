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

void lsb_1(); //extraer con lsb1
void lsb_4(); //extraer con lsb4

void lsb1_insert();
void lsb1_insert_2();
void lsb1_insert_3();
void lsb4_insert_3();
void lsb1_insert_image();
void lsb4_insert_image();
void lsb4_insert();
void ladoLSB4aes256ofb();

int main()
{
    create_suite("General Test");
    add_test(lsb_1);
    add_test(lsb_4);
    add_test(lsb1_insert);
    add_test(lsb4_insert);
    add_test(lsb1_insert_2);
    add_test(lsb1_insert_3);
    add_test(lsb4_insert_3);
    add_test(lsb1_insert_image);
    add_test(lsb4_insert_image);
    add_test(ladoLSB4aes256ofb);

    run_suite();
    clear_suite();
}

void ladoLSB4aes256ofb()
{

    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4aes256ofb.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    lsb l = create_lsb(4);

    payload p = extract_payload(l, c);

    uint8_t *plaintext = malloc(p->size);
    
    int d = decrypt(plaintext, "secreto", p->content, p->size, ofb, aes256);
    FILE *f = fopen("tests_output/ladoLSB4aes256ofb_prueba.png", "w");

    //muy importante el +4 para saltear el tamanio de lo encriptado
    fwrite(plaintext+4, sizeof(uint8_t), d, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);

    
}

void lsb_1()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    FILE *f = fopen("tests_output/lbs1_extra_prueba.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb_4()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
    FILE *f = fopen("tests_output/lbs4_extra_prueba.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void definitive_1()
{
    bmp_file bmp_f = read_bmp("files_for_testing/roma.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    FILE *f = fopen("tests_output/lsb1_unsteg.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb1_insert_image()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    hfs example_hf = process_hf("files_for_testing/lsbi_extract_test.png");
    uint8_t *payload_insert = concat_hf(example_hf);

    //poner total size en la estructura de hf
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(1);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);

    FILE *f = fopen("tests_output/lbs1_insert_ppng.png", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb4_insert_image()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    hfs example_hf = process_hf("files_for_testing/lsbi_extract_test.png");
    uint8_t *payload_insert = concat_hf(example_hf);

    //poner total size en la estructura de hf
    payload p = create_payload(payload_insert, sizeof(uint32_t) + example_hf->size + example_hf->ext_size);
    lsb l = create_lsb(4);
    lsb_steg(l, c, p);
    payload p1 = extract_payload(l, c);

    FILE *f = fopen("tests_output/lbs4_insert_ppng.png", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb1_insert()
{
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
    FILE *f = fopen("tests_output/lbs1_insert_text.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb4_insert()
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
    FILE *f = fopen("tests_output/lbs4_insert_text.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

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
    FILE *f = fopen("tests_output/lbs1_insert_prueba2.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

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
    FILE *f = fopen("tests_output/lsb1_insertion_text3.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void lsb4_insert_3()
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
    FILE *f = fopen("tests_output/lsb4_insertion_text3.txt", "w");
    fwrite(p1->content, sizeof(uint8_t), p1->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}
