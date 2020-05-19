#include <encrypt.h>
#include <stdio.h>
#include <string.h>
#include <testing_suite.h>
#include <unistd.h>

void encrypt_decrypt_test();
void aes256_cbc_test();
void aes192_cbc_test();
void aes128_cbc_test();
void des_cbc_test();

void aes256_ecb_test();
void aes192_ecb_test();
void aes128_ecb_test();
void des_ecb_test();

void aes256_cfb_test();
void aes192_cfb_test();
void aes128_cfb_test();
void des_cfb_test();

void aes256_ofb_test();
void aes192_ofb_test();
void aes128_ofb_test();
void des_ofb_test();

int i = 0;
int main() {
  create_suite("Encription test");
  add_named_test(aes256_ecb_test, "aes256_ecb_test");
  add_named_test(aes192_ecb_test, "aes192_ecb_test");
  add_named_test(aes128_ecb_test, "aes128_ecb_test");
  add_named_test(des_ecb_test, "des_ecb_test");

  add_named_test(aes256_cfb_test, "aes256_cfb_test");
  add_named_test(aes192_cfb_test, "aes192_cfb_test");
  add_named_test(aes128_cfb_test, "aes128_cfb_test");
  add_named_test(des_cfb_test, "des_cfb_test");

  add_named_test(aes256_ofb_test, "aes256_ofb_test");
  add_named_test(aes192_ofb_test, "aes192_ofb_test");
  add_named_test(aes128_ofb_test, "aes128_ofb_test");
  add_named_test(des_ofb_test, "des_ofb_test");

  add_named_test(aes256_cbc_test, "aes256_cbc_test");
  add_named_test(aes192_cbc_test, "aes192_cbc_test"); // Falla
  add_named_test(aes128_cbc_test, "aes128_cbc_test"); // Falla
  add_named_test(des_cbc_test, "des_cbc_test");
  run_suite();
  clear_suite();
}

void encrypt_decrypt_test(enum algorithms algorithm, enum modes mode) {
    char * plain = "hola, me llamo es brian";
    char * password = "hello";

  
    // Aca se va a poner el texto cifrado
    char * cipher = malloc(2048);
    /// Aca se va a poner el texto descifrado
    char * unsciphered = malloc(2048);
    int cipher_len = encrypt((unsigned char *)plain, password, (unsigned char *) cipher, mode, algorithm);
    int decrypt_len = decrypt((unsigned char *)unsciphered, password, (unsigned char *)cipher, cipher_len, mode, algorithm);
    assert_false(memcmp(plain, unsciphered, decrypt_len));
    free(cipher);
    free(unsciphered);
}


// Test Mode CBC
void aes256_cbc_test() {
  encrypt_decrypt_test(aes256, cbc);
}

void aes192_cbc_test() {
  encrypt_decrypt_test(aes192, cbc);
}

void aes128_cbc_test() {
  encrypt_decrypt_test(aes128, cbc);
}

void des_cbc_test() {
  encrypt_decrypt_test(des, cbc);
}


// Test Mode ECB
void aes256_ecb_test() {
  encrypt_decrypt_test(aes256, ecb);
}

void aes192_ecb_test() {
  encrypt_decrypt_test(aes192, ecb);
}

void aes128_ecb_test() {
  encrypt_decrypt_test(aes128, ecb);
}

void des_ecb_test() {
  encrypt_decrypt_test(des, ecb);
}



// Test Mode CFB
void aes256_cfb_test() {
  encrypt_decrypt_test(aes256, cfb);
}

void aes192_cfb_test() {
  encrypt_decrypt_test(aes192, cfb);
}

void aes128_cfb_test() {
  encrypt_decrypt_test(aes128, cfb);
}

void des_cfb_test() {
  encrypt_decrypt_test(des, cfb);
}

// Test Mode OFB
void aes256_ofb_test() {
  encrypt_decrypt_test(aes256, ofb);
}

void aes192_ofb_test() {
  encrypt_decrypt_test(aes192, ofb);
}

void aes128_ofb_test() {
  encrypt_decrypt_test(aes128, ofb);
}

void des_ofb_test() {
  encrypt_decrypt_test(des, ofb);
}