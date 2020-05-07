#include <lsb.h>
#include <payload.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE 8

lsb create_lsb(int n, uint8_t* carrier, uint8_t size) {
  lsb l = (lsb)malloc(sizeof(t_lsb));
  l->n = n;
  l->carrier = carrier;
  l->size = size;
  l->counter = 0;
  l->mask = (1 << l->n) - 1;
  return l;
}

void destroy_lsb(lsb l) { free(l); }

/*
 * Función para inyectar bits en un byte del archivo portador. Para
 * realizar la inyección se realizó la cuenta: I XOR (( B XOR M ) XOR B)
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
