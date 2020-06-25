#include <encrypt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// For development to avoid gcc error

void mostrarKey(unsigned char key[], int len) {
  int i;
  for (i = 0; i < len; i++) {
    printf("%0x", key[i]);
  }
}

void handleErrors(void) {
  ERR_print_errors_fp(stderr);
  abort();
}

cipherFunction getDesEncriptionFunctionPtr(enum modes mode) {
  switch (mode) {
    case ecb:
      return &EVP_des_ecb;
    case cfb:
      return &EVP_des_cfb8;
    case ofb:
      return &EVP_des_ofb;
    case cbc:
      return &EVP_des_cbc;
    default:
      printf("ERROR: UNKNOWN MODE %d", mode);
      abort();
  }
}

cipherFunction getAes128EncriptionFunctionPtr(enum modes mode) {
  switch (mode) {
    case ecb:
      return &EVP_aes_128_ecb;
    case cfb:
      // Todo. existe EVP_aes_128_cfb8 EVP_aes_128_cfb8 y EVP_aes_128_cfb1.
      // Preguntar cual va
      return &EVP_aes_128_cfb8;
    case ofb:
      return &EVP_aes_128_ofb;
    case cbc:
      return &EVP_aes_128_cbc;
    default:
      printf("ERROR: UNKNOWN MODE %d", mode);
      abort();
  }
}

cipherFunction getAes192EncriptionFunctionPtr(enum modes mode) {
  switch (mode) {
    case ecb:
      return &EVP_aes_192_ecb;
    case cfb:
      // Todo. existe EVP_aes_192_cfb8 EVP_aes_192_cfb8 y EVP_aes_192_cfb1.
      // Preguntar cual va
      return &EVP_aes_192_cfb8;
    case ofb:
      return &EVP_aes_192_ofb;
    case cbc:
      return &EVP_aes_192_cbc;
    default:
      printf("ERROR: UNKNOWN MODE %d", mode);
      abort();
  }
}

cipherFunction getAes256EncriptionFunctionPtr(enum modes mode) {
  switch (mode) {
    case ecb:
      return &EVP_aes_256_ecb;
    case cfb:
      // Todo. existe EVP_aes_256_cfb8 EVP_aes_256_cfb8 y EVP_aes_256_cfb1.
      // Preguntar cual va
      return &EVP_aes_256_cfb8;
    case ofb:
      return &EVP_aes_256_ofb;
    case cbc:
      return &EVP_aes_256_cbc;
    default:
      printf("ERROR: UNKNOWN MODE %d", mode);
      abort();
  }
}

cipherFunction getEncriptionFunctionPtr(enum algorithms alg, enum modes mode) {
  switch (alg) {
    case des:
      return getDesEncriptionFunctionPtr(mode);
    case aes128:
      return getAes128EncriptionFunctionPtr(mode);
    case aes192:
      return getAes192EncriptionFunctionPtr(mode);
    case aes256:
      return getAes256EncriptionFunctionPtr(mode);
    default:
      printf("ERROR: UNKNOWN ALGORITHM");
      abort();
  }
}

// Codigo adaptado de
// https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
int _encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
             unsigned char *iv, unsigned char *ciphertext,
             cipherFunction cipherFunctionPtr) {
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  // printf("Paramatros que llegaron: \n");
  // dump_binary("Plain", plaintext, plaintext_len);
  // dump_binary("Key",key, 256 / 8 / 2);
  // dump_binary("Iv", iv, 128 / 8 / 2);

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
  /*
   * Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_EncryptInit_ex(ctx, (*cipherFunctionPtr)(), NULL, key, iv))
    handleErrors();

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /*
   * Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  // dump_binary("Enc", ciphertext, 200/ 8 / 2);
  return ciphertext_len;
}

int _decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
             unsigned char *iv, unsigned char *plaintext,
             cipherFunction cipherFunctionPtr) {
  EVP_CIPHER_CTX *ctx;

  int len;
  // printf("Paramatros que llegaron a decrypt: \n");
  // dump_binary("cipher", ciphertext, ciphertext_len);
  // dump_binary("Key",key, 256 / 8 / 2);
  // dump_binary("Iv", iv, 128 / 8 / 2);
  int plaintext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /*
   * Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_DecryptInit_ex(ctx, (*cipherFunctionPtr)(), NULL, key, iv))
    handleErrors();

  /*
   * Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary.
   */
  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /*
   * Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

// Return value is size of plaintext
int decrypt(unsigned char *plaintext, char *password, unsigned char *ciphertext,
            int ciphertext_len, enum modes mode, enum algorithms algorithm) {
  int plaintext_len;
  // Sacado del Anexo
  const EVP_CIPHER *cipher;
  const EVP_MD *dgst = NULL;
  // int keylen, ivlen;
  // Generate the key from the password
  unsigned char key[EVP_MAX_KEY_LENGTH];
  unsigned char iv[EVP_MAX_IV_LENGTH];
  const unsigned char *salt = NULL;
  cipherFunction cipherFunctionPtr = getEncriptionFunctionPtr(algorithm, mode);
  cipher = (*cipherFunctionPtr)();
  dgst = EVP_sha256();
  EVP_BytesToKey(cipher, dgst, salt, (unsigned char *)password,
                 strlen(password), 1, key, iv);
  int keylen = EVP_CIPHER_key_length(cipher);
  int ivlen = EVP_CIPHER_iv_length(cipher);

  UNUSED(keylen);
  UNUSED(ivlen);

  plaintext_len = _decrypt(ciphertext, ciphertext_len, key, iv, plaintext,
                           cipherFunctionPtr);

  return plaintext_len;
}

// Return value is size of ciphertext
int encrypt(unsigned char *plaintext, long plaintext_size, char *password,
            unsigned char *ciphertext, enum modes mode,
            enum algorithms algorithm) {
  // Sacado del Anexo
  const EVP_CIPHER *cipher;
  const EVP_MD *dgst = NULL;
  int keylen, ivlen;
  // Generate the key from the password
  unsigned char key[EVP_MAX_KEY_LENGTH];
  unsigned char iv[EVP_MAX_IV_LENGTH];
  const unsigned char *salt = NULL;
  cipherFunction cipherFunctionPtr = getEncriptionFunctionPtr(algorithm, mode);
  cipher = (*cipherFunctionPtr)();
  dgst = EVP_sha256();
  EVP_BytesToKey(cipher, dgst, salt, (unsigned char *)password,
                 strlen(password), 1, key, iv);
  keylen = EVP_CIPHER_key_length(cipher);
  ivlen = EVP_CIPHER_iv_length(cipher);
  int cipher_len = _encrypt(plaintext, plaintext_size, key, iv, ciphertext,
                            cipherFunctionPtr);

  UNUSED(keylen);
  UNUSED(ivlen);

  return cipher_len;
}
