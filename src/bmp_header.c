#include <bmp_header.h>

bmp_file read_bmp(char *file_name)
{
  FILE *fp;
  bmp_header bmp_h = (bmp_header)malloc(sizeof(t_bmp_header));
  bmp_file bmp_f = (bmp_file)malloc(sizeof(t_bmp_file));

  fp = fopen(file_name, "rb");
  if (fp == NULL)
  {
    printf("File Not Found!\n");
    return NULL;
  }

  int32_t r = fread(bmp_h, sizeof(t_bmp_header), 1, fp);
  if (r != 1)
  {
    printf("Error while reading header!\n");
    fclose(fp);
    return NULL;
  }

  bmp_f->header = bmp_h;

  bmp_f->data = malloc(bmp_h->image_size_bytes);
  if (!bmp_f->data)
  {
    printf("No space for allocating bmp_f->data!\n");
    fclose(fp);
    return NULL;
  }

  int32_t r1 = fread(bmp_f->data, bmp_h->image_size_bytes, 1, fp);
  if (r1 != 1)
  {
    printf("Error while reading image data\n");
    fclose(fp);
    return NULL;
  }

  fclose(fp);
  return bmp_f;
}
