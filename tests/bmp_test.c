#include <bmp_header.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h>

void bmp_size_test();
void bmp_create_test();
void bmp_size_test_example1();

int main()
{
  create_suite("BMP test");
   add_test(bmp_size_test);
  add_test(bmp_create_test);
  //add_test(bmp_size_test_example1);
  run_suite();
  clear_suite();
}

// void bmp_size_test_example1()
// {
//   bmp_file bmpf = read_bmp("example1.BMP");
//   uint32_t size = 786486; //sacado del archivo
//   int32_t width = 1024;    //sacado dela archivo
//   int32_t heigh = 768;    //sacado del archivo
//   bmp_header bmph = bmpf->header;
//   printf("size %d %d %d %d\n",bmph->size,bmph->image_size_bytes,bmph->width_px,bmph->height_px);
//   if (size != bmph->size)
//   {
//     assert_true(1 == 0);
//   }
//   if (width != bmph->width_px)
//   {
//     assert_true(1 == 0);
//   }
//   if (heigh != bmph->height_px)
//   {
//     assert_true(1 == 0);
//   }

//   assert_true(1 == 1);
// }



void bmp_size_test()
{
  bmp_file bmpf = read_bmp("ladoLSB1.bmp");
  uint32_t size = 921654; //sacado del archivo
  int32_t width = 640;    //sacado dela archivo
  int32_t heigh = 480;    //sacado del archivo
  bmp_header bmph = bmpf->header;

  if (size != bmph->size)
  {
    assert_true(1 == 0);
  }
  if (width != bmph->width_px)
  {
    assert_true(1 == 0);
  }
  if (heigh != bmph->height_px)
  {
    assert_true(1 == 0);
  }

  assert_true(1 == 1);
}

void bmp_create_test()
{
  bmp_file bmpf = read_bmp("ladoLSB1.bmp");
  bmp_header bmph = bmpf->header;
  uint8_t* image = malloc(bmph->size);
  if (!image){
    printf("Error while asigning memory!\n");
    return;
  }
  memcpy(image, bmph, sizeof(t_bmp_header));
  memcpy(image + sizeof(t_bmp_header), bmpf->data, bmph->image_size_bytes);

  FILE *f = fopen("test.bmp", "wb");
  fwrite(image, sizeof(uint8_t), bmph->size, f);
  fclose(f);
}
