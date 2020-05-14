#include <hidden_file.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h>

void hidden_file_size_test();
void hidden_file_test();
void hidden_file_ext();
void hidden_file_procces();

int main() {
  create_suite("Hidden File test");
  add_test(hidden_file_size_test);
  add_test(hidden_file_test);
  add_test(hidden_file_ext);
 add_test(hidden_file_procces);
  run_suite();
  clear_suite();
}


void hidden_file_size_test() {
    char* str = "hola como estas?";
    uint32_t size=strlen(str);//no tiene en cuenta el \0. EL file_size si lo cuenta

    if (file_size("test1.txt")!=size+1) {
        assert_true(1== 0);
    }

    assert_true(1==1);
}

void hidden_file_procces(){
  char* str="hola como estas?";
  char* ext=".txt";
  hfs test=(hfs)malloc(sizeof(t_hf));
  test=process_hf("test1.txt");
  if(test->size != strlen(str)){// no necesito el +1 porque lo desconte cuando asigne en la struct
    assert_true(1== 0);
  }
  if(strncmp((char*)test->file,str,strlen(str))){
    assert_true(1== 0);
  }
  if(strncmp((char*)test->ext,ext,strlen(ext))){
    assert_true(1== 0);


  }
  assert_true(1== 1);


}

void hidden_file_ext(){
  char* str=".txt";
  uint8_t* ext=analice_name("test1.txt",NULL);
  if(strcmp(str,(char*)ext)!=0){
    assert_true(1== 0);

  }
  assert_true(1==1);

}

void hidden_file_test(){
  char* str="hola como estas?";
  hfs hf = (hfs)malloc(sizeof(t_hf));
  hf->size=file_size("test1.txt");
  hf->file=malloc(hf->size);

  store_file("test1.txt",hf);

  if(strncmp((char*)hf->file,str,strlen(str))!=0){
    assert_true(1== 0);
  }
  assert_true(1==1);

}
