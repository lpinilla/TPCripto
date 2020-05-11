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

int main(){
    create_suite("Jobs Suite");
    add_named_test(job_division_test, "job_division_test");
    add_named_test(job_division_test_2, NAME_OFF(job_division_test_2));
    add_named_test(job_division_test_3, NAME_OFF(job_division_test_3));
    add_test(job_division_test_4);
    add_test(job_division_test_5);
    add_test(job_division_test_6);
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

long create_test(long size, long inj_size, int n, long width, long height){
    uint8_t carr[size], inj[inj_size];
    lsb l = create_lsb(n);
    payload p = create_payload(inj, inj_size);
    carrier c = create_carrier( (uint8_t *)carr, size, width, height);
    jobs j = divide_jobs(l, c, p);
    destroy_carrier(c);
    return j->size;
}
