#include <testing_suite.h>
#include <jobs.h>
#include <lsb.h>
#include <carrier.h>
#include <payload.h>
#include <stddef.h>
#include <math.h>


long create_test(long size, long inj_size, int n, long width, long height);
void job_division_test();
void job_division_test_2();
void job_division_test_3();
void job_division_test_4();
void job_division_test_5();
void job_division_test_6();
void job_division_test_7();
void job_division_test_8();
void job_division_test_9();
void job_division_test_10();
void job_division_test_11();

int main(){
    create_suite("Jobs Suite");
    add_named_test(job_division_test, "job_division_test");
    add_named_test(job_division_test_2, NAME_OFF(job_division_test_2));
    add_named_test(job_division_test_3, NAME_OFF(job_division_test_3));
    add_test(job_division_test_4);
    add_test(job_division_test_5);
    add_test(job_division_test_6);
    add_named_test(job_division_test_7, NAME_OFF(job_division_test_7));
    add_named_test(job_division_test_8, NAME_OFF(job_division_test_8));
    add_named_test(job_division_test_9, NAME_OFF(job_division_test_9));
    add_named_test(job_division_test_10, NAME_OFF(job_division_test_10));
    add_named_test(job_division_test_11, NAME_OFF(job_division_test_11));
    run_suite();
    clear_suite();
}


void print_test(char * test);

void job_division_test(){
    long size = 8;
    long asst = create_test(size, 1, 1, size, 1);
    assert_true(1 == asst);
}


void job_division_test_2(){
    long size = 8;
    long asst = create_test(size, 1, 4, size, 1);
    assert_true(1 == asst);
}

void job_division_test_3(){
    long size = 16, inj_size = 2;
    long asst = create_test(size, inj_size, 1, size / 2, 2);
    assert_true(2 == asst);
}

void job_division_test_4(){
    long size = 16, inj_size = 2;
    long asst = create_test(size, inj_size, 4, size / 2, 2);
    assert_true(1 == asst);
}

void job_division_test_5(){
    long size = 8, inj_size = 1;
    long asst = create_test(size, inj_size, 1, size / 4, 4);
    assert_true(4 == asst);
}

void job_division_test_6(){
    long size = 16, inj_size = 2;
    long asst = create_test(size, inj_size, 4, size / 4, 4);
    assert_true(1 == asst);
}

void job_division_test_7(){
    int asserts = 0;
    long carrier_size = 16, inj_size = 2;
    uint8_t carr[carrier_size];
    uint8_t inj[inj_size];
    for(int i = 0; i < carrier_size; i++) carr[i] = 0;
    for(int i = 0; i < inj_size; i++) inj[i] = 0;
    carrier c = create_carrier(carr, carrier_size, carrier_size, 1);
    payload p = create_payload(inj, inj_size);
    lsb l = create_lsb(1);
    jobs j = divide_jobs(l, c, p);
    asserts += j->size == 1;
    asserts += j->carriers[0]->content == carr;
    asserts += j->payloads[0]->content == inj;
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    destroy_jobs(j);
    assert_true(asserts == 3);
}

void job_division_test_8(){
    int asserts = 0;
    long carrier_size = 16, inj_size = 4;
    uint8_t carr[carrier_size];
    uint8_t inj[inj_size];
    for(int i = 0; i < carrier_size; i++) carr[i] = 0;
    for(int i = 0; i < inj_size; i++) inj[i] = 0;
    carrier c = create_carrier(carr, carrier_size, carrier_size, 1);
    payload p = create_payload(inj, inj_size);
    lsb l = create_lsb(1);
    jobs j = divide_jobs(l, c, p);
    asserts += j->size == 2;
    asserts += j->carriers[0]->content == carr;
    asserts += j->payloads[0]->content == inj;
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    destroy_jobs(j);
    assert_true(asserts == 3);
}

void job_division_test_9(){
    int asserts = 0, j_size = 0;
    long carrier_size = 16, inj_size = 2;
    uint8_t carr[carrier_size];
    uint8_t inj[inj_size];
    for(int i = 0; i < carrier_size; i++) carr[i] = 0;
    for(int i = 0; i < inj_size; i++) inj[i] = 0;
    carrier c = create_carrier(carr, carrier_size, 1, carrier_size);
    payload p = create_payload(inj, inj_size);
    lsb l = create_lsb(1);
    jobs j = divide_jobs(l, c, p);
    j_size = j->size;
    asserts += j_size == 16;
    for(int i = 0; i < j->size; i++){
        asserts += j->carriers[i]->content == (carr + i * sizeof(uint8_t));
        asserts += j->payloads[i]->content == (inj + i * sizeof(uint8_t));
    }
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    destroy_jobs(j);
    assert_true(asserts == (2 * j_size+ 1));
}

void job_division_test_10(){
    int asserts = 0, j_size = 0;
    long carrier_size = 16, inj_size = 2;
    uint8_t carr[carrier_size];
    uint8_t inj[inj_size];
    for(int i = 0; i < carrier_size; i++) carr[i] = 0;
    for(int i = 0; i < inj_size; i++) inj[i] = 0;
    carrier c = create_carrier(carr, carrier_size, carrier_size, 1);
    payload p = create_payload(inj, inj_size);
    lsb l = create_lsb(4);
    jobs j = divide_jobs(l, c, p);
    j_size = j->size;
    asserts += j_size == 1;
    for(int i = 0; i < j->size; i++){
        asserts += j->carriers[i]->content == (carr + i * sizeof(uint8_t));
        asserts += j->payloads[i]->content == (inj + i * sizeof(uint8_t));
    }
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    destroy_jobs(j);
    assert_true(asserts == (2 * j_size + 1));
}

void job_division_test_11(){
    int asserts = 0, j_size = 0;
    long carrier_size = 16, inj_size = 2;
    uint8_t carr[carrier_size];
    uint8_t inj[inj_size];
    for(int i = 0; i < carrier_size; i++) carr[i] = 0;
    for(int i = 0; i < inj_size; i++) inj[i] = 0;
    carrier c = create_carrier(carr, carrier_size, 1, carrier_size);
    payload p = create_payload(inj, inj_size);
    lsb l = create_lsb(4);
    jobs j = divide_jobs(l, c, p);
    j_size = j->size;
    asserts += j_size == 4;
    for(int i = 0; i < j->size; i++){
        asserts += j->carriers[i]->content == (carr + i * sizeof(uint8_t));
        asserts += j->payloads[i]->content == (inj + i * sizeof(uint8_t));
    }
    destroy_carrier(c);
    destroy_payload(p);
    destroy_lsb(l);
    destroy_jobs(j);
    assert_true(asserts == (2 * j_size + 1));
}

long create_test(long size, long inj_size, int n, long width, long height){
    long ret = 0;
    uint8_t carr[size], inj[inj_size];
    lsb l = create_lsb(n);
    payload p = create_payload(inj, inj_size);
    carrier c = create_carrier( (uint8_t *)carr, size, width, height);
    jobs j = divide_jobs(l, c, p);
    destroy_carrier(c);
    ret = j->size;
    destroy_jobs(j);
    return ret;
}
