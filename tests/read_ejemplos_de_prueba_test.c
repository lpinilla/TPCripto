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

void lsb_4(); //extraer con lsb4
void lsb_1(); //extraer con lsb1
void ladoLSB4aes256ofb(); //estraer con aes256 ofb
void lsb_i(); //extraer con lsbi

int main()
{

    create_suite("Extract ejemplos prueba test");
    //add_test(lsb_1);
    //add_test(lsb_4);
    //add_test(ladoLSB4aes256ofb);
    add_test(lsb_i);
    run_suite();
    clear_suite();
}

void lsb_i()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSBI_corregido.bmp");

    bmp_header bmp_h = bmp_f->header;

    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    uint8_t *key = malloc(N); //48bits necesarios para la key

    payload p = extract_payload_lsbi(c, key);
    
    //memcpy(key, bmp_f->data, N);

    //encriptamos el size devuelta, ya que para desencriptar el size tiene que estar encriptado al principio
    // uint8_t* sizeencript=malloc(T);
    // uint8_t array[T];
    // array[0] = (int)((p->size >> 24) & 0xFF);
    // array[1] = (int)((p->size >> 16) & 0xFF);
    // array[2] = (int)((p->size >> 8) & 0XFF);
    // array[3] = (int)((p->size & 0XFF));

    // RC4(key,array,sizeencript,T);


    FILE *f = fopen("test_create_files/lsbi_extract_test.png", "w");
    if (f == NULL)
    {
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

void lsb_1()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB1.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(1);
    payload p = extract_payload(l, c);
    //  payload_ext(p);

    FILE *f = fopen("test_create_files/lsb1_extract_test.png", "w");
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

void lsb_4()
{
    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
   
    FILE *f = fopen("test_create_files/lsb4_extract_test.png", "w");
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

void ladoLSB4aes256ofb()
{

    bmp_file bmp_f = read_bmp("files_for_testing/ladoLSB4aes256ofb.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);

    lsb l = create_lsb(4);

    payload p = extract_payload(l, c);

    uint8_t *plaintext = malloc(p->size);
    //uint8_t *cyphertext = malloc(p->size+T+E);


    int d = decrypt(plaintext, "secreto", p->content, p->size, ofb, aes256);
    //printf("decrypt size: %d\n", d);
    //  for (int i = 0; i < 10; i++)
    //     {
    //         printf("end %c\n", *(plaintext + p->size - i));
    //     }
    FILE *f = fopen("test_create_files/ladoLSB4aes256ofb_extract_test.png", "w");
    if (f == NULL)
    {
        printf("Could not create file!\n");
        return;
    }

    //muy importante el +4 para saltear el tamanio de lo encriptado, el -4 para descontar el tamanio y -5 para extension
    fwrite(plaintext + 4, sizeof(uint8_t), d - T-E, f);
    fclose(f);
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
}
