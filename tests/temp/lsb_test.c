#include <lsb.h>
#include <math.h>
#include <payload.h>
#include <carrier.h>
#include <stddef.h>
#include <stdio.h>
#include <jobs.h>
#include <testing_suite.h>
#include <pthread.h>

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
void worker_lbs_steg_test_2();
void worker_lbs_steg_test_3();
void worker_lbs_steg_test_4();
void worker_lbs_steg_test_5();
void worker_lbs_steg_test_6();
void worker_subroutine_test();
void thread_test();
void thread_test_2();
void thread_test_3();
void lsb_steg_test();
void lsb_steg_test_2();
void lsb_steg_test_3();
void lsb_steg_test_4();
void extract_byte_test();
void extract_byte_test_2();
void extract_byte_test_3();
void extract_byte_test_4();
void extract_payload_size_test();
void extract_payload_size_test_2();
void extract_payload_size_test_3();
void extract_payload_size_test_4();
void extract_payload_size_test_5();
void extract_payload_size_test_6();
void extract_payload_test();
void extract_payload_test_2();
void extract_payload_test_3();
void inject_lsbi_byte_test();
void inject_lsbi_byte_test_2();

int main() {
  create_suite("LSB suite");
  //add_test(lsb_creation_test_1);
  //add_test(lsb_creation_test_4);
  //add_test(injection_test_1);
  //add_test(injection_test_2);
  //add_test(injection_test_3);
  //add_test(injection_test_4);
  //add_test(injection_test_5);
  //add_test(injection_test_6);
  //add_test(injection_test_7);
  //add_test(injection_test_8);
  //add_test(injection_test_9);
  //add_test(injection_test_10);
  //add_test(injection_test_11);
  //add_test(injection_test_12);
  //add_test(injection_test_13);
  //add_test(injection_test_14);
  //add_test(injection_test_15);
  //add_test(injection_test_16);
  //add_test(injection_test_17);
  //add_test(injection_test_18);
  //add_test(injection_test_19);
  //add_test(worker_lbs_steg_test_1);
  //add_test(worker_lbs_steg_test_2);
  //add_test(worker_lbs_steg_test_3);
  //add_test(worker_lbs_steg_test_4);
  //add_test(worker_lbs_steg_test_5);
  //add_test(worker_lbs_steg_test_6);
  //add_named_test(worker_subroutine_test,NAME_OFF(worker_subroutine_test));
  //add_named_test(thread_test,NAME_OFF(thread_test));
  //add_named_test(thread_test_2,NAME_OFF(thread_test_2));
  //add_named_test(thread_test_3,NAME_OFF(thread_test_3));
  //add_named_test(lsb_steg_test, NAME_OFF(lsb_steg_test));
  //add_named_test(lsb_steg_test_2, NAME_OFF(lsb_steg_test_2));
  //add_named_test(lsb_steg_test_3, NAME_OFF(lsb_steg_test_3));
  //add_named_test(lsb_steg_test_4, NAME_OFF(lsb_steg_test_4));
  //add_named_test(extract_byte_test, NAME_OFF(extract_byte_test));
  //add_named_test(extract_byte_test_2, NAME_OFF(extract_byte_test_2));
  //add_named_test(extract_byte_test_3, NAME_OFF(extract_byte_test_3));
  //add_named_test(extract_byte_test_4, NAME_OFF(extract_byte_test_4));
  //add_named_test(extract_payload_size_test, NAME_OFF(extract_payload_size_test));
  //add_named_test(extract_payload_size_test_2, NAME_OFF(extract_payload_size_test_2));
  //add_named_test(extract_payload_size_test_3, NAME_OFF(extract_payload_size_test_3));
  //add_named_test(extract_payload_size_test_4, NAME_OFF(extract_payload_size_test_4));
  //add_named_test(extract_payload_size_test_5, NAME_OFF(extract_payload_size_test_5));
  //add_named_test(extract_payload_test, NAME_OFF(extract_payload_test));
  //add_named_test(extract_payload_test_2, NAME_OFF(extract_payload_test_2));
  //add_named_test(extract_payload_test_3, NAME_OFF(extract_payload_test_3));
    add_named_test(inject_lsbi_byte_test, NAME_OFF(inject_lsbi_byte_test));

    //add_named_test(inject_lsbi_byte_test_2, NAME_OFF(inject_lsbi_byte_test_2));

  run_suite();
  clear_suite();
}

void lsb_creation_test_1() {
  int asserts = 0;
  lsb l = create_lsb(1);
  asserts += l->n == 1;
  asserts += l->shift_val == 7;
  asserts += l->c_mask == 0x01;
  asserts += l->i_mask == 0x80;
  destroy_lsb(l);
  assert_true(asserts == 4);
}

void lsb_creation_test_4() {
  int asserts = 0;
  lsb l = create_lsb(4);
  asserts += l->n == 4;
  asserts += l->shift_val == 4;
  asserts += l->c_mask == 0x0F;
  asserts += l->i_mask == 0xF0;
  destroy_lsb(l);
  assert_true(asserts == 4);
}

void injection_test_1() {
  int size = 1, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carr[size];
  carr[0] = original_bit;
  carrier c = create_carrier(carr, size, size, 0);
  lsb l = create_lsb(1);
  inject_bit(l, c, injection, 7);
  ret += carr[0] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_2() {
  int size = 1, ret = 0;
  uint8_t original_bit = 0, injection = 1;
  uint8_t carr[size];
  carr[0] = original_bit;
  carrier c = create_carrier((uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(1);
  inject_bit(l, c, injection, 7);
  ret += carr[0] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_3() {
  int size = 1, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carr[size];
  carr[0] = original_bit;
  carrier c = create_carrier((uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(1);
  inject_bit(l, c, injection, 7);
  ret += carr[0] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_4() {
  int size = 1, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carr[size];
  carr[0] = original_bit;
  carrier c = create_carrier((uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(1);
  inject_bit(l, c, injection, 7);
  ret += carr[0] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_5() {
  int size = 4, ret = 0;
  uint8_t original_bit = 0, injection = 0;
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
   carrier c = create_carrier((uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++) ret += carr[i] == original_bit;
  ret += carr[size - 1] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_6() {
  int size = 8, ret = 0;
  uint8_t original_bit = 0, injection = 0x01;
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier((uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++) ret += carr[i] == original_bit;
  ret += carr[size - 1] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_7() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 0;
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++)
    ret += carr[i] == injection;  // caso especial
  ret += carr[size - 1] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_8() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 1;
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  for (int i = 0; i < (size - 1); i++) ret += carr[i] == 0;  // caso especial
  ret += carr[size - 1] == injection;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_9() {
  int size = 8, ret = 0;
  uint8_t original_bit = 0, injection = 0xa0;  // a = 1010
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  ret += carr[0] == 1;
  ret += carr[1] == 0;
  ret += carr[2] == 1;
  ret += carr[3] == 0;
  ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_10() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 0xa0;  // a = 1010
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  ret += carr[0] == 1;
  ret += carr[1] == 0;
  ret += carr[2] == 1;
  ret += carr[3] == 0;
ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_11() {
  int size = 8, ret = 0;
  uint8_t original_bit = 0, injection = 0xe0;  // a = 1010
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  ret += carr[0] == 1;
  ret += carr[1] == 1;
  ret += carr[2] == 1;
  ret += carr[3] == 0;
    ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_12() {
  int size = 8, ret = 0;
  uint8_t original_bit = 1, injection = 0xe0;  // a = 1010
  uint8_t carr[size];
  carr[0] = original_bit;
  for (int i = 0; i < size; i++) carr[i] = original_bit;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  ret += carr[0] == 1;
  ret += carr[1] == 1;
  ret += carr[2] == 1;
  ret += carr[3] == 0;
ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;

  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_13() {
  int size = 8, ret = 0;
  uint8_t injection = 0x20;
  uint8_t carr[size];
  // byte original: 0101
  carr[0] = carr[2] = 0;
  carr[1] = carr[3] = 1;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  ret += carr[0] == 0;
  ret += carr[1] == 0;
  ret += carr[2] == 1;
  ret += carr[3] == 0;
ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;
  destroy_lsb(l);
    destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_14() {
  int size = 8, ret = 0;
  uint8_t injection = 0xF0;
  uint8_t carr[size];
  // byte original: 1101
  carr[0] = carr[1] = carr[3] = 1;
  carr[2] = 0;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(1);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * (l->n));
  ret += carr[0] == 1;
  ret += carr[1] == 1;
  ret += carr[2] == 1;
  ret += carr[3] == 1;
    ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_15() {
  int size = 2, ret = 0;
  uint8_t injection = 0xFF;
  uint8_t carr[size];
  carr[0] = carr[1] = 0;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(4);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection,i * l->n);
  ret += carr[0] == 0xF;
  ret += carr[1] == 0xF;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_16() {
  int size = 2, ret = 0;
  uint8_t injection = 0x30;
  uint8_t carr[size];
  carr[0] = carr[1] = 0;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(4);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * l->n);
  ret += carr[0] == 3;
  ret += carr[1] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_17() {
  int size = 2, ret = 0;
  uint8_t injection = 0x0a; // a = 1010; 10 = 2
  uint8_t carr[size];
  carr[0] = carr[1] = 0;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(4);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * l->n);
  ret += carr[0] == 0;
  ret += carr[1] == 0xa;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_18() {
  int size = 2, ret = 0;
  uint8_t injection = 0xb0;
  uint8_t carr[size];
  carr[0] = carr[1] = 0;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(4);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * l->n);
  ret += carr[0] == 0xb;
  ret += carr[1] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_19() {
  int size = 2, ret = 0;
  uint8_t injection = 0xb0;
  uint8_t carr[size];
  carr[0] = 1;
  carr[1] = 0;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(4);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * l->n);
  ret += carr[0] == 0xb;
  ret += carr[1] == 0;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void injection_test_20() {
  int size = 2, ret = 0;
  uint8_t injection = 0xd;
  uint8_t carr[size];
  carr[0] = 0x8;
  carr[1] = 0xb;
  carrier c = create_carrier( (uint8_t *)carr, size, size, 1);
  lsb l = create_lsb(4);
  for (int i = 0; i < size; i++) inject_bit(l, c, injection, i * l->n);
  ret += carr[0] == 0xb;
  ret += carr[1] == 0xa;
  destroy_lsb(l);
  destroy_carrier(c);
  assert_true(ret == size);
}

void worker_lbs_steg_test_1() {
  int size = 8, ret = 0;
  uint8_t carr[size], content = 0x0a;  // bits 00001010
  for (int i = 0; i < size; i++) carr[i] = 0;
  payload p = create_payload(&content, size);
  carrier c = create_carrier( (uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(1);
  worker_lsb_steg(l, c, p, size);
  destroy_lsb(l);
  destroy_payload(p);
  destroy_carrier(c);
  ret += carr[0] == 0;
  ret += carr[1] == 0;
  ret += carr[2] == 0;
  ret += carr[3] == 0;
  ret += carr[4] == 1;
  ret += carr[5] == 0;
  ret += carr[6] == 1;
  ret += carr[7] == 0;
  assert_true(ret == size);
}

void worker_lbs_steg_test_2() {
  int size = 8, ret = 0;
  uint8_t carr[size], content = 0xa0;  // bits 10100000
  for (int i = 0; i < size; i++) carr[i] = 0;
  payload p = create_payload(&content, size);
  carrier c = create_carrier( (uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(1);
  worker_lsb_steg(l, c, p, size);
  destroy_lsb(l);
  destroy_payload(p);
  destroy_carrier(c);
  ret += carr[0] == 1;
  ret += carr[1] == 0;
  ret += carr[2] == 1;
  ret += carr[3] == 0;
  ret += carr[4] == 0;
  ret += carr[5] == 0;
  ret += carr[6] == 0;
  ret += carr[7] == 0;
  assert_true(ret == size);
}

void worker_lbs_steg_test_3() {
  int size = 8, ret = 0;
  uint8_t carr[size], content = 0xd8;
  for (int i = 0; i < size; i++) carr[i] = 0xF;
  payload p = create_payload(&content, size);
  carrier c = create_carrier( (uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(1);
  worker_lsb_steg(l, c, p, size);
  destroy_lsb(l);
  destroy_payload(p);
  destroy_carrier(c);
  ret += carr[0] == 0xf;
  ret += carr[1] == 0xf;
  ret += carr[2] == 0xe;
  ret += carr[3] == 0xf;
  ret += carr[4] == 0xf;
  ret += carr[5] == 0xe;
  ret += carr[6] == 0xe;
  ret += carr[7] == 0xe;
  assert_true(ret == size);
}

void worker_lbs_steg_test_4() {
  int size = 2, ret = 0;
  uint8_t carr[size], content = 0xd8;
  for (int i = 0; i < size; i++) carr[i] = 0xaa;
  payload p = create_payload(&content, size);
  carrier c = create_carrier( (uint8_t *)carr, size, 1, 1);
  lsb l = create_lsb(4);
  worker_lsb_steg(l, c, p, size);
  destroy_lsb(l);
  destroy_payload(p);
  destroy_carrier(c);
  ret += carr[0] == 0xad;
  ret += carr[1] == 0xa8;
  assert_true(ret == size);
}

void worker_lbs_steg_test_5() {
  int size = 4, ret = 0;
  uint8_t carr[size], injection[2];
  injection[0] = 0x8a;
  injection[1] = 0x3b;
  for (int i = 0; i < size; i++) carr[i] = 0x0;
  carrier c = create_carrier( (uint8_t *)carr, size/2, 1, 1);
  carrier c2 = create_carrier( (uint8_t *)carr + sizeof(uint8_t)* 2, size/2, 1, 1);
  lsb l = create_lsb(4);
  payload p = create_payload(injection, size / 2);
  payload p2 = create_payload(injection + sizeof(uint8_t), size / 2);
  worker_lsb_steg(l, c, p, size/2);
  worker_lsb_steg(l, c2, p2, size/2);
  destroy_lsb(l);
  destroy_payload(p);
  destroy_payload(p2);
  destroy_carrier(c);
  destroy_carrier(c2);
  ret += carr[0] == 0x08;
  ret += carr[1] == 0x0a;
  ret += carr[2] == 0x03;
  ret += carr[3] == 0x0b;
  assert_true(ret == size);
}

void worker_lbs_steg_test_6() {
  int size = 8, ret = 0;
  uint8_t carr[size], injection[4];
  injection[0] = 0x8a;
  injection[1] = 0x3b;
  injection[2] = 0x4c;
  injection[3] = 0x05;
  for (int i = 0; i < size; i++) carr[i] = 0xaa;
  lsb l = create_lsb(4);
carrier c = create_carrier( (uint8_t *)carr, size/2, 1, 1);
  carrier c2 = create_carrier( (uint8_t *)carr + sizeof(uint8_t)* 4, size/2, 1, 1);
  payload p = create_payload(injection, 2);
  payload p2 = create_payload(injection + sizeof(uint8_t) * 2, 2);
  worker_lsb_steg(l, c, p, size/2);
  worker_lsb_steg(l, c2, p2, size/2);
  destroy_lsb(l);
  destroy_payload(p);
  destroy_carrier(c);
  destroy_carrier(c2);
  ret += carr[0] == 0xa8;
  ret += carr[1] == 0xaa;
  ret += carr[2] == 0xa3;
  ret += carr[3] == 0xab;
  ret += carr[4] == 0xa4;
  ret += carr[5] == 0xac;
  ret += carr[6] == 0xa0;
  ret += carr[7] == 0xa5;
  assert_true(ret == size);
}

void worker_subroutine_test(){
    int carr_size = 8, inj_size = 1, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0xaa;
    lsb l = create_lsb(1);
    carrier c = create_carrier( (uint8_t *)carr, carr_size, carr_size, 1);
    payload p = create_payload(injection, inj_size);
    t_routine_args args = { .l = l, .c = c, .p = p, .n_of_pixels = c->pixel_width };
    worker_sub_routine( (void *) &args);
    ret += carr[0] == 0x1;
    ret += carr[1] == 0x0;
    ret += carr[2] == 0x1;
    ret += carr[3] == 0x0;
    ret += carr[4] == 0x1;
    ret += carr[5] == 0x0;
    ret += carr[6] == 0x1;
    ret += carr[7] == 0x0;
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(ret == inj_size * 8);
}

void thread_test(){
    int carr_size = 8, inj_size = 1, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    pthread_t main_thread;
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0xaa;
    lsb l = create_lsb(1);
    carrier c = create_carrier( (uint8_t *)carr, carr_size, carr_size, 1);
    payload p = create_payload(injection, inj_size);
    t_routine_args args = { .l = l, .c = c, .p = p, .n_of_pixels = c->pixel_width };
    pthread_create(&main_thread, NULL, worker_sub_routine, (void *) &args);
    pthread_join(main_thread, NULL);
    ret += carr[0] == 0x1;
    ret += carr[1] == 0x0;
    ret += carr[2] == 0x1;
    ret += carr[3] == 0x0;
    ret += carr[4] == 0x1;
    ret += carr[5] == 0x0;
    ret += carr[6] == 0x1;
    ret += carr[7] == 0x0;
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(ret == inj_size * 8);
}

void thread_test_2(){ //FIXME
    int carr_size = 8, inj_size = 1, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    pthread_t main_thread;
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0xaa;
    lsb l = create_lsb(1);
    lsb l2 = create_lsb(1);
    carrier c = create_carrier((uint8_t *)carr, carr_size, carr_size / 2, 1);
    carrier c2 = create_carrier((uint8_t *)carr + sizeof(uint8_t) * carr_size / 2, carr_size, carr_size / 2, 1);
    payload p = create_payload(injection, inj_size);
    payload p2 = create_payload(injection + sizeof(uint8_t) * inj_size / 2 , inj_size);
    t_routine_args args = { .l = l, .c = c, .p = p, .n_of_pixels = c->pixel_width };
    t_routine_args args2 = { .l = l2, .c = c2, .p = p2, .n_of_pixels = c->pixel_width};
    pthread_create(&main_thread, NULL, worker_sub_routine, (void *) &args);
    pthread_create(&main_thread, NULL, worker_sub_routine, (void *) &args2);
    pthread_join(main_thread, NULL);
    ret += carr[0] == 0x1;
    ret += carr[1] == 0x0;
    ret += carr[2] == 0x1;
    ret += carr[3] == 0x0;
    ret += carr[4] == 0x1;
    ret += carr[5] == 0x0;
    ret += carr[6] == 0x1;
    ret += carr[7] == 0x0;
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l2);
    destroy_carrier(c2);
    destroy_payload(p2);
    assert_true(ret == carr_size);
}

void thread_test_3(){
    int carr_size = 16, inj_size = 2, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    pthread_t main_thread;
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0x97;
    injection[1] = 0x31;
    lsb l = create_lsb(1);
    lsb l2 = create_lsb(1);
    carrier c = create_carrier((uint8_t *)carr, carr_size / 2, carr_size / 2, 1);
    carrier c2 = create_carrier((uint8_t *)carr + sizeof(uint8_t) * carr_size /2, carr_size / 2, carr_size/2, 1);
    payload p = create_payload(injection, inj_size);
    payload p2 = create_payload(injection + sizeof(uint8_t) * inj_size / 2 , inj_size);
    t_routine_args args = { .l = l, .c = c, .p = p, .n_of_pixels = c->pixel_width };
    t_routine_args args2 = { .l = l2, .c = c2, .p = p2, .n_of_pixels = c->pixel_width};
    pthread_create(&main_thread, NULL, worker_sub_routine, (void *) &args);
    pthread_create(&main_thread, NULL, worker_sub_routine, (void *) &args2);
    pthread_join(main_thread, NULL);
    ret += carr[0] == 0x1;
    ret += carr[1] == 0x0;
    ret += carr[2] == 0x0;
    ret += carr[3] == 0x1;
    ret += carr[4] == 0x0;
    ret += carr[5] == 0x1;
    ret += carr[6] == 0x1;
    ret += carr[7] == 0x1;
    ret += carr[8] == 0x0;
    ret += carr[9] == 0x0;
    ret += carr[10] == 0x1;
    ret += carr[11] == 0x1;
    ret += carr[12] == 0x0;
    ret += carr[13] == 0x0;
    ret += carr[14] == 0x0;
    ret += carr[15] == 0x1;
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l2);
    destroy_carrier(c2);
    destroy_payload(p2);
    assert_true(ret == carr_size);
}

void lsb_steg_test(){
    int carr_size = 24, inj_size = 2, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    lsb l = create_lsb(1);
    injection[0] = 0x35;
    injection[1] = 0xba;
    carrier c = create_carrier( (uint8_t *)carr, carr_size, 8, 3);
    payload p = create_payload( (uint8_t *)injection, inj_size);
    lsb_steg(l, c, p);
    ret += carr[0] == 0;
    ret += carr[1] == 0;
    ret += carr[2] == 1;
    ret += carr[3] == 1;
    ret += carr[4] == 0;
    ret += carr[5] == 1;
    ret += carr[6] == 0;
    ret += carr[7] == 1;
    ret += carr[8] == 1;
    ret += carr[9] == 0;
    ret += carr[10] == 1;
    ret += carr[11] == 1;
    ret += carr[12] == 1;
    ret += carr[13] == 0;
    ret += carr[14] == 1;
    ret += carr[15] == 0;
    ret += carr[16] == 0;
    ret += carr[17] == 0;
    ret += carr[18] == 0;
    ret += carr[19] == 0;
    ret += carr[20] == 0;
    ret += carr[21] == 0;
    ret += carr[22] == 0;
    ret += carr[23] == 0;
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    assert_true(ret == carr_size);
}

void lsb_steg_test_2(){
    int carr_size = 20, inj_size = 2, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0x35;
    injection[1] = 0xba;
    carrier c = create_carrier( (uint8_t *)carr, carr_size, 4, 5);
    payload p = create_payload( (uint8_t *)injection, inj_size);
    lsb l = create_lsb(1);
    lsb_steg(l, c, p);
    ret += carr[0] == 0;
    ret += carr[1] == 0;
    ret += carr[2] == 1;
    ret += carr[3] == 1;
    ret += carr[4] == 0;
    ret += carr[5] == 1;
    ret += carr[6] == 0;
    ret += carr[7] == 1;
    ret += carr[8] == 1;
    ret += carr[9] == 0;
    ret += carr[10] == 1;
    ret += carr[11] == 1;
    ret += carr[12] == 1;
    ret += carr[13] == 0;
    ret += carr[14] == 1;
    ret += carr[15] == 0;
    ret += carr[16] == 0;
    ret += carr[17] == 0;
    ret += carr[18] == 0;
    ret += carr[19] == 0;
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    assert_true(ret == carr_size);
}

void lsb_steg_test_3(){
    int carr_size = 20, inj_size = 2, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0x35;
    injection[1] = 0xba;
    carrier c = create_carrier( (uint8_t *)carr, carr_size, 4, 5);
    payload p = create_payload( (uint8_t *)injection, inj_size);
    lsb l = create_lsb(4);
    lsb_steg(l, c, p);
    ret += carr[0] == 0x3;
    ret += carr[1] == 0x5;
    ret += carr[2] == 0xb;
    ret += carr[3] == 0xa;
    ret += carr[4] == 0;
    ret += carr[5] == 0;
    ret += carr[6] == 0;
    ret += carr[7] == 0;
    ret += carr[8] == 0;
    ret += carr[9] == 0;
    ret += carr[10] == 0;
    ret += carr[11] == 0;
    ret += carr[12] == 0;
    ret += carr[13] == 0;
    ret += carr[14] == 0;
    ret += carr[15] == 0;
    ret += carr[16] == 0;
    ret += carr[17] == 0;
    ret += carr[18] == 0;
    ret += carr[19] == 0;
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    assert_true(ret == carr_size);
}

void lsb_steg_test_4(){
    int carr_size = 20, inj_size = 2, ret = 0;
    uint8_t carr[carr_size], injection[inj_size];
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    injection[0] = 0x35;
    injection[1] = 0xba;
    carrier c = create_carrier( (uint8_t *)carr, carr_size, 10, 2);
    payload p = create_payload( (uint8_t *)injection, inj_size);
    lsb l = create_lsb(4);
    lsb_steg(l, c, p);
    ret += carr[0] == 0x3;
    ret += carr[1] == 0x5;
    ret += carr[2] == 0xb;
    ret += carr[3] == 0xa;
    ret += carr[4] == 0;
    ret += carr[5] == 0;
    ret += carr[6] == 0;
    ret += carr[7] == 0;
    ret += carr[8] == 0;
    ret += carr[9] == 0;
    ret += carr[10] == 0;
    ret += carr[11] == 0;
    ret += carr[12] == 0;
    ret += carr[13] == 0;
    ret += carr[14] == 0;
    ret += carr[15] == 0;
    ret += carr[16] == 0;
    ret += carr[17] == 0;
    ret += carr[18] == 0;
    ret += carr[19] == 0;
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    assert_true(ret == carr_size);
}

void extract_byte_test(){
    int carr_size = 8;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, carr_size, 1);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[carr_size - 1] = 1;
    ret = extract_byte(l, c);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_byte_test_2(){
    int carr_size = 8;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, carr_size, 1);
    lsb l = create_lsb(4);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[1] = 1;
    ret = extract_byte(l, c);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_byte_test_3(){
    int carr_size = 8;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, carr_size, 1);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[0] = 1;
    carr[carr_size -1] = 1;
    carr[carr_size -2] = 1;
    ret = extract_byte(l, c);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 0x83);
}

void extract_byte_test_4(){
    int carr_size = 8;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, carr_size, 1);
    lsb l = create_lsb(4);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[0] = 4;
    carr[1] = 0x0b;
    ret = extract_byte(l, c);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 0x4b);
}

void extract_payload_size_test(){
    int carr_size = 32;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, carr_size, 1);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1;
    ret = extract_payload_size(l, c, 0);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_payload_size_test_2(){
    int carr_size = 32;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, carr_size, 1);
    lsb l = create_lsb(4);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1;
    ret = extract_payload_size(l, c, 0);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_payload_size_test_3(){
    int carr_size = 32;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1;
    ret = extract_payload_size(l, c, 0);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_payload_size_test_4(){
    int carr_size = 32;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    lsb l = create_lsb(4);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1;
    ret = extract_payload_size(l, c, 0);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_payload_size_test_5(){
    int carr_size = 32;
    uint8_t carr[carr_size];
    uint32_t ret = 0;
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[17] = 1;
    carr[22] = 1;
    carr[24] = 1;
    carr[25] = 1;
    carr[27] = 1;
    carr[28] = 1;
    carr[29] = 1;
    carr[30] = 1;
    for(int i = 0; i < carr_size; i++){
        printf("%d ", carr[i]);
    }
    printf("\n");
    ret = extract_payload_size(l, c, 0);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 17118);
}

void extract_payload_size_test_6(){
    int carr_size = 32;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    lsb l = create_lsb(4);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1;
    ret = extract_payload_size(l, c, 0);
    destroy_lsb(l);
    destroy_carrier(c);
    assert_true(ret == 1);
}

void extract_payload_test(){
    int carr_size = 40;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1; //tamaño = 1
    carr[carr_size - 1] = 1;
    payload p = extract_payload(l, c);
    ret = *p->content;
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(ret == 1);
}

void extract_payload_test_2(){
    int carr_size = 40;
    uint8_t carr[carr_size], ret = 0;
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    lsb l = create_lsb(1);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 1] = 1; //tamaño = 1
    carr[carr_size - 1 - 7] = 1;
    carr[carr_size - 1] = 1;
    payload p = extract_payload(l, c);
    ret = *p->content;
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(ret == 0x81);
}

void extract_payload_test_3(){
    lsb l = create_lsb(1);
    int inj_size = 2;
    //int carr_size = 32 * inj_size + (BYTE_SIZE/ l->n) * inj_size;
    int carr_size = 32 +  8 * 2;
    uint8_t carr[carr_size], ret[inj_size];
    carrier c = create_carrier(carr, carr_size, 1, carr_size);
    for(int i = 0; i < carr_size; i++) carr[i] = 0;
    for(int i = 0; i < inj_size; i++) ret[i] = 0;
    carr[(4 * BYTE_SIZE/ l->n) - 2] = 1; //tamaño = 2
    carr[carr_size - 1] = 0;
    carr[carr_size - 2] = 1;
    carr[carr_size - 3] = 0;
    carr[carr_size - 4] = 1;
    carr[carr_size - 5] = 0;
    carr[carr_size - 6] = 0;
    carr[carr_size - 7] = 0;
    carr[carr_size - 8] = 0;
    carr[carr_size - 9] = 1;
    carr[carr_size - 10] = 0;
    carr[carr_size - 11] = 1;
    carr[carr_size - 12] = 0;
    carr[carr_size - 13] = 0;
    carr[carr_size - 14] = 1;
    carr[carr_size - 15] = 1;
    carr[carr_size - 16] = 1;
    payload p = extract_payload(l, c);
    for(int i = 0; i < inj_size; i++) ret[i] = p->content[i];
    destroy_lsb(l);
    destroy_carrier(c);
    destroy_payload(p);
    assert_true(ret[0] == 0xe5 && ret[1] == 0x0a);
}
<<<<<<< Updated upstream

void inject_lsbi_byte_test(){
    int arr_size = 16;
    uint8_t arr[arr_size];
    uint8_t payload[2] = {0xff, 0x55};
    int hop = 2, ret = 0;
    int expected[16] ={1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1};
    memset(arr, 0, arr_size);
    lsb l = create_lsb(1);
    carrier c = create_carrier((uint8_t *) arr, arr_size, 4, 4);
    inject_lsbi_byte(l, c, payload[0], hop);
    inject_lsbi_byte(l, c, payload[1], hop);
    for(int i = 0; i < arr_size; i++) ret += arr[i] == expected[i];
    destroy_lsb(l);
    destroy_carrier(c);
    assert_equals(&ret, &arr_size, sizeof(int));
}

//no anda
void inject_lsbi_byte_test_2(){
    int arr_size = 24;
    uint8_t arr[arr_size];
    uint8_t payload[3] = {0xff, 0x55, 0x3c};
    int hop = 2, ret = 0;
    int expected[24] = {
        1, 0, 1, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 0, 1, 0,
        1, 0, 1, 0,
        1, 0, 1, 0,
    };
    memset(arr, 0, arr_size);
    lsb l = create_lsb(1);
    carrier c = create_carrier((uint8_t *) arr, arr_size, 6, 4);
    inject_lsbi_byte(l, c, payload[0], hop);
    printf("counter : %d \n", c->counter);
    inject_lsbi_byte(l, c, payload[1], hop);
    printf("counter : %d \n", c->counter);
    inject_lsbi_byte(l, c, payload[2], hop);
    printf("counter : %d \n", c->counter);
    for(int i = 0; i < arr_size; i++){
        if(i != 0 && i % 4 == 0) printf("\n");
        printf("%d ", arr[i]);
        ret += arr[i] == expected[i];
    }
    printf("\n");
    destroy_lsb(l);
    destroy_carrier(c);
    printf("%d \n", ret);
    assert_equals(&ret, &arr_size, sizeof(int));
}
||||||| merged common ancestors
=======

void inject_lsbi_byte_test(){
    int arr_size = 16;
    uint8_t arr[arr_size];
    uint8_t payload[2] = {0xff, 0x55};
    int hop = 2, ret = 0;
    int expected[16] ={1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1};
    memset(arr, 0, arr_size);
    lsb l = create_lsb(1);
    carrier c = create_carrier((uint8_t *) arr, arr_size, 4, 4);
    inject_lsbi_byte(l, c, payload[0], hop);
    inject_lsbi_byte(l, c, payload[1], hop);
    for(int i = 0; i < arr_size; i++) ret += arr[i] == expected[i];
    destroy_lsb(l);
    destroy_carrier(c);
    assert_equals(&ret, &arr_size, sizeof(int));
}

//no anda
void inject_lsbi_byte_test_2(){
    int arr_size = 24;
    uint8_t arr[arr_size];
    uint8_t payload[3] = {0xff, 0x55, 0x3c};
    int hop = 2, ret = 0;
    int expected[24] = {
        1, 0, 1, 0,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 0, 1, 0,
        1, 0, 1, 0,
        1, 0, 1, 0,
    };
    memset(arr, 0, arr_size);
    lsb l = create_lsb(1);
    carrier c = create_carrier((uint8_t *) arr, arr_size, 6, 4);
    inject_lsbi_byte(l, c, payload[0], hop);
    printf("counter : %ld \n", c->counter);
    inject_lsbi_byte(l, c, payload[1], hop);
    printf("counter : %ld \n", c->counter);
    inject_lsbi_byte(l, c, payload[2], hop);
    printf("counter : %ld \n", c->counter);
    for(int i = 0; i < arr_size; i++){
        if(i != 0 && i % 4 == 0) printf("\n");
        printf("%d ", arr[i]);
        ret += arr[i] == expected[i];
    }
    printf("\n");
    destroy_lsb(l);
    destroy_carrier(c);
    printf("%d \n", ret);
    assert_equals(&ret, &arr_size, sizeof(int));
}
>>>>>>> Stashed changes
