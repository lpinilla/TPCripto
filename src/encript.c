#include <encript.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "openssl/sha.h"

// For development to avoid gcc errors
#define UNUSED(x) (void)(x)

// Codigo adaptado de
// https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
// int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
//             unsigned char *iv, unsigned char *ciphertext)
// {
//     EVP_CIPHER_CTX *ctx;

//     int len;

//     int ciphertext_len;

//     /* Create and initialise the context */
//     if(!(ctx = EVP_CIPHER_CTX_new()))
//         handleErrors();

//     /*
//      * Initialise the encryption operation. IMPORTANT - ensure you use a key
//      * and IV size appropriate for your cipher
//      * In this example we are using 256 bit AES (i.e. a 256 bit key). The
//      * IV size for *most* modes is the same as the block size. For AES this
//      * is 128 bits
//      */
//     if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
//         handleErrors();

//     /*
//      * Provide the message to be encrypted, and obtain the encrypted output.
//      * EVP_EncryptUpdate can be called multiple times if necessary
//      */
//     if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext,
//     plaintext_len))
//         handleErrors();
//     ciphertext_len = len;

//     /*
//      * Finalise the encryption. Further ciphertext bytes may be written at
//      * this stage.
//      */
//     if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
//         handleErrors();
//     ciphertext_len += len;

//     /* Clean up */
//     EVP_CIPHER_CTX_free(ctx);

//     return ciphertext_len;
// }

uint32_t get_key_size(enum algorithms alg) {
  switch (alg) {
    case des:
      return 64;
    case aes128:
      return 128;
    case aes192:
      return 192;
    case aes256:
      return 256;
    default:
      // TODO Exception handling
      printf("ERROR: UNKNOWN ALGORITHM");
      abort();
  }
}

// Calculate hash
// https://stackoverflow.com/questions/918676/generate-sha-hash-in-c-using-openssl-library

bool simpleSHA256(void* input, unsigned long length, unsigned char* md) {
  SHA256_CTX context;
  if (!SHA256_Init(&context)) return false;

  if (!SHA256_Update(&context, input, length)) return false;

  if (!SHA256_Final(md, &context)) return false;

  return true;
}

void print_hash_binary(unsigned char* sha256hash) {
  size_t len;
  for (len = 0; len < SHA256_DIGEST_LENGTH; ++len) {
    printf("%02x", sha256hash[len]);
  }
  printf("\n");
}

void encrypt(char* plaintext, char* password, char* ciphertext, enum modes mode,
             enum algorithms algorithm) {
  // Generate the key from the password
  uint32_t key_size_in_bits = get_key_size(algorithm);

  uint8_t key[key_size_in_bits / 8];

  // Sha definition
  unsigned char md[SHA256_DIGEST_LENGTH];  // 32 bytes
  if (!simpleSHA256(password, strlen(password), md)) {
    printf("There was an error calculating the key from the password");
    abort();
  }
  printf("hash: %s", md);

  UNUSED(key);
  UNUSED(plaintext);
  UNUSED(mode);
  UNUSED(ciphertext);
}

void handleErrors(void) {
  ERR_print_errors_fp(stderr);
  abort();
}
