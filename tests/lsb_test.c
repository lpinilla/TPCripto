#include <lsb.h>
#include <payload.h>
#include <stddef.h>
#include <stdio.h>
#include <testing_suite.h>

void lsb_creation_test_1();
void lsb_creation_test_4();
void injection_test_1();
void injection_test_2();
void injection_test_3();
void injection_test_4();

int main() {
  create_suite("LSB suite");
  add_test(lsb_creation_test_1);
  add_test(lsb_creation_test_4);
  add_test(injection_test_1);
  add_test(injection_test_2);
  add_test(injection_test_3);
  add_test(injection_test_4);
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
  asserts += l->mask == 0x1;
  assert_true(asserts == 7);
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
  asserts += l->mask == 15;
  assert_true(asserts == 7);
}


void injection_test_1() {
  int size = 2, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carrier[size];
  for (long i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size / 2, size / 2);
  inject_bit(l1, injection, 0);
  for (int i = 1; i < size; i++) {
    ret += (carrier[i] == original_bit) ? 1 : 0;
  }
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_2() {
  int size = 2, ret = 0;
  uint8_t original_bit = 0, injection = 1;
  uint8_t carrier[size];
  for (long i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size / 2, size / 2);
  inject_bit(l1, injection, 0);
  for (int i = 1; i < size; i++) {
    ret += (carrier[i] == original_bit) ? 1 : 0;
  }
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_3() {
  int size = 2, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carrier[size];
  for (long i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size / 2, size / 2);
  inject_bit(l1, injection, 0);
  for (int i = 1; i < size; i++) {
    ret += (carrier[i] == original_bit) ? 1 : 0;
  }
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}

void injection_test_4() {
  int size = 2, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carrier[size];
  for (long i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l1 = create_lsb(1, (uint8_t *)carrier, size, size / 2, size / 2);
  inject_bit(l1, injection, 0);
  for (int i = 1; i < size; i++) {
    ret += (carrier[i] == original_bit) ? 1 : 0;
  }
  ret += carrier[0] == injection;
  destroy_lsb(l1);
  assert_true(ret == size);
}
