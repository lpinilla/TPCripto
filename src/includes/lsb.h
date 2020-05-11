#ifndef _LSB_H_
#define _LSB_H_

#include <stdint.h>
#include <payload.h>
#include <carrier.h>
#include <lsb.h>

#define BYTE_SIZE 8

typedef struct t_lsb{
    int n; //La cantidad de bits menos significativos que a manejar.
    uint8_t c_mask; //máscara a aplicar a el byte del archivo contenedor para calcular I.
    uint8_t i_mask; //máscara a aplicar al byte a inyectar para saber qué bits usar.
    uint8_t shift_val; //valor auxiliar que depende del modo que vamos a utilizar en las cuentas
} t_lsb;

typedef t_lsb * lsb;

lsb create_lsb(int n);

void destroy_lsb(lsb l);

//int payload_fit_test(long carrier_size, long payload_size);

//función para inyectar el bit según la máscara en la imágen portadora.
void inject_bit(lsb l, carrier c, uint8_t i_byte, int bits_used);

//función para realizar la steganografía.
void worker_lsb_steg(lsb l, carrier c, payload p, long n_of_pixels);

#endif
