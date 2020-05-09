#include <lsb.h>
#include <math.h>
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
  switch (n) {
    case 1:
          l->c_mask = 0x01;
          l->shift_val = 7;
          break;
    case 2:
          l->c_mask = 0x03;
          l->shift_val = 5;
          break;
    case 4:
          l->c_mask = 0x0F;
          l->shift_val = 4;
    default:
          break;
  }
  l->i_mask = l->c_mask << l->shift_val;
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

  // printf("carrier byte %d \n", carrier_byte);
  // printf("i_byte %d %d %d %d \n", i_byte, l->i_mask >> bits_used, bits_used,
  // ( (i_byte & (l->i_mask >> bits_used)) << bits_used  )); printf("cuenta %d
  // \n", ( (i_byte & (l->i_mask >> bits_used)) >> (4 - l->shift_val +
  // bits_used)   ));
  /*printf("cuenta_2 %d \n",
            ((i_byte & (l->i_mask >> bits_used))
            >> ((BYTE_SIZE / 2) - ( bits_used + 1)) ) ^
            ((carrier_byte & l->c_mask) ^ carrier_byte));*/

  l->carrier[l->counter++] =
      ((i_byte & (l->i_mask >> bits_used)) >> (l->shift_val - bits_used)) ^
      ((carrier_byte & l->c_mask) ^ carrier_byte);
}

// función que va inyectar los bits en n píxeles sobre cada "fila" de la imagen
void worker_lsb_steg(lsb l, payload p, long n_of_pixels) {
  if (l == NULL || p == NULL || n_of_pixels == 0) return;
  uint8_t i_byte = get_next_byte(p);
  int step = (int)ceil(l->n / 2);
  for (int i = 0; i < n_of_pixels; i++) {
    inject_bit(l, i_byte, i * step);
    if (4 - ((i * step) % 4) == 0) {
      i_byte = get_next_byte(p);
    }
  }
}
