#ifndef _RC4_H_
#define _RC4_H_

/*Codigo adaptado de https://gist.github.com/rverton/a44fc8ca67ab9ec32089 */

//el tamanio de la clave es de 48bits
//el tamanio del plaintext/cyphertext es el tamanio de la imagen - 48bits de la clave
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define RC4_N 6 //para nuestra implementacion vamos a usar claves de 48bits
#define RC4_T 4 //tamanio del archivo
#define RC4_E 4 //tamanio de la exxtension (.png\0)

void swap(uint8_t *a, uint8_t *b);
int KSA(uint8_t *key, uint8_t *S);
int PRGA(uint8_t *S, uint8_t *plaintext, uint8_t *ciphertext,uint32_t size);
int RC4(uint8_t *key, uint8_t *plaintext, uint8_t *ciphertext, uint32_t size);
int prepare_size(uint32_t payload_size,uint8_t* prep_size);
int prepare_size_enc(uint32_t payload_size, uint8_t *prep_size);

uint32_t hex_to_dec(uint8_t* payload_size_decript,int size);


#endif
