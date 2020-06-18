#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <stdbool.h>
#include <encrypt.h>

enum stego_types {
    lsb1, lsb4, lsbi
};

enum operations {
    embed, extract
};

typedef struct options {
    enum operations operation;
    char in[255];
    char p[255];
    char out[255];
    enum stego_types stego_type;
    bool encrypted;
    enum modes encription_mode;
    enum algorithms encription_algorithm;
    char encription_password[255];
} options;

#endif