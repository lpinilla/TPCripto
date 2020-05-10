#include <encript.h>
#include <stdio.h>
#include <testing_suite.h>
#include <string.h>
#include <unistd.h> 

void sha256_test();

int main() {
  create_suite("Encription test");
  add_test(sha256_test);
  run_suite();
  clear_suite();
}


void sha256_test() {
    char* str = "hello world";
    unsigned char  md[32];
    if (!simpleSHA256(str, strlen(str), md)) {
        assert_true(1== 0);
    }

    // Aca un test podria ser comparar la salida de esta funcion con la de llamarlo por bash

    print_hash_binary(md);

    assert_true(1==1);
}