#include <lsb.h>
#include <math.h>
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
void injection_test_15();
void injection_test_16();
void injection_test_17();
void injection_test_18();
void injection_test_19();
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
  add_test(injection_test_15);
  add_test(injection_test_16);
  add_test(injection_test_17);
  add_test(injection_test_18);
  add_test(injection_test_19);
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
  asserts += l->shift_val == 7;
  asserts += l->c_mask == 0x01;
  asserts += l->i_mask == 0x80;
  assert_true(asserts == 9);
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
  asserts += l->shift_val == 4;
  asserts += l->c_mask == 0x0F;
  asserts += l->i_mask == 0xF0;
  destroy_lsb(l);
  assert_true(asserts == 9);
}

void injection_test_1() {
  int size = 1, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  inject_bit(l, injection, 7);
  ret += carrier[0] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_2() {
  int size = 1, ret = 0;
  uint8_t original_bit = 0, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, 1, 0);
  inject_bit(l, injection, 7);
  ret += carrier[0] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_3() {
  int size = 1, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, 1, 0);
  inject_bit(l, injection, 7);
  ret += carrier[0] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_4() {
  int size = 1, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, 1, 0);
  inject_bit(l, injection, 7);
  ret += carrier[0] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_5() {
  int size = 4, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++) ret += carrier[i] == original_bit;
  ret += carrier[size - 1] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_6() {
  int size = 8, ret = 0;
  uint8_t original_bit = 0, injection = 0x01;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++) ret += carrier[i] == original_bit;
  ret += carrier[size - 1] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_7() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++)
    ret += carrier[i] == injection;  // caso especial
  ret += carrier[size - 1] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_8() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++) ret += carrier[i] == 0;  // caso especial
  ret += carrier[size - 1] == injection;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_9() {
  int size = 8, ret = 0;
  uint8_t original_bit = 0, injection = 0xa0;  // a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  ret += carrier[0] == 1;
  ret += carrier[1] == 0;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
  ret += carrier[4] == 0;
  ret += carrier[5] == 0;
  ret += carrier[6] == 0;
  ret += carrier[7] == 0;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_10() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 0xa0;  // a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  ret += carrier[0] == 1;
  ret += carrier[1] == 0;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
ret += carrier[4] == 0;
  ret += carrier[5] == 0;
  ret += carrier[6] == 0;
  ret += carrier[7] == 0;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_11() {
  int size = 8, ret = 0;
  uint8_t original_bit = 0, injection = 0xe0;  // a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  ret += carrier[0] == 1;
  ret += carrier[1] == 1;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
ret += carrier[4] == 0;
  ret += carrier[5] == 0;
  ret += carrier[6] == 0;
  ret += carrier[7] == 0;

  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_12() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 0xe0;  // a = 1010
  uint8_t carrier[size];
  carrier[0] = original_bit;
  for (int i = 0; i < size; i++) carrier[i] = original_bit;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  ret += carrier[0] == 1;
  ret += carrier[1] == 1;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
ret += carrier[4] == 0;
  ret += carrier[5] == 0;
  ret += carrier[6] == 0;
  ret += carrier[7] == 0;

  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_13() {
  int size = 8, ret = 0;
  uint8_t injection = 0x20;
  uint8_t carrier[size];
  // byte original: 0101
  carrier[0] = carrier[2] = 0;
  carrier[1] = carrier[3] = 1;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  ret += carrier[0] == 0;
  ret += carrier[1] == 0;
  ret += carrier[2] == 1;
  ret += carrier[3] == 0;
ret += carrier[4] == 0;
  ret += carrier[5] == 0;
  ret += carrier[6] == 0;
  ret += carrier[7] == 0;

  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_14() {
  int size = 8, ret = 0;
  uint8_t injection = 0xF0;
  uint8_t carrier[size];
  // byte original: 1101
  carrier[0] = carrier[1] = carrier[3] = 1;
  carrier[2] = 0;
  lsb l = create_lsb(1, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * (l->n));
  ret += carrier[0] == 1;
  ret += carrier[1] == 1;
  ret += carrier[2] == 1;
  ret += carrier[3] == 1;
ret += carrier[4] == 0;
  ret += carrier[5] == 0;
  ret += carrier[6] == 0;
  ret += carrier[7] == 0;

  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_15() {
  int size = 2, ret = 0;
  uint8_t injection = 0xFF;
  uint8_t carrier[size];
  carrier[0] = carrier[1] = 0;
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection,i * l->n);
  ret += carrier[0] == 0xF;
  ret += carrier[1] == 0xF;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_16() {
  int size = 2, ret = 0;
  uint8_t injection = 0x30;
  uint8_t carrier[size];
  carrier[0] = carrier[1] = 0;
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * l->n);
  ret += carrier[0] == 3;
  ret += carrier[1] == 0;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_17() {
  int size = 2, ret = 0;
  uint8_t injection = 0x0a; // a = 1010; 10 = 2
  uint8_t carrier[size];
  carrier[0] = carrier[1] = 0;
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * l->n);
  ret += carrier[0] == 0;
  ret += carrier[1] == 0xa;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_18() {
  int size = 2, ret = 0;
  uint8_t injection = 0xb0;
  uint8_t carrier[size];
  carrier[0] = carrier[1] = 0;
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * l->n);
  ret += carrier[0] == 0xb;
  ret += carrier[1] == 0;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_19() {
  int size = 2, ret = 0;
  uint8_t injection = 0xb0;
  uint8_t carrier[size];
  carrier[0] = 1;
  carrier[1] = 0;
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * l->n);
  ret += carrier[0] == 0xb;
  ret += carrier[1] == 0;
  destroy_lsb(l);
  assert_true(ret == size);
}

void injection_test_20() {
  int size = 2, ret = 0;
  uint8_t injection = 0xd;
  uint8_t carrier[size];
  carrier[0] = 0x8;
  carrier[1] = 0xb;
  lsb l = create_lsb(4, (uint8_t *)carrier, size, size, 0);
  for (int i = 0; i < size; i++) inject_bit(l, injection, i * l->n);
  ret += carrier[0] == 0xb;
  ret += carrier[1] == 0xa;
  destroy_lsb(l);
  assert_true(ret == size);
}

void worker_lbs_steg_test_1() {
  int size = 4;
  uint8_t carrier[size], content = 0xa;  // bits 1010
  for (int i = 0; i < size; i++) carrier[i] = 0;
  payload p = create_payload(&content, sizeof(content));
  lsb l = create_lsb(1, carrier, size, size, 1);
  worker_lsb_steg(l, p, size);
  destroy_lsb(l);
  destroy_payload(p);
}
