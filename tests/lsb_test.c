#include <testing_suite.h>
#include <lsb.h>
#include <payload.h>
#include <stddef.h>
#include <stdio.h>

void lsb_creation_test_1();
void lsb_creation_test_4();
void injection_test_1();

int main(){
    create_suite("LSB suite");
    add_test(lsb_creation_test_1);
    add_test(injection_test_1);
    run_suite();
    clear_suite();
}

void lsb_creation_test_1(){
    int size = 8, asserts = 0;
    uint8_t carrier[size];
    lsb l = create_lsb(1, (uint8_t *) carrier, size);
    asserts += l->n == 1;
    asserts += (uint8_t *) l->carrier ==  (uint8_t * )&carrier;
                asserts += l->counter == 0;
                asserts += l->size == 8;
                asserts += l->mask == 0x1;
    assert_true(asserts == 5);
}

void injection_test_1(){
    int size = 8, ret = 0;
    uint8_t carrier[size], injection = 1;
    for(int i = 0; i < size; i++) carrier[i] = 0;
    lsb l1 = create_lsb(1, (uint8_t *) carrier, size);
    inject_bit(l1, injection, 0);
    for(int i = 1; i < size; i++){
        ret += (carrier[i] == 0)? 1 : 0;
    }
    ret += carrier[0] == 1;
    assert_true(ret == size);
}
