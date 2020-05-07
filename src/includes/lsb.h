#ifndef _LSB_H_
#define _LSB_H_

#include <stdint.h>
#include <payload.h>

typedef struct t_lsb{
    int n; //La cantidad de bits menos significativos que va a ejecutar
    uint8_t ** carrier; //puntero a array de bits del archivo portador
    int counter; //contador del arreglo carrier
    int size; //tamaño del archivo portador
    uint8_t mask; //máscara de 8 bits que se va a aplicar para extraer los n bits de acuerdo a los alg
} t_lsb;

typedef t_lsb * lsb;

lsb create_lsb(int n, uint8_t ** carrier, uint8_t size);

void destroy_lsb(lsb l);

//función para inyectar el bit según la máscara en la imágen portadora
void inject_bit(lsb l, uint8_t i_byte, int bits_used);

//función para realizar la steganografía
void lbs_steg(lsb l, payload p);

#endif
