#include <rc4.h>
/*Codigo adaptado de https://gist.github.com/rverton/a44fc8ca67ab9ec32089 */

#define M 256 // 2^8
#define T 4

void swap(uint8_t *a, uint8_t *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int KSA(uint8_t *key, uint8_t *S)
{
  // printf("entro ksa\n");
  // printf("key: ");
  // for(int i=0;i<6;i++){
  //     printf("%c ",key[i]);
  // }
  // printf("\n");

  // int len = strlen(key);
  int len = RC4_N;
  int j = 0;

  for (int i = 0; i < M; i++)
    S[i] = i;

  for (int i = 0; i < M; i++)
  {
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

int PRGA(uint8_t *S, uint8_t *plaintext, uint8_t *ciphertext, uint32_t size)
{
  int i = 0;
  int j = 0;

  for (size_t n = 0, len = size; n < len; n++)
  {
    i = (i + 1) % M;
    j = (j + S[i]) % M;

    swap(&S[i], &S[j]);
    int rnd = S[(S[i] + S[j]) % M];

    ciphertext[n] = rnd ^ plaintext[n];
    // printf("cyper %ld: %c\n",n,ciphertext[n]);
  }

  return 0;
}

int RC4(uint8_t *key, uint8_t *plaintext, uint8_t *ciphertext, uint32_t size)
{
  uint8_t S[M];

  KSA(key, S);

  PRGA(S, plaintext, ciphertext, size);

  // printf("adentro ");
  // for (int i = 0; i < 4; i++)
  // {
  //   printf("%02x ", ciphertext[i]);
  // }
  // printf("\n");
  // printf("por salir\n");

  return 0;
}

int prepare_size(uint32_t payload_size, uint8_t *prep_size)
{
  uint8_t array[4];
  array[0] = (int)((payload_size >> 24) & 0xFF);
  array[1] = (int)((payload_size >> 16) & 0xFF);
  array[2] = (int)((payload_size >> 8) & 0XFF);
  array[3] = (int)((payload_size & 0XFF));

  if (array[0] == 0 && array[1] == 0)
  {
    memcpy(prep_size, array + 2, 2);
    return 2;
  }
  if (array[0] == 0)
  {
    memcpy(prep_size, array + 1, 3);
    return 3;
  }
  else
  {
    memcpy(prep_size, array, T);
    return 4;
  }
}

int prepare_size_enc(uint32_t payload_size, uint8_t *prep_size)
{
  uint8_t array[4];
  array[0] = (int)((payload_size >> 24) & 0xFF);
  array[1] = (int)((payload_size >> 16) & 0xFF);
  array[2] = (int)((payload_size >> 8) & 0XFF);
  array[3] = (int)((payload_size & 0XFF));

  memcpy(prep_size, array, RC4_T);
  return RC4_T;
}

uint32_t hex_to_dec(uint8_t *payload_size_decript, int size)
{
  uint32_t res = 0;
  char arr[size];

  for (int i = 0; i < size; i++)
    sprintf((arr + (i * 2)), "%02x", (payload_size_decript[i] & 0xff));

  res = strtoll(arr, NULL, 16);
  return res;
}
