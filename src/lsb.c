#include <lsb.h>
#include <payload.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE 8

lsb create_lsb(int n, uint8_t* carrier, long size, long p_w, long p_h) {
  lsb l = (lsb)malloc(sizeof(t_lsb));
  l->n = n;
  l->carrier = carrier;
  l->c_size = size;
  l->pixel_width = p_w;
  l->pixel_height = p_h;
  l->counter = 0;
  l->mask = (1 << l->n) - 1;
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
  l->carrier[l->counter] = (i_byte & (l->mask << bits_used)) ^
                           ((carrier_byte & l->mask) ^ carrier_byte);
}

//función que va inyectar los bits sobre cada "fila" de la imagen
void lsb_steg(lsb l, payload p){
    if(l == NULL || p == NULL) return;
    uint8_t i_byte = get_next_byte(p);
    int bits_used = 0;
    for(int i = 0; i < l->pixel_width; i++){
        inject_bit(l, i_byte, bits_used);
        bits_used += l->n;
        if(bits_used == 8){
            i_byte = get_next_byte(p);
            bits_used = 0;
        }
    }
}
