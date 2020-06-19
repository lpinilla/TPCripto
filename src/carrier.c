#include <carrier.h>
#include <stdlib.h>

carrier create_carrier(uint8_t *content, long c_size, long p_w, long p_h) {
  if (content == NULL || c_size == 0 || p_w == 0 || p_h == 0) return NULL;
  carrier ret = (carrier)malloc(sizeof(t_carrier));
  ret->content = content;
  ret->c_size = c_size;
  ret->pixel_width = p_w;
  ret->pixel_height = p_h;
  ret->counter = 0;
  return ret;
}

void destroy_carrier(carrier c) { free(c); }
