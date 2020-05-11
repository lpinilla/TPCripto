#ifndef _CARRIER_H_
#define _CARRIER_H_

#include <stdint.h>

typedef struct t_carrier{
    uint8_t * content; //puntero a array de bits del archivo portador
    long counter; //contador del arreglo carrier
    long c_size; //tamaño total en bytes del archivo portador
    long pixel_width; //cantidad de pixels de largo (columnas)
    long pixel_height; //cantidad de pixels de alto (filas)
}t_carrier;

typedef t_carrier * carrier;

carrier create_carrier(uint8_t *content, long c_size, long p_w, long p_h);


void destroy_carrier(carrier c);


#endif
