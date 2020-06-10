#include <rc4.h>
/*Codigo adaptado de https://gist.github.com/rverton/a44fc8ca67ab9ec32089 */



#define M 256   // 2^8

void swap(uint8_t *a, uint8_t *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(uint8_t* key, uint8_t *S) {
    // printf("entro ksa\n");
    // printf("key: ");
    // for(int i=0;i<6;i++){
    //     printf("%c ",key[i]);
    // }
    // printf("\n");

    //int len = strlen(key);
    int len=N;
    int j = 0;

    for(int i = 0; i < M; i++)
        S[i] = i;

    for(int i = 0; i < M; i++) {
        j = (j + S[i] + key[i % len]) % M;

        swap(&S[i], &S[j]);
    }

    // printf("s: ");
    // for(int i=0;i<M;i++){
    //     printf("%x ",S[i]);
    // }
    // printf("\n");

    return 0;
}

int PRGA(uint8_t *S, uint8_t *plaintext, uint8_t *ciphertext, uint32_t size) {

    int i = 0;
    int j = 0;

    for(size_t n = 0, len = size; n < len; n++) {
        i = (i + 1) % M;
        j = (j + S[i]) % M;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % M];

        ciphertext[n] = rnd ^ plaintext[n];
        //printf("cyper %ld: %c\n",n,ciphertext[n]);

    }


    return 0;
}

int RC4(uint8_t* key, uint8_t *plaintext,uint8_t *ciphertext, uint32_t size) {

    uint8_t S[M];
    // printf("key: ");
    // for(int i=0;i<6;i++){
    //     printf("%02x ",key[i]);
    // }
    // printf("\n");

    KSA(key, S);
    PRGA(S, plaintext, ciphertext,size);
    // rc4_init(key,6);
    // for(int m=0;m<6;m++){
    //     printf("%02X", plaintext[m] ^ rc4_output());
    // }
    // printf("\nsalio rc4\n");
    return 0; 
}

