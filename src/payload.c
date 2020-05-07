#include <payload.h>
#include <stddef.h>

uint8_t get_next_byte(payload p) {
  if (p == NULL || p->counter == p->size) return 0;
  return *p->content[++(p->counter)];
}
