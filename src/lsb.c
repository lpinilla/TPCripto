#include <lsb.h>
#include <math.h>
#include <payload.h>
#include <carrier.h>
#include <jobs.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

lsb create_lsb(int n){
  lsb l = (lsb)malloc(sizeof(t_lsb));
  l->n = n;
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
 * realizar la inyección se realizó la cuenta: I XOR (( B AND C_M ) XOR B)
 * donde I es el bit del payload a inyectar, B el byte del archivo portador
 * y M la máscara, que depende del algoritmo.
 *
 * Para calcular I, tomamos la máscara y se la aplicamos al byte que
 * actualmente analizando del payload. Para calcular qué bits tenemos
 * que inyectar ahora, podemos realizar los desplazamientos correctos
 * de la máscara con los bits ya utilizados.
 */
void inject_bit(lsb l, carrier c, uint8_t i_byte, int bits_used) {
  if (l == NULL || c == NULL) return;
  uint8_t carrier_byte = c->content[c->counter];
  c->content[c->counter++] =
      ((i_byte & (l->i_mask >> bits_used)) >> (l->shift_val - bits_used)) ^
      ((carrier_byte & l->c_mask) ^ carrier_byte);
}

// función que va inyectar los bits en n píxeles sobre cada "fila" de la imagen
void worker_lsb_steg(lsb l, carrier c, payload p, long n_of_pixels) {
  if (l == NULL || c == NULL || p == NULL || n_of_pixels == 0) return;
  uint8_t i_byte = 0;
  for (int i = 0; i < n_of_pixels; i++) {
    if ( (i * l->n) % BYTE_SIZE == 0) i_byte = get_next_byte(p);
    inject_bit(l, c, i_byte, i * l->n % BYTE_SIZE);
  }
}

void * worker_sub_routine(void * args){
    t_routine_args * ar = (t_routine_args *) args;
    worker_lsb_steg(
            ar->l,
            ar->c,
            ar->p,
            ar->n_of_pixels);
    return NULL; //podría retornar el estado de la tarea
}


void lsb_steg(int n, carrier c, payload p){
    if(n <= 0 || c == NULL || p == NULL) return;
    long n_of_pixels = 0;
    long payload_reminder = p->size % c->pixel_width;
    lsb l = create_lsb(n);
    jobs total_jobs = divide_jobs(l, c, p);
    pthread_t main_thread;
    for(long i=0; i < total_jobs->size; i++){
        n_of_pixels = total_jobs[i].carriers[i]->pixel_width;
        if(i == (total_jobs->size - 1)){
            n_of_pixels = (payload_reminder == 0)?
                total_jobs[i].carriers[i]->pixel_width : payload_reminder;
        }
        t_routine_args args =
        {
            .l = l,
            .c = total_jobs[i].carriers[i],
            .p = total_jobs[i].payloads[i],
            .n_of_pixels = n_of_pixels
        };
        pthread_create(&main_thread, NULL, worker_sub_routine, (void *) &args);
    }
    pthread_join(main_thread, NULL);
}
