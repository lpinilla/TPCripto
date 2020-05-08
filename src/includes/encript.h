#ifndef _ENCRIPT_H_
#define _ENCRIPT_H_

#include <stdbool.h>

enum algorithms {
    des,
    aes128,
    aes192,
    aes256
};

enum modes {
    ecb,
    cfb,
    ofb,
    cbc
};

void encrypt(char *plaintext, char* password, char* ciphertext, enum modes mode, enum algorithms algorithm);
bool simpleSHA256(void* input, unsigned long length, unsigned char* md);
void print_hash_binary(unsigned char * sha256hash);

#endif