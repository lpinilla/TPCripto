#include <hidden_file.h>
#define UNUSED(x) (void)(x)


hfs process_hf(char* file_name){
  hfs hf = (hfs)malloc(sizeof(t_hf));

  //size NO INCLUYE ningun \0 cuando termina el texto
  hf->size=file_size(file_name); //tiene en cuenta el EOF
  hf->file=malloc(hf->size * sizeof(uint8_t));
  hf->ext=analice_name(file_name,hf);
  store_file(file_name,hf);

  return hf;
}

void create_file(hfs hfs){
  char* file_name;
  //uint8_t* new_file;

  file_name=malloc(strlen("new_file")+hfs->ext_size);
  memcpy(file_name+strlen("new_file"),hfs->ext,hfs->ext_size);
  printf("fle name: %s\n",file_name);

  //new_file=malloc(hfs->size);

  FILE *f = fopen(file_name, "wb");
  fwrite(hfs->file, sizeof(uint8_t), hfs->size, f);
  return;
}

void store_file(char file_name[],hfs hfs){
  // opening the file in read mode
FILE* fp = fopen(file_name, "r");

  // checking if the file exist or not
  if (fp == NULL) {
      printf("File Not Found!\n");
      return;
  }

  uint32_t count=fread(hfs->file,sizeof(uint8_t),hfs->size-1,fp);

  fclose(fp);

  if(count!= hfs->size-1){
    printf("An error has occurd during reading file\n");
    return ;
  }
  return;
}

uint8_t* analice_name(char* file_name,hfs hfs){
  uint8_t* extencion;
  uint8_t ext[10];
  int i=0,j=0;
  size_t s;
  while(file_name[i]!='\0' && file_name[i]!='.'){
    i++;
  }
  s=strlen(file_name-i);
  ext[0]='.';
  i++;
  memcpy(ext+1,file_name+i,s);
  while(ext[j]!='\0'){
    j++;
  }
  if(hfs!=NULL){
    hfs->ext_size=j;
  }
  extencion=malloc(j+1);
  memcpy(extencion,ext,s);
  return extencion;
}

//tiene en cuenta el EOF. Lo resto cuando lo asigno en la struct
uint32_t file_size(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    uint32_t res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
}
