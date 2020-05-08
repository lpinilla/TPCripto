#include <lsb.h>
#include <payload.h>
#include <stddef.h>
#include <stdio.h>
#include <testing_suite.h>
#include <math.h>

void lsb_creation_test_1();
void lsb_creation_test_4();
void injection_test_1();
void injection_test_2();
void injection_test_3();
void injection_test_4();
void injection_test_5();
void injection_test_6();
void injection_test_7();
void injection_test_8();
void injection_test_9();
void injection_test_10();
void injection_test_11();
void injection_test_12();
void injection_test_13();
void injection_test_14();
void worker_lbs_steg_test_1();

int main() {
  create_suite("LSB suite");
  add_test(lsb_creation_test_1);
  add_test(lsb_creation_test_4);
  add_test(injection_test_1);
  add_test(injection_test_2);
  add_test(injection_test_3);
  add_test(injection_test_4);
  add_test(injection_test_5);
  add_test(injection_test_6);
  add_test(injection_test_7);
  add_test(injection_test_8);
  add_test(injection_test_9);
  add_test(injection_test_10);
  add_test(injection_test_11);
  add_test(injection_test_12);
  add_test(injection_test_13);
  add_test(injection_test_14);
  add_test(worker_lbs_steg_test_1);
  run_suite();
  clear_suite();
}

void lsb_creation_test_1() {
  int size = 8, asserts = 0;
  uint8_t carrier[size];
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size / 2, size / 2);
  asserts += l->n == 1;
  asserts += (uint8_t *)l->carrier == (uint8_t *)&carrier;
  asserts += l->counter == 0;
  asserts += l->c_size == 8;
  asserts += l->pixel_width == size / 2;
  asserts += l->pixel_height == size / 2;
  asserts += l->c_mask == 0x1;
  asserts += l->i_mask == 0x8;
  assert_true(asserts == 8);
}

void lsb_creation_test_4() {
  int size = 8, asserts = 0;
  uint8_t carrier[size];
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size / 2, size / 2);
  asserts += l->n == 4;
  asserts += (uint8_t *)l->carrier == (uint8_t *)&carrier;
  asserts += l->counter == 0;
  asserts += l->c_size == 8;
  asserts += l->pixel_width == size / 2;
  asserts += l->pixel_height == size / 2;
  asserts += l->c_mask == 0x3;
  asserts += l->i_mask == 0xc;
  destroy_lsb(l);
  assert_true(asserts == 8);
}


void injection_test_1() {
  int size = 1, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  inject_bit(l1, injection, 3);
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_2() {
  int size = 1, ret = 0;
  uint8_t original_bit = 0, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, 1, 0);
  inject_bit(l1, injection, 3);
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_3() {
  int size = 1, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, 1, 0);
  inject_bit(l1, injection, 3);
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_4() {
  int size = 1, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, 1, 0);
  inject_bit(l1, injection, 3);
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_5() {
  int size = 4, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  for(int i = 0; i < (size -1); i++) ret += carrier[i] == original_bit;
  ret += carrier[size-1] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_6() {
  int size = 4, ret = 0;
  uint8_t original_bit = 0, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  for(int i = 0; i < (size -1); i++) ret += carrier[i] == original_bit;
  ret += carrier[size-1] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_7() {
  int size = 4, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  for(int i = 0; i < (size -1); i++) ret += carrier[i] == injection; //caso especial
  ret += carrier[size-1] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_8() {
  int size = 4, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  for(int i = 0; i < (size -1); i++) ret += carrier[i] == 0; //caso especial
  ret += carrier[size-1] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_9() {
  int size = 4, ret = 0;
  uint8_t original_bit = 0, injection = 0xa; //a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  ret += carrier[0] == 1;
  ret += carrier[1] == 0;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_10() {
  int size = 4, ret = 0;
  uint8_t original_bit = 1, injection = 0xa; //a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  ret += carrier[0] == 1;
  ret += carrier[1] == 0;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_11() {
  int size = 4, ret = 0;
  uint8_t original_bit = 0, injection = 0xe; //a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  ret += carrier[0] == 1;
  ret += carrier[1] == 1;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_12() {
  int size = 4, ret = 0;
  uint8_t original_bit = 1, injection = 0xe; //a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for(int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  ret += carrier[0] == 1;
  ret += carrier[1] == 1;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_13() {
  int size = 4, ret = 0;
  uint8_t injection = 0x2;
  uint8_t carrier[size];
  //byte original: 0101
  carrier[0] = carrier[2] =  0;
  carrier[1] = carrier[3] = 1;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  ret += carrier[0] == 0;
  ret += carrier[1] == 0;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_14() {
  int size = 4, ret = 0;
  uint8_t injection = 0xF;
  uint8_t carrier[size];
  //byte original: 1101
  carrier[0] = carrier[1] = carrier[3] =  1;
  carrier[2] = 0;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for(int i = 0; i < size; i++) inject_bit(l1, injection, i);
  ret += carrier[0] == 1;
  ret += carrier[1] == 1;
  ret += carrier[2] == 1;
  ret += carrier[3] == 1;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void worker_lbs_steg_test_1(){
    int size = 4;
    uint8_t carrier[size], content = 0xa; // bits 1010
    for(int i = 0; i < size; i++) carrier[i] = 0;
    payload p = create_payload(&content, sizeof(content));
    lsb l = create_lsb(1, carrier, size, size, 1);
    worker_lsb_steg(l, p, size);
    destroy_lsb(l);
    destroy_payload(p);
}
