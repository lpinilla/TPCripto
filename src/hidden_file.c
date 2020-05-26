#include <hidden_file.h>
#define UNUSED(x) (void)(x)

hfs process_hf(char *file_name)
{
  hfs hf = (hfs)malloc(sizeof(t_hf));

  //size NO CUENTA  EOF cuando termina el archivo
  hf->size = file_size(file_name); //no tiene en cuenta el EOF
  hf->file = malloc(hf->size+1);//para agregar \0
  hf->ext = analice_name(file_name, hf);
  hf->file_name = malloc(strlen(file_name) + 1); //+1 para el /0
  memcpy(hf->file_name, file_name, strlen(file_name) + 1);

  store_file(file_name, hf);
  //printf("en porcess_hf %d %s %s %d\n",hf->size,hf->ext,hf->file,hf->ext_size);

  return hf;
}

void create_file(hfs hfs)
{

  FILE *f = fopen(hfs->file_name, "wb");
  fwrite(hfs->file, sizeof(uint8_t), hfs->size, f);
  return;
}

void store_file(char file_name[], hfs hfs)
{
  // opening the file in read mode
  FILE *fp = fopen(file_name, "r");

  // checking if the file exist or not
  if (fp == NULL)
  {
    printf("File Not Found!\n");
    return;
  }

  uint32_t count = fread(hfs->file, sizeof(uint8_t), hfs->size+1 , fp);

  fclose(fp);

  if (count != hfs->size)
  {
    printf("An error has occurd during reading file\n");
    return;
  }
  return;
}

uint8_t *analice_name(char *file_name, hfs hfs)
{
  uint8_t *extencion;
  uint8_t ext[10];
  int i = 0, j = 0;
  size_t s;
  while (file_name[i] != '\0' && file_name[i] != '.')
  {
    i++;
  }
  s = strlen(file_name - i);
  ext[0] = '.';
  i++;
  memcpy(ext + 1, file_name + i, s);
  while (ext[j] != '\0')
  {
    j++;
  }
  if (hfs != NULL)
  {
    hfs->ext_size = j;
  }
  extencion = malloc(j + 1);
  memcpy(extencion, ext, s + 1); //s no cuenta el \0
  return extencion;
}

//no tiene en cuenta el EOF. 
uint32_t file_size(char file_name[])
{
  // opening the file in read mode
  FILE *fp = fopen(file_name, "r");

  // checking if the file exist or not
  if (fp == NULL)
  {
    printf("File Not Found!\n");
    return -1;
  }

  fseek(fp, 0L, SEEK_END);

  // calculating the size of the file
  uint32_t res = ftell(fp);

//printf("Size en file size %d\n",res);
  // closing the file
  fclose(fp);

  return res;
}

uint8_t *concat_hf(hfs hf_info)
{
  uint8_t *rta = malloc(sizeof(uint32_t) + hf_info->size + hf_info->ext_size);
  rta[0] = hf_info->size >> 24;
  rta[1] = hf_info->size  >> 16;
  rta[2] = hf_info->size  >> 8;
  rta[3] = hf_info->size ;
//   printf("size: %c\n",hf_info->size >> 24);
//   printf("size: %d\n",hf_info->size >> 16);
//   printf("size: %d\n",hf_info->size >> 8);
//   printf("size: %d\n",hf_info->size);
// printf("rta %d\n",rta[0]);
  //memcpy(rta, hf_info->size, sizeof(uint32_t));
  memcpy(rta + sizeof(uint32_t), hf_info->file, hf_info->size );
  memcpy(rta + sizeof(uint32_t) + hf_info->size , hf_info->ext, hf_info->ext_size + 1);

  return rta;
}
