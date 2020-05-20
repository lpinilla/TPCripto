#include <bmp_header.h>

bmp_file read_bmp(char* file_name){
FILE* fp;
bmp_header bmp_h=(bmp_header)malloc(sizeof(t_bmp_header));
bmp_file bmp_f=(bmp_file)malloc(sizeof(t_bmp_file));

fp=fopen(file_name,"rb");
if(fp==NULL){
  printf("File Not Found!\n");
  return NULL;
}


//verify if its bmp type of file
fseek(fp, TYPE_OFFSET, SEEK_SET);
int32_t r=fread(&(bmp_h->type), sizeof(bmp_h->type), 1, fp);
if(r!=1){
  printf("Error while reading type\n" );
  fclose(fp);
  return NULL;
}
if(bmp_h->type != BMP_TYPE){
  printf("File is not BMP type!\n");
  fclose(fp);
  return NULL;
}

//reading file size
fseek(fp, SIZE_OFFSET, SEEK_SET);
int32_t r1=fread(&(bmp_h->size), sizeof(bmp_h->size), 1, fp);
if(r1!=1){
  printf("Error while reading file size\n" );
  fclose(fp);
  return NULL;
}

//readinf width_px
fseek(fp, WIDTH_OFFSET, SEEK_SET);
int32_t r2=fread(&(bmp_h->width_px), sizeof(bmp_h->width_px), 1, fp);
if(r2!=1){
  printf("Error while reading width_px\n" );
  fclose(fp);
  return NULL;
}

//reading height_px
fseek(fp, HEIGHT_OFFSET, SEEK_SET);
int32_t r3=fread(&(bmp_h->height_px),sizeof(bmp_h->height_px), 1, fp);
if(r3!=1){
  printf("Error while reading height_px\n");
  fclose(fp);
  return NULL;
}

//setting pointer to image start
uint8_t* a=malloc(bmp_h->size);
bmp_f->data=malloc(bmp_h->size);

fseek(fp, BMP_HEADER_OFFSET, SEEK_SET);
uint32_t r4=fread(a,bmp_h->size-BMP_HEADER_OFFSET,1,fp);
bmp_f->data=a;

if(r4!=1){
  printf("Error while assigning image to array\n");
  fclose(fp);
  return NULL;
}

bmp_f->header=bmp_h;

fclose(fp);

  return bmp_f;

}
