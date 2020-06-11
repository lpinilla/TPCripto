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
void lsb1_test(); //con imagen roma



int main(){
    create_suite("Ejemplos Definitivos");
    //add_test(roma_test);
    //add_test(lsb4_test);
    add_test(lsbi_test);
    //add_test(lsb1_test);
    run_suite();
    clear_suite();
    
}



void lsb1_test()
{

    bmp_file bmp_f = read_bmp("hugo4.bmp");
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



void lsb4_test(){

    bmp_file bmp_f = read_bmp("hugo4.bmp");
    bmp_header bmp_h = bmp_f->header;
    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    printf("hugo %d %d %d %d\n",bmp_h->size,bmp_h->bits_per_pixel,bmp_h->width_px, bmp_h->height_px);
    lsb l = create_lsb(4);
    payload p = extract_payload(l, c);
    printf("size %ld\n",p->size);
    printf("content : ");
    for (int i = 0; i < 20; i++)
    {
        printf("%x ", p->content[i]);
    }
    printf("\n");    
    // uint8_t* plaintext=malloc(p->size);
    // int d = decrypt(plaintext, "camuflado", p->content, p->size, cbc, aes256);

   
    FILE *f = fopen("lsb4_test", "w");
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

void lsbi_test(){

    bmp_file bmp_f = read_bmp("budapest.bmp");

    bmp_header bmp_h = bmp_f->header;

    carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes, bmp_h->width_px, bmp_h->height_px);
    printf("lsbi %d %d %d %d\n",bmp_h->size,bmp_h->bits_per_pixel,bmp_h->width_px, bmp_h->height_px);

    uint8_t *key = malloc(N); //48bits necesarios para la key

    payload p = extract_payload_lsbi(c, key);
    
    memcpy(key, bmp_f->data, N);

    //en plaintext vamos a guardar el payload desencriptado mas el tamanio al principio
    //el tamanio es 4(bytes para el tamanio)+tamanio del archivo(p->size)+5(extencion)
    uint8_t *plaintext = malloc(sizeof(uint8_t) * (p->size+T+E));

    //en final guardamos tamanio encriptado + payload encriptado
    uint8_t *final = malloc(p->size +T+E );

    //encriptamos el size devuelta, ya que para desencriptar el size tiene que estar encriptado al principio
    uint8_t* sizeencript=malloc(T);
    uint8_t array[T];
    array[0] = (int)((p->size >> 24) & 0xFF);
    array[1] = (int)((p->size >> 16) & 0xFF);
    array[2] = (int)((p->size >> 8) & 0XFF);
    array[3] = (int)((p->size & 0XFF));

    RC4(key,array,sizeencript,T);

    //copio al princio de final el size encriptado
    memcpy(final, sizeencript, T);

    //copio despues del size el contenido 
    memcpy(final + T, p->content, p->size+E);

    //desencripto final y lo guardo en plaintext
    RC4(key, final, plaintext, p->size+T+E);

    // uint8_t* plaintext1=malloc(p->size+9);
    // int d = decrypt(plaintext1, "camuflado", p->content, p->size, cfb, aes256);

    FILE *f = fopen("lsbi_test", "w");
    if (f == NULL)
    {
        printf("Could not create file!\n");
        return;
    }
    //escribo el plaintext en el file, sin el tamanio inicial ni la extension al final
    fwrite(plaintext+4, sizeof(uint8_t), p->size, f);
    fclose(f);

    destroy_carrier(c);
    destroy_payload(p);
    assert_true(1 == 1);
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