#ifndef _LSB_H_
#define _LSB_H_

#include <stdint.h>
#include <payload.h>
#include <carrier.h>
#include <lsb.h>

#define BYTE_SIZE 8
#define MAX_THREADS 64
//valor aleatorio, se puede variar para evaluar la performance
#define BYTE_INJECTIONS_PER_JOB 256
#define KEY_SIZE 48


typedef struct t_lsb{
    int n; //La cantidad de bits menos significativos que a manejar.
    uint8_t c_mask; //máscara a aplicar a el byte del archivo contenedor para calcular I.
    uint8_t i_mask; //máscara a aplicar al byte a inyectar para saber qué bits usar.
    uint8_t shift_val; //valor auxiliar que depende del modo que vamos a utilizar en las cuentas
} t_lsb;

typedef t_lsb * lsb;

typedef struct{
    lsb l;
    carrier c;
    payload p;
    long n_of_pixels;
}t_routine_args;

typedef t_routine_args * routine_args;


lsb create_lsb(int n);

void destroy_lsb(lsb l);

//Steagnografía con lsb-n (sin incluír lsb-i)
void lsb_steg(lsb l, carrier c, payload p);

//función para recuperar un objeto payload del carrier en base a un lsb
payload extract_payload(lsb l, carrier c);

//LSB Improved
void lsb_i_steg(carrier c, payload p);

//función para recuperar un objeto payload del carrier con lsb-i
payload extract_payload_lsbi(carrier c, uint8_t * rc4_key);

//función para inyectar el bit según la máscara en la imágen portadora.
void inject_bit(lsb l, carrier c, uint8_t i_byte, int bits_used);

//función para recuperar un byte del archivo portador (consumiendolo)
uint8_t extract_byte(lsb l, carrier c);

//función para hayar el tamaño del payload a recuperar utilizando un valor de hop en caso de ser necesario
uint32_t extract_payload_size(lsb l, carrier c, int hop_value);

//función para realizar la steganografía.
void worker_lsb_steg(lsb l, carrier c, payload p, long n_of_pixels);

//wrapper de worker_lsb_steg para poder ser usado con threads
void * worker_sub_routine(void * args);

//función que se encarga de calcular el hop value de la imagen
uint8_t get_lsbi_hop(carrier c);

//función para inyectar un byte con lsbi en la imagen portadora dado un numero de saltos hop
void inject_lsbi_byte(lsb l, carrier c, uint8_t i_byte, int hop);

#endif
