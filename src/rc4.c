#include <rc4.h>

/*Codigo adaptado de https://gist.github.com/rverton/a44fc8ca67ab9ec32089 */

void swap(uint8_t *a, uint8_t *b) {

    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(uint8_t* key, uint8_t *S) {

    //int len = strlen(key);
    int len=N;
    int j = 0;

    for(int i = 0; i < N; i++)
        S[i] = i;

    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        swap(&S[i], &S[j]);
    }

    return 0;
}

int PRGA(uint8_t *S, uint8_t *plaintext, uint8_t *ciphertext, uint32_t size) {

    int i = 0;
    int j = 0;

    for(size_t n = 0, len = size; n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];

    }

    return 0;
}

int RC4(uint8_t* key, uint8_t *plaintext,uint8_t *ciphertext, uint32_t size) {

    unsigned char S[N];
    KSA(key, S);

    PRGA(S, plaintext, ciphertext,size);

    return 0;
}

