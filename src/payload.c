#include <payload.h>
#include <stddef.h>
#include <stdlib.h>


payload create_payload(uint8_t * content, long size){
    payload p = (payload) malloc(sizeof(t_payload));
    p->content = content;
    p->counter = 0;
    p->size = size;
    p->bits_used = 0;
    return p;
}

void destroy_payload(payload p){
    free(p);
}

uint8_t get_next_byte(payload p) {
  if (p == NULL) return 0;
  if(p->counter == p->size){
      //p->completed = 1;
      return 0;
  }
  return p->content[(p->counter++)];
}

