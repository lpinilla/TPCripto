#include <lsb.h>
#include <payload.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BYTE_SIZE 8

lsb create_lsb(int n, uint8_t* carrier, long size, long p_w, long p_h) {
  lsb l = (lsb)malloc(sizeof(t_lsb));
  l->n = n;
  l->carrier = carrier;
  l->c_size = size;
  l->pixel_width = p_w;
  l->pixel_height = p_h;
  l->counter = 0;
  l->c_mask = (n == 1)? 0x1: 0x3;
  l->i_mask = l->c_mask << (int) (  (BYTE_SIZE / 2) - ceil(l->n / 2.0));
  return l;
}

void destroy_lsb(lsb l) { free(l); }

/*
 * Función para inyectar bits en un byte del archivo portador. Para
 * realizar la inyección se realizó la cuenta: I XOR (( B AND M ) XOR B)
 * donde I es el bit del payload a inyectar, B el byte del archivo portador
 * y M la máscara, que depende del algoritmo.
 *
 * Para calcular I, tomamos la máscara y se la aplicamos al byte que
 * actualmente analizando del payload. Para calcular qué bits tenemos
 * que inyectar ahora, podemos realizar los desplazamientos correctos
 * de la máscara con los bits ya utilizados.
 */

void inject_bit(lsb l, uint8_t i_byte, int bits_used) {
  if (l == NULL) return;
  uint8_t carrier_byte = l->carrier[l->counter];
  //printf("carrier byte %d \n", carrier_byte);
  //printf("i_byte %d %d %d %d \n", i_byte, l->i_mask, bits_used, i_byte & (l->i_mask << bits_used));
  //printf("cuenta %d \n", (carrier_byte & l->c_mask) ^ carrier_byte);
  //printf("cuenta_2 %d \n", (i_byte & (l->i_mask >> bits_used)) ^
  //                         ((carrier_byte & l->c_mask) ^ carrier_byte));
  l->carrier[l->counter++] = (i_byte & (l->i_mask >> bits_used)) ^
                           ((carrier_byte & l->c_mask) ^ carrier_byte);
}

//función que va inyectar los bits en n píxeles sobre cada "fila" de la imagen
void worker_lsb_steg(lsb l, payload p, long n_of_pixels){
    if(l == NULL || p == NULL || n_of_pixels == 0) return;
    uint8_t i_byte = get_next_byte(p), bits_used = 0;
    for(int i = 0; i < n_of_pixels; i++){
        inject_bit(l, i_byte, bits_used);
        bits_used += l->n;
        if(bits_used == 8){
            i_byte = get_next_byte(p);
            bits_used = 0;
        }
    }
}
