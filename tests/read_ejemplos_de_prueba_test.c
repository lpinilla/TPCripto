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

void lsb_4(); //extraer con lsb4
void lsb_1(); //extraer con lsb1
void ladoLSB4aes256ofb();
void lsb_i(); //extraer con lsbi

int main()
{
    create_suite("Extract ejemplos prueba test");
    add_test(lsb_1);
    add_test(lsb_4);
    add_test(ladoLSB4aes256ofb);
    //add_test(lsb_i);
    run_suite();
    clear_suite();
}

void lsb_i()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSBI_corregido.bmp");

    bmp_header bmp_h = bmp_f->header;

    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    lsb l = create_lsb(1);
    uint8_t *key = malloc(64); //48bits necesarios, lo demas se rellena con 0

    payload p = extract_payload_lsbi(c, key);
    printf("hasta aca\n");
    printf("SIZE: %ld\n", p->size);
    //rc4
    // uint8_t* key=malloc(48); //48bits
    // memcpy(key,bmp_f->data,N);

    uint8_t *cyphertext = malloc(p->size);
    printf("hasta aca1 %c\n", p->content[0]);

    memcpy(cyphertext, p->content, p->size);

    uint8_t *plaintext = malloc(sizeof(uint8_t) * p->size);
    RC4(key, cyphertext, plaintext, p->size);

    FILE *f = fopen("test_create_files/lbsi_extract_test.png", "w");
    fwrite(plaintext, sizeof(uint8_t), p->size, f);
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
    //  payload_ext(p);

    FILE *f = fopen("test_create_files/lbs1_extract_test.png", "w");
    if (f == NULL)
    {
        printf("File Not Found!\n");
        return ;
    }
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
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("end %c\n", *(p->content + p->size +3 - i));
    // }
    FILE *f = fopen("test_create_files/lbs4_extract_test.png", "w");
    fwrite(p->content, sizeof(uint8_t), p->size, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}

void ladoLSB4aes256ofb()
{

    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4aes256ofb.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    lsb l = create_lsb(4);

    payload p = extract_payload(l, c);
    //printf("payload size: %ld\n", p->size);

    uint8_t *plaintext = malloc(p->size);

    int d = decrypt(plaintext, "secreto", p->content, p->size, ofb, aes256);
    //printf("decrypt size: %d\n", d);
//  for (int i = 0; i < 10; i++)
//     {
//         printf("end %c\n", *(plaintext + p->size - i));
//     }
    FILE *f = fopen("test_create_files/ladoLSB4aes256ofb_extract_test.png", "w");

    //muy importante el +4 para saltear el tamanio de lo encriptado, el -4 para descontar el tamanio de lo leido
    fwrite(plaintext + 4, sizeof(uint8_t), d - 4, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}