#include <jobs.h>
#include <lsb.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <bmp_header.h>

lsb create_lsb(int n)
{
  lsb l = (lsb)malloc(sizeof(t_lsb));
  l->n = n;
  switch (n)
  {
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
void inject_bit(lsb l, carrier c, uint8_t i_byte, int bits_used)
{
  if (l == NULL || c == NULL)
    return;
  uint8_t carrier_byte = c->content[c->counter];
  c->content[c->counter++] =
      ((i_byte & (l->i_mask >> bits_used)) >> (l->shift_val - bits_used)) ^
      ((carrier_byte & l->c_mask) ^ carrier_byte);
}

// función que va inyectar los bits en los pixels a lo largo de la imágen
void worker_lsb_steg(lsb l, carrier c, payload p, long n_of_pixels)
{
  if (l == NULL || c == NULL || p == NULL || n_of_pixels == 0)
    return;
  uint8_t i_byte = 0;
  for (int i = 0; i < n_of_pixels; i++)
  {
    if ((i * l->n) % BYTE_SIZE == 0)
      i_byte = get_next_byte(p);
    inject_bit(l, c, i_byte, i * l->n % BYTE_SIZE);
  }
}

void *worker_sub_routine(void *args)
{
  t_routine_args *ar = (t_routine_args *)args;
  worker_lsb_steg(ar->l, ar->c, ar->p, ar->n_of_pixels);
  return NULL;
}

uint8_t extract_byte(lsb l, carrier c)
{
  uint8_t ret = 0;
  int bytes_needed = sizeof(uint8_t) * BYTE_SIZE / l->n;
  for (int i = 0; i < bytes_needed; i++)
  {
    ret ^= (c->content[i] & l->c_mask) << (l->shift_val - l->n * i);
  }
  c->content += bytes_needed;
  return ret;
}

uint8_t extract_byte_lsbi(lsb l, carrier c, int hop_value, long i)
{
  uint8_t ret = 0;
  uint8_t bytes_needed = sizeof(uint8_t) * BYTE_SIZE / l->n;
  for (long j = 0; j < bytes_needed; j++)
  {
    ret ^= (c->content[((i * bytes_needed + j) * hop_value) % (c->c_size - 1)] &
            l->c_mask)
           << (l->shift_val - l->n * j);
  }
  return ret;
}

uint32_t extract_payload_size(lsb l, carrier c, int hop)
{
  uint8_t bytes[BYTE_SIZE / 2] = {0, 0, 0, 0};
  for (int i = 0; i < (BYTE_SIZE / 2); i++)
  {
    if (hop)
    {
      bytes[i] = extract_byte_lsbi(l, c, hop, i);
    }
    else
    {
      bytes[i] = extract_byte(l, c);
    }
  }
  return (bytes[0] << 24) ^ (bytes[1] << 16) ^ (bytes[2] << 8) ^ bytes[3];
}

payload extract_payload(lsb l, carrier c)
{
  if (l == NULL || c == NULL)
    return NULL;
  payload p = (payload)malloc(sizeof(t_payload));
  p->size = extract_payload_size(l, c, 0);
  if (p->size >= c->c_size)
    return NULL;
  p->content = (uint8_t *)malloc(sizeof(uint8_t) * p->size + 5);
  for (int i = 0; i < p->size + 5; i++)
    p->content[i] = extract_byte(l, c);
  return p;
}

int lsb_steg(lsb l, carrier c, payload p)
{
  if (l == NULL || c == NULL || p == NULL)
    return 1;
  if ((p->size * (BYTE_SIZE / l->n)) >= c->c_size)
    return -1;
  jobs total_jobs = divide_jobs(l, c, p, BYTE_INJECTIONS_PER_JOB);
  pthread_t threads[total_jobs->size];
  routine_args args =
      (routine_args)malloc(sizeof(t_routine_args) * total_jobs->size);
  for (long i = 0; i < total_jobs->size; i++)
  {
    args[i].l = l;
    args[i].c = (carrier)total_jobs[i].carrier;
    args[i].p = (payload)total_jobs[i].payload;
    args[i].n_of_pixels = BYTE_INJECTIONS_PER_JOB * BYTE_SIZE / l->n;
    pthread_create(&threads[i], NULL, worker_sub_routine, (void *)&args[i]);
  }
  for (long i = 0; i < total_jobs->size; i++)
    pthread_join(threads[i], NULL);
  free(args);
  destroy_jobs(total_jobs);
  return 0;
}

uint8_t get_lsbi_hop(carrier c)
{
  uint8_t hop_byte = *c->content, ret = 0;
  for(int i = (BYTE_SIZE - 1); !ret && i >= 0; i--) ret = hop_byte & (1 << i);
  return (!ret) ? 256 : ret;
}

//uint8_t extract_byte_lsbi(lsb l, carrier c, int hop_value, long i){
//  uint8_t ret = 0;
//  uint8_t bytes_needed = sizeof(uint8_t) * BYTE_SIZE / l->n;
//  for (long j = 0; j < bytes_needed; j++){
//    ret ^= (c->content[((i * bytes_needed + j) * hop_value) % (c->c_size - 1)] &
//            l->c_mask)
//           << (l->shift_val - l->n * j);
//  }
//  return ret;
//}

void inject_lsbi_byte(lsb l, carrier c, uint8_t i_byte, int hop){
    for (int i = 0; i < BYTE_SIZE; i++) {
        //printf("%ld \n", c->counter);
        inject_bit(l, c, i_byte, i);
        c->counter--;
        c->counter += hop;
        if(c->counter > (c->c_size - 1)){
            c->counter = c->counter % (c->c_size - 1);
        }
        //printf("%ld \n", c->counter);
    }
}

int lsb_i_steg(carrier c, payload p){
  if(c == NULL || p == NULL) return 1;
  lsb l = create_lsb(1);
  //agarro la key, osea los primeros 6 bytes del carrier
  uint8_t *rc4_key = malloc(RC4_N); //claves de 48 bits
  memcpy(rc4_key, c->content, KEY_SIZE / BYTE_SIZE);
  payload rc4_p = rc4_payload(rc4_key, p);
  if(rc4_p == NULL) return 1;
  uint8_t hop_value = get_lsbi_hop(c);
  uint8_t byte_to_inject = 0;
  long bytes_needed = rc4_p->size * BYTE_SIZE;
  if (bytes_needed >= c->c_size) return -1;
  c->content += 6 * sizeof(uint8_t);
  c->counter = 0;
  for (long i = 0; i < rc4_p->size; i++){
    byte_to_inject = get_next_byte(rc4_p);
    inject_lsbi_byte(l, c, byte_to_inject, hop_value);
  }
  destroy_lsb(l);
  destroy_payload(rc4_p);
  return 0;
}

payload rc4_payload(uint8_t * rc4_key, payload p){
    if(rc4_key == NULL) return NULL;
    p->content += 4;
    p->size -= (RC4_T + RC4_E);
    payload encrypt_p = malloc(sizeof(t_payload));
    encrypt_p->content = malloc(p->size+RC4_E+RC4_T);
    uint8_t *encript_size = malloc(RC4_T);
    //encripto con RC4 el contentsize
    uint8_t *prep_size = malloc(RC4_T);
    prepare_size_enc(p->size, prep_size);
    RC4(rc4_key,prep_size,encript_size,RC4_T);
    //encripto el tamaño||contenido
    uint8_t* to_encript=malloc(p->size+RC4_E+RC4_T);
    memcpy(to_encript,prep_size,RC4_T);
    memcpy(to_encript+RC4_T,p->content,p->size+RC4_E);
    RC4(rc4_key,to_encript, encrypt_p->content,(uint32_t)p->size+RC4_E+RC4_T);
    encrypt_p->size = p->size + (RC4_T + RC4_E);
    return encrypt_p;
}


payload extract_payload_lsbi(carrier c){
  if (c == NULL) return NULL;
  lsb l = create_lsb(1);
  uint8_t *rc4_key = malloc(RC4_N); //claves de 48 bits
  memcpy(rc4_key, c->content, KEY_SIZE / BYTE_SIZE);
  uint8_t hop = get_lsbi_hop(c);
   //c->content += sizeof(uint8_t) * 6; //ignorando el byte de la llave
  payload p = (payload)malloc(sizeof(t_payload));
  uint32_t payload_size_enc = extract_payload_size(l, c, hop);
  uint8_t *prep_size = malloc(RC4_T);
  int size_rc4 = prepare_size(payload_size_enc, prep_size);
  //desencripto el size
  uint8_t *payload_size_decript = malloc(6);
  RC4(rc4_key, prep_size, payload_size_decript, size_rc4);
  //convierto payload_size_decript de hexa a numero decimal
  p->size = hex_to_dec(payload_size_decript, size_rc4);
  if (p->size >= c->c_size)
    return NULL;
  p->content = (uint8_t *)malloc(sizeof(uint8_t) * (p->size + 4));
  for (long i = 0; i < p->size + 4; i++)
    p->content[i] = extract_byte_lsbi(l, c, hop, i + 4);
  // ya tengo el contenido encriptado con RC4 en p->content, y el size desencriptado en p->size, y el size encriptado en
  // payload_size_enc y el size encriptado en 4 bytes en prep_size

  //en plaintext vamos a guardar el payload desencriptado mas el tamaño al principio
  //el tamaño es 4(bytes para el tamaño)+tamaño del archivo(p->size)+5(extencion)
  uint8_t *plaintext = malloc(sizeof(uint8_t) * (p->size + RC4_T + RC4_E));
  //en final guardamos tamaño encriptado + payload encriptado
  uint8_t *final = malloc(p->size + RC4_T + RC4_E);

  //copio al princio de final el size encriptado
  memcpy(final, prep_size, RC4_T);

  //copio despues del size el contenido
  memcpy(final + RC4_T, p->content, p->size + RC4_E);

  //desencripto final y lo guardo en plaintext
  RC4(rc4_key, final, plaintext, p->size + RC4_T + RC4_E);
  //guardo en p->content el contenido desencriptado
  memcpy(p->content, plaintext + RC4_T, p->size + RC4_T);
  destroy_lsb(l);
  return p;
}
