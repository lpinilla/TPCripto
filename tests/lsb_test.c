#include <testing_suite.h>
#include <lsb.h>
#include <payload.h>
#include <stddef.h>

void lsb_creation_test();
void lsb_destruction_test();
void injection_test_1();

int main(){
    create_suite("LSB suite");
    //add_test(injection_test_1);
    run_suite();
    clear_suite();
}

void injection_test_1(){
    int size = 8;
    uint8_t carrier[size], injection = 1;
    for(int i = 0; i < size; i++) carrier[i] = 0;
    lsb l1 = create_lsb(1, (uint8_t **) &carrier, size);
    inject_bit(l1, injection, 0);
    assert_true(injection == carrier[7]);
}
