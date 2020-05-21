#include <hidden_file.h>
#include <bmp_header.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h>

void hidden_file_size_test();
void hidden_file_test();
void hidden_file_ext();
void hidden_file_procces();
void hidden_file_bmp();
void hidden_file_bmp_procces();
void hidden_file_create();
int main()
{
  create_suite("Hidden File test");
  add_test(hidden_file_size_test);
  add_test(hidden_file_test);
  add_test(hidden_file_ext);
  add_test(hidden_file_procces);
  add_test(hidden_file_bmp);
  add_test(hidden_file_bmp_procces);
  add_test(hidden_file_create);
  run_suite();
  clear_suite();
}

void hidden_file_create(){
  hfs test = (hfs)malloc(sizeof(t_hf));
  test = process_hf("test1.txt");

  create_file(test);

}

void hidden_file_bmp()
{
  //harcodeo la info de la foto bmp
  uint32_t size = 921654;

  if (file_size("ladoLSB1.bmp") != size)
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}

void hidden_file_bmp_procces()
{
  bmp_file bmpf = read_bmp("ladoLSB1.bmp");
  bmp_header bmph = bmpf->header;
  char *ext = ".bmp";
  hfs test = (hfs)malloc(sizeof(t_hf));
  test = process_hf("ladoLSB1.bmp");
  
    if (test->size != bmph->size)
  { 
    assert_true(1 == 0);
  }
  if (strncmp((char *)test->ext, ext, strlen(ext)))
  {
    assert_true(1 == 0);
  }
  if (!(memcmp(bmpf->data,test->file,bmph->size)))
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}

void hidden_file_size_test()
{
  char *str = "hola como estas?";
  uint32_t size = strlen(str); //strlen no tiene en cuenta el \0. EL file_size si lo cuenta

  if (file_size("test1.txt") != size + 1)
  {
    assert_true(1 == 0);
  }

  assert_true(1 == 1);
}

void hidden_file_procces()
{
  char *str = "hola como estas?";
  char *ext = ".txt";
  hfs test = (hfs)malloc(sizeof(t_hf));
  test = process_hf("test1.txt");
  if (test->size != strlen(str) + 1)
  { //  necesito el +1 porque strlen no cuenta /0, el size de la struct cuenta el EOF
    assert_true(1 == 0);
  }
  if (strncmp((char *)test->file, str, strlen(str)))
  {
    assert_true(1 == 0);
  }
  if (strncmp((char *)test->ext, ext, strlen(ext)))
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}

void hidden_file_ext()
{
  char *str = ".txt";
  uint8_t *ext = analice_name("test1.txt", NULL);
  if (strcmp(str, (char *)ext) != 0)
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}

void hidden_file_test()
{
  char *str = "hola como estas?";
  hfs hf = (hfs)malloc(sizeof(t_hf));
  hf->size = file_size("test1.txt");
  hf->file = malloc(hf->size);

  store_file("test1.txt", hf);

  if (strncmp((char *)hf->file, str, strlen(str)) != 0)
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}
