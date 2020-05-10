#ifndef _LSB_H_
#define _LSB_H_

#include <stdint.h>
#include <payload.h>

typedef struct t_lsb{
    int n; //La cantidad de bits menos significativos que va a ejecutar
    uint8_t * carrier; //puntero a array de bits del archivo portador
    int counter; //contador del arreglo carrier
    long c_size; //tamaño total en bytes del archivo portador
    long pixel_width; //cantidad de pixels de largo (columnas)
    long pixel_height; //cantidad de pixels de alto (filas)
    uint8_t c_mask; //máscara a aplicar a el byte del archivo contenedor para calcular I.
    uint8_t i_mask; //máscara a aplicar al byte a inyectar para saber qué bits usar.
    uint8_t shift_val; //valor auxiliar que depende del modo que vamos a utilizar en las cuentas
} t_lsb;

typedef t_lsb * lsb;

lsb create_lsb(int n, uint8_t * carrier, long size, long pixel_width, long pixel_height);

void destroy_lsb(lsb l);

int payload_fit_test(long carrier_size, long payload_size);

//función para inyectar el bit según la máscara en la imágen portadora
void inject_bit(lsb l, uint8_t i_byte, int bits_used);

//función para realizar la steganografía
void worker_lsb_steg(lsb l, payload p, long n_of_pixels);

#endif
