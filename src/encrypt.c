#include <encrypt.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


// For development to avoid gcc errors
#define UNUSED(x) (void)(x)




void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

cipherFunction getDesEncriptionFunctionPtr (enum modes mode) {
    switch (mode) {
        case ecb:
            return &EVP_des_ecb;
        case cfb:
            // Todo. existe EVP_des_cfb64 EVP_des_cfb8 y EVP_des_cfb1. Preguntar cual va
            return &EVP_des_cfb64;
        case ofb:
            return &EVP_des_ofb;
        case cbc:
            return &EVP_des_cbc;
        default:
            printf("ERROR: UNKNOWN MODE %d", mode);
            abort();
    }
}

cipherFunction getAes128EncriptionFunctionPtr (enum modes mode) {
    switch (mode) {
        case ecb:
            return &EVP_aes_128_ecb;
        case cfb:
            // Todo. existe EVP_aes_128_cfb128 EVP_aes_128_cfb8 y EVP_aes_128_cfb1. Preguntar cual va
            return &EVP_aes_128_cfb128;
        case ofb:
            return &EVP_aes_128_ofb;
        case cbc:
            return &EVP_aes_128_cbc;
        default:
            printf("ERROR: UNKNOWN MODE %d", mode);
            abort();
    }
}

cipherFunction getAes192EncriptionFunctionPtr (enum modes mode) {
    switch (mode) {
        case ecb:
            return &EVP_aes_192_ecb;
        case cfb:
            // Todo. existe EVP_aes_192_cfb128 EVP_aes_192_cfb8 y EVP_aes_192_cfb1. Preguntar cual va
            return &EVP_aes_192_cfb128;
        case ofb:
            return &EVP_aes_192_ofb;
        case cbc:
            return &EVP_aes_192_cbc;
        default:
            printf("ERROR: UNKNOWN MODE %d", mode);
            abort();
    }
}

cipherFunction getAes256EncriptionFunctionPtr (enum modes mode) {
    switch (mode) {
        case ecb:
            return &EVP_aes_256_ecb;
        case cfb:
            // Todo. existe EVP_aes_256_cfb128 EVP_aes_256_cfb8 y EVP_aes_256_cfb1. Preguntar cual va
            return &EVP_aes_256_cfb128;
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
            // TODO Exception handling
            printf("ERROR: UNKNOWN ALGORITHM");
            abort();
    }
}

void print_binary(unsigned char * binary, size_t size) {
    size_t len;
    for (len = 0; len < size; ++len) {
        printf("%02x", binary[len]);
    }
    printf("\n");
}

void print_hash_binary(unsigned char * sha256hash) {
    print_binary(sha256hash, SHA256_DIGEST_LENGTH);
}

void dump_binary(char * title, unsigned char * binary, size_t size) {
    printf("%s: \t", title);
    print_binary(binary, size);
}

// Codigo adaptado de  https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
int _encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext, cipherFunction cipherFunctionPtr)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    printf("Paramatros que llegaron: \n");
    dump_binary("Plain", plaintext, plaintext_len);
    dump_binary("Key",key, 256 / 8);
    dump_binary("Iv", iv, 128 / 8);

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();
    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, (*cipherFunctionPtr)(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    dump_binary("Enc", ciphertext, 200/ 8);
    return ciphertext_len;
}

int _decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}



size_t get_iv_size(enum algorithms alg) {
    switch (alg) {
        case des:
            return 64;
        case aes128:
        case aes192:
        case aes256:
            return 128;
        default:
            // TODO Exception handling
            printf("ERROR: UNKNOWN ALGORITHM");
            abort();
    }
}

size_t get_key_size(enum algorithms alg) {
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

bool simpleSHA256(void* input, unsigned long length, unsigned char* md)
{
    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, input, length))
        return false;

    if(!SHA256_Final(md, &context))
        return false;

    return true;
}



int encrypt(unsigned char *plaintext, char* password, unsigned char* ciphertext, enum modes mode, enum algorithms algorithm) {
    // Generate the key from the password
    size_t key_size_in_bits = get_key_size(algorithm);

    uint8_t key[key_size_in_bits / 8];

    // Sha definition
    unsigned char md[SHA256_DIGEST_LENGTH]; // 32 bytes
    if(!simpleSHA256(password, strlen(password), md)) {
        printf("There was an error calculating the key from the password");
        abort();
    }
    // printf("hash: %s\n", md);
    
    // Copy to our key only the N bits necessary for our algorithm
    memcpy(key, md, key_size_in_bits / 8);
    printf("Key: ");
    print_hash_binary(key);
    cipherFunction cipherFunctionPtr = getEncriptionFunctionPtr(algorithm, mode);


    // Generate IV
    // Todo: Generate random IV according to algorithm
    size_t iv_size_in_bits = get_iv_size(algorithm);
    unsigned char iv[iv_size_in_bits / 8];
    memset(iv,0,iv_size_in_bits/ 8);

    /* A 256 bit key */
    unsigned char *key2 = (unsigned char *)"01234567890123456789012345678901";

    /* A 128 bit IV */
    unsigned char *iv2 = (unsigned char *)"0123456789012345";

    int cipher_len = _encrypt(plaintext, strlen((char *)plaintext), key2, iv2, ciphertext, cipherFunctionPtr);
    return cipher_len;
}


