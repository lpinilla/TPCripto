#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#include <stdbool.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include "openssl/sha.h"
#include <openssl/x509.h>
#include <openssl/conf.h>

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

// Function pointer to an encription function
typedef const EVP_CIPHER *(*cipherFunction)(void);

// Return value is size of ciphertext
int encrypt(unsigned char *plaintext, char* password, unsigned char* ciphertext, enum modes mode, enum algorithms algorithm);

// Return value is size of plaintext
int decrypt(unsigned char *plaintext, char * password, unsigned char * ciphertext, enum modes mode, enum algorithms algorithm);

bool simpleSHA256(void* input, unsigned long length, unsigned char* md);
void print_hash_binary(unsigned char * sha256hash);

#endif