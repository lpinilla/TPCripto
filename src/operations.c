#include <bmp_header.h>
#include <carrier.h>
#include <hidden_file.h>
#include <lsb.h>
#include <operations.h>
#include <memory.h>
#include <options.h>
#include <payload.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

#define UNUSED(x) (void)(x)

payload get_payload(struct options *options) {
  bmp_file bmp_f = read_bmp(options->p);
  bmp_header bmp_h = bmp_f->header;
  carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes,
                             bmp_h->width_px, bmp_h->height_px);
  payload p;
  enum stego_types lsb_type = options->stego_type;
  if (lsb_type == lsbi) {
    p = extract_payload_lsbi(c);
  } else {
    lsb l;
    if (lsb_type == lsb1) {
      l = create_lsb(1);
    } else if (lsb_type == lsb4) {
      l = create_lsb(4);
    } else {
      printf("Unknown lsb type\n");
      return 0;
    }
    p = extract_payload(l, c);
    destroy_lsb(l);
  }
  destroy_carrier(c);
  return p;
}

void _embed(struct options *options) {
  uint8_t *ciphertext = NULL;
  // Paso 1: Crear size||data||ext a partir del archivo de entrada
  hfs hf = process_hf(options->in);
  uint8_t *in = concat_hf(hf);
  long in_size = sizeof(uint32_t) + hf->size + hf->ext_size;
  // Paso 2: Encriptar en caso de ser necesario
  if (options->encrypted) {
    ciphertext = malloc(in_size * 2);  // Reserve twice the space just in case
    int cipher_size =
        encrypt(in, in_size, options->encription_password, ciphertext + sizeof(uint32_t),
                options->encription_mode, options->encription_algorithm);
    uint32_t c_size = (uint32_t) cipher_size;
    in = ciphertext;
    ciphertext[0] = c_size >> 24;
    ciphertext[1] = c_size >> 16;
    ciphertext[2] = c_size >> 8;
    ciphertext[3] = c_size;
    in_size = (long)cipher_size + sizeof(uint32_t);
  }
  if (!copy_file(options->out, options->p)) {
      goto cleanup;
  }
  bmp_file bmp_f = read_bmp(options->out);
  bmp_header bmp_h = bmp_f->header;
  carrier c = create_carrier(bmp_f->data, bmp_h->image_size_bytes,
                             bmp_h->width_px, bmp_h->height_px);
  uint8_t * aux_data = c->content;
  payload p = create_payload(in, sizeof(uint32_t) + hf->size + hf->ext_size);
  enum stego_types lsb_type = options->stego_type;
  int steg_return;
  if (lsb_type == lsbi) {
    steg_return = lsb_i_steg(c, p);
  } else {
    if (lsb_type == lsb1) {
      lsb l = create_lsb(1);
      steg_return = lsb_steg(l, c, p);
    } else if (lsb_type == lsb4) {
      lsb l = create_lsb(4);
      steg_return = lsb_steg(l, c, p);
    } else {
      printf("Invalid lsb type\n");
      return;
    }
  }
  if(steg_return == -1){
      printf("Payload image too big\n");
      goto cleanup;
  }
  size_t header_size = sizeof(t_bmp_header);
  uint8_t *output = malloc(bmp_h->size);
  memcpy(output, bmp_h, header_size);
  memcpy(output + header_size, aux_data, c->c_size);
  save_file(output, bmp_h->size, options->out);
  free(output);
cleanup:
  // Cleanup
  if (ciphertext != NULL) free(ciphertext);
  return;
}

void _extract(struct options *options) {
  // A tener en cuenta: el tipo payload es un puntero
  payload pl = get_payload(options);
  
  if (pl == 0) {
    printf("Error extracting payload (returned 0)\n");
    return;
  }
  uint8_t *output = pl->content;
  long size = pl->size;
  if (options->encrypted) {
    uint8_t *plaintext = malloc(pl->size);
    int d =
        decrypt(plaintext, options->encription_password, pl->content, pl->size,
                options->encription_mode, options->encription_algorithm);
    size = d - RC4_T - RC4_E;
    output = plaintext;
    // muy importante el +4 para saltear el tamanio de lo encriptado, el -4 para
    // descontar el tamanio y -5 para extension
    output += 4;
  }
  save_file(output, size, options->out);
  // Cleanup
  destroy_payload(pl);
}
