#ifndef _HIDDEN_FILE_H_
#define _HIDDEN_FILE_H_

#include <encript.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <openssl/conf.h>
#include <stdint.h>

typedef struct hf{
  uint32_t size; //size of file 4 bytes
  uint8_t* file; //data in file
  uint8_t* ext; //file extencion with . and \0
  uint8_t ext_size;
}t_hf;

//hidden_file structure
typedef t_hf * hfs;

hfs process_hf(char* file_name);
uint32_t file_size(char file_name[]);
void store_file(char file_name[],hfs hfs);
uint8_t* analice_name(char* file_name,hfs hfs);
uint8_t* concat_hf(hfs hf_info);



#endif
