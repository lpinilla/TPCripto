#ifndef _PAYLOAD_H_
#define _PAYLOAD_H_

#include <stdint.h>

/*
 * Header de la representación del mensaje (encriptado o no) que se va a
 * introducir en la imágen. La idea es definir una estructura que tiene
 * un arreglo de bytes a los cuales vamos a pedir de a uno para ir
 * inyectando dentro de la imágen.
 */

typedef struct t_payload{
    uint8_t * content; //puntero a el mensaje a inyectar como array de bytes
    uint8_t counter; //índice del byte actual en el array
    long size; //tamaño del array

} t_payload;

typedef t_payload * payload;

payload create_payload(uint8_t * content, long size);

void destroy_payload(payload p);

uint8_t get_next_byte(payload p);

#endif
