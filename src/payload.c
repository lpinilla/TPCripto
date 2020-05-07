#include <payload.h>
#include <stddef.h>

uint8_t get_next_byte(payload p) {
  if (p == NULL) return 0;
  if(p->counter == p->size){
      p->completed = 1;
      return 0;
  }
  return *p->content[(p->counter++)];
}
