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

// función que va inyectar los bits en los pixels a lo largo de la imágen
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
    return NULL;
}

uint8_t extract_byte(lsb l, carrier c, int hop_value){
    uint8_t ret = 0;
    int bytes_needed = sizeof(uint8_t) * BYTE_SIZE / l->n;
    for(int i = 0; i < bytes_needed; i++){
        ret ^= (c->content[i] & l->c_mask) << (l->shift_val - l->n*i);
        if(hop_value) c->content += (sizeof(uint8_t) * hop_value) - 1;
    }
    c->content += bytes_needed;
    return ret;
}

uint8_t extract_byte_lsbi(lsb l, carrier c, int hop_value){
    uint8_t ret = 0;
    int bytes_needed = sizeof(uint8_t) * BYTE_SIZE / l->n;
    for(int i = 0; i < bytes_needed; i++){
        //ret ^= (c->content[(i*hop_value*3)%c->c_size] & l->c_mask) <<
        //       (l->shift_val - l->n*i);
        ret ^= (*(c->content + ((i * hop_value * 3) % c->c_size) ) &
                l->c_mask) << (l->shift_val - l->n*i);

    }
    return ret;
}

uint32_t extract_payload_size(lsb l, carrier c, int hop){
    uint8_t bytes[BYTE_SIZE / 2] = {0, 0, 0, 0};
    for(int i = 0; i < (BYTE_SIZE/2); i++){
        if(hop){
            bytes[i] = extract_byte_lsbi(l,c, hop);
        }else{
            bytes[i] = extract_byte(l,c, 0);
        }
    }
    return (bytes[0] << 24) ^ (bytes[1] << 16) ^ (bytes[2] << 8) ^ bytes[3];
}

payload extract_payload(lsb l, carrier c){
    if(l == NULL || c == NULL) return NULL;
    payload p = (payload) malloc(sizeof(t_payload));
    p->size = extract_payload_size(l, c, 0);
    p->content = (uint8_t *) malloc(sizeof(uint8_t) * p->size);
    for(int i = 0; i < p->size; i++) p->content[i] = extract_byte(l, c, 0);
    return p;
}

void lsb_steg(int n, carrier c, payload p){
    if(n <= 0 || c == NULL || p == NULL) return;
    int n_threads = 0;
    lsb l = create_lsb(n);
    jobs total_jobs = divide_jobs(l, c, p, BYTE_INJECTIONS_PER_JOB);
    pthread_t main_thread;
    t_routine_args args[MAX_THREADS];
    for(long i=0; i < total_jobs->size; i++){
        args[i].l = l;
        args[i].c = (carrier) total_jobs[i].carrier;
        args[i].p = (payload) total_jobs[i].payload;
        args[i].n_of_pixels = args[i].c->c_size;
        pthread_create(&main_thread, NULL, worker_sub_routine, (void *) (args + sizeof(t_routine_args) * i));
        n_threads++;
        //si alcanzamos el límite, esperamos que terminen para no saturar la pc
        if(n_threads == MAX_THREADS){
            pthread_join(main_thread, NULL);
            n_threads = 0;
        }
    }
    pthread_join(main_thread, NULL);
    destroy_lsb(l);
    destroy_jobs(total_jobs);
}

uint8_t get_lsbi_hop(carrier c){
    uint8_t hop_byte = *c->content, ret = 0;
    for(int i=(BYTE_SIZE - 1); !ret && i >= 0; i++) ret = hop_byte & (1 << i);
    c->content += sizeof(uint8_t);
    return (!ret)? 256: ret;
}

void inject_lsbi_byte(lsb l, carrier c, uint8_t i_byte, int hop){
    for(int i = 0; i < BYTE_SIZE; i++){
        inject_bit(l, c, i_byte, i);
        c->content += sizeof(uint8_t) * (hop + 1);
    }
}

void lsb_i_steg(carrier c, payload p){
    lsb l = create_lsb(1);
    uint8_t hop_value = get_lsbi_hop(c);
    uint8_t byte_to_inject = 0;
    long bytes_needed = p->size * (BYTE_SIZE/ l->n);
    for(long i = 0; i < bytes_needed; i++){
        byte_to_inject = get_next_byte(p);
        inject_lsbi_byte(l, c, byte_to_inject, hop_value);
    }
    destroy_lsb(l);
}

payload extract_payload_lsbi(carrier c){
    if(c == NULL) return NULL;
    lsb l = create_lsb(1);
    uint8_t hop= get_lsbi_hop(c);
    c->content += sizeof(uint8_t) * 5; //ignorando el byte de la llave
    printf("hop: %d \n", hop);
    payload p = (payload) malloc(sizeof(t_payload));
    uint32_t payload_size = extract_payload_size(l, c, hop);
    //lsb1 size 44886
    printf("size: %d \n", payload_size);
    p->size = payload_size;
    //p->content = (uint8_t *) malloc(sizeof(uint8_t) * payload_size);
    //for(long i =0; i < p->size; i++) p->content[i] = extract_byte_lsbi(l,c,hop);
    destroy_lsb(l);
    return p;
}
