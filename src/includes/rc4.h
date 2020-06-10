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

//para nuestra implementacion vamos a usar claves de 48bits
#define N 6

void swap(uint8_t *a, uint8_t *b);
int KSA(uint8_t *key, uint8_t *S);
int PRGA(uint8_t *S, uint8_t *plaintext, uint8_t *ciphertext,uint32_t size);
int RC4(uint8_t *key, uint8_t *plaintext, uint8_t *ciphertext, uint32_t size);

// void swap(unsigned char *s, unsigned int i, unsigned int j);
// void rc4_init(unsigned char *key, unsigned int key_lenght);
// unsigned char rc4_output();

#endif