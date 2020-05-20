#ifndef _BMP_H_
#define _BMP_H_

#define BMP_TYPE 0x4D42

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <openssl/conf.h>
#include <stdint.h>

#define TYPE_OFFSET 0x0000
#define SIZE_OFFSET 0x0002
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BMP_HEADER_OFFSET 0x0036

typedef struct t_bmp_header{
  uint16_t  type;             // BMP TYPE = 0x4d42
  uint32_t  size;             // File size in bytes
  uint16_t  reserved1;        // Not used
  uint16_t  reserved2;        // Not used
  uint32_t  offset;           // Offset to image data in bytes from beginning of file (54 bytes)
  uint32_t  dib_header_size;  // DIB Header size in bytes (40 bytes)
  int32_t   width_px;         // Width of the image
  int32_t   height_px;        // Height of image
  uint16_t  num_planes;       // Number of color planes
  uint16_t  bits_per_pixel;   // Bits per pixel
  uint32_t  compression;      // Compression type = 0 because its not compressed
  uint32_t  image_size_bytes; // Image size in bytes
  int32_t   x_resolution_ppm; // Pixels per meter
  int32_t   y_resolution_ppm; // Pixels per meter
  uint32_t  num_colors;       // Number of colors
  uint32_t  important_colors; // Important colors
}t_bmp_header;

typedef t_bmp_header * bmp_header;

typedef struct t_bmp_file{
    bmp_header header;
    uint8_t* data;
} t_bmp_file;

typedef t_bmp_file * bmp_file;

bmp_file read_bmp(char* file_name);

#endif
