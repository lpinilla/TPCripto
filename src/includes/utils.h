#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

long get_file_size(FILE *f);
void save_file(uint8_t *content, long size, char *path);
int copy_file(char *target_path, char *source_path);
bool filesEqual(char *fp1, char *fp2);

#endif