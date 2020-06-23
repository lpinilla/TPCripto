#include <utils.h>
#include <carrier.h>
#define UNUSED(x) (void)(x)

int copy_file(char *target_path, char *source_path) {
    FILE *source, *target;
    source = fopen(source_path, "r");
    if (source == NULL) {
        printf("Unable to create copy of carrier file: %s\n", source_path);
        return 0;
    }

    target = fopen(target_path, "w+");
    
    if( target == NULL ) {
        fclose(source);
        return 0;
    }

    char c[4096];
     while (!feof(source)) {
        size_t bytes = fread(c, 1, sizeof(c), source);
        if (bytes) {
            fwrite(c, 1, bytes, target);
        }
    }
    fclose(source);
    fclose(target);
    return 1;
}

void save_file(uint8_t *content, long size, char *path) {
  FILE *f = fopen(path, "w");
  if (f == NULL) {
    printf("[ERROR] Could not create file to save!\n");
    return;
  }
  fwrite(content, sizeof(uint8_t), size, f);
  fclose(f);
  return;
}

long get_file_size(FILE *f) {
  // Es necesario que el file este apuntando al principio
  fseek(f, 0L, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);
  return size;
}



bool filesEqual(char *fp1, char *fp2) {
    int c1, c2;
    FILE *f1 = fopen(fp1, "r");
    FILE *f2 = fopen(fp2, "r");
    if (f1 == NULL) {
      printf(" Unable to compare files. Could not find %s\n", fp1);
      return false;
    }
    if (f2 == NULL) {
      printf(" Unable to compare files. Could not find %s\n", fp2);
      return false;
    }

    c1 = getc(f1);
    c2 = getc(f2);
    while (c1 != EOF || c2 != EOF) {
      if (c1 != c2)  {
        return false;
      }
      c1 = getc(f1);
      c2 = getc(f2);
    }
    if (c1 != EOF || c2 != EOF) {
      return false;
    }

    return true;
}
