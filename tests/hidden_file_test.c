#include <hidden_file.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h>

void hidden_file_size_test();
void hidden_file_test();
void hidden_file_ext();
void hidden_file_procces();
void hidden_file_concat();
void hidden_file_size_test_2();
void hidden_file_ext_2();
void hidden_file_procces_2();
void hidden_file_concat_2();

int main()
{
  create_suite("Hidden File test");
  add_test(hidden_file_size_test);
  add_test(hidden_file_test);
  add_test(hidden_file_ext);
  add_test(hidden_file_procces);
  add_test(hidden_file_concat);
  add_test(hidden_file_size_test);
  add_test(hidden_file_size_test_2);
  add_test(hidden_file_ext_2);
  add_test(hidden_file_procces_2);
  add_test(hidden_file_concat_2);
  run_suite();
  clear_suite();
}

void hidden_file_size_test()
{
  char *str = "hola como estas?";
  uint32_t size = strlen(str);
  if (file_size("tests_input/test1.txt") != size)
  {
    assert_true(1 == 0);
  }

  assert_true(1 == 1);
}

void hidden_file_size_test_2()
{
  char *str = "[Intro]La-la-la-la, la-la-la-la[Verse 1]Call me what you wanna, I'll be what you wannaI've been here a thousand times";
  uint32_t size = strlen(str);
  if (file_size("tests_input/test2.txt") != size)
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
  test = process_hf("tests_input/test1.txt");
  if (test->size != strlen(str))
  { // no necesito el porque strlen no cuenta \0 y file size tampoco
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

void hidden_file_procces_2()
{
  char *str = "[Intro]La-la-la-la, la-la-la-la[Verse 1]Call me what you wanna, I'll be what you wannaI've been here a thousand times";
  char *ext = ".txt";
  hfs test = (hfs)malloc(sizeof(t_hf));
  test = process_hf("tests_input/test2.txt");
  if (test->size != strlen(str))
  { // no necesito el porque strlen no cuenta \0 y file size tampoco
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
  uint8_t *ext = analice_name("tests_input/test1.txt", NULL);
  if (strcmp(str, (char *)ext) != 0)
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}

void hidden_file_ext_2()
{
  char *str = ".txt";
  uint8_t *ext = analice_name("tests_input/test2.txt", NULL);
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
  hf->size = file_size("tests_input/test1.txt");
  hf->file = malloc(hf->size);

  store_file("tests_input/test1.txt", hf);

  if (strncmp((char *)hf->file, str, strlen(str)) != 0)
  {
    assert_true(1 == 0);
  }
  assert_true(1 == 1);
}

void hidden_file_concat()
{
  char * expected = "hola como estas?.txt";
  hfs test = (hfs)malloc(sizeof(t_hf));
  test = process_hf("tests_input/test1.txt");
  uint8_t *concat = concat_hf(test);
  assert_true(strcmp((char *) concat + 4, expected) == 0);
}

void hidden_file_concat_2()
{
  char * expected = "[Intro]La-la-la-la, la-la-la-la[Verse 1]Call me what you wanna, I'll be what you wannaI've been here a thousand times.txt";
  hfs test = (hfs)malloc(sizeof(t_hf));
  test = process_hf("tests_input/test2.txt");
  uint8_t *concat = concat_hf(test);
  assert_true(strcmp((char *) concat + 4, expected) == 0);
}
