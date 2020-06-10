#include <testing_suite.h>
#include <rc4.h>

void rc4_text_test();
void rc4_image_test();
void rc4_image_test_1();
void rc4_image_test_2();

void rc4_text_test_hexa();

//uint8_t *hex_to_char(uint8_t *hexa);

int main()
{
    create_suite("RC4 Test");
    //add_test(rc4_text_test);
    //add_test(rc4_text_test_hexa);
    //add_test(rc4_image_test);
    //add_test(rc4_image_test_1);
    //add_test(rc4_image_test_2);

    run_suite();
    clear_suite();
}

//testea la salida del payload de lsbi, que desencripte bien con rc4 y arme la foto
void rc4_image_test_2()
{
    uint32_t size = 44894;        //size del cyphertext completo, 44886 del archivo+4 del tamanio+4 de la extension
    uint8_t *key = malloc(6); //48bits

    uint8_t *ciphertext = malloc(size);

    FILE *f = fopen("salidaRC4", "rb");
    if (f == NULL)
    {
        printf("File Not Found!\n");
        return;
    }

    FILE *h = fopen("files_for_testing/ladoLSBI_corregido.bmp", "rb");
    if (h == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    fseek(h, 54, SEEK_SET);
    fread(key, sizeof(uint8_t), 6, h);

    printf("key ");
    for (int i = 0; i < 6; i++)
    {
        printf("%x ", key[i]);
    }
    printf("\n");

    //fseek(f,4,SEEK_SET);
    fread(ciphertext, sizeof(uint8_t), size, f);

    // printf("chipher ");
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%x ", ciphertext[i]);
    // }
    // printf("\n");

    //decrypt
    unsigned char *decrypt = malloc(sizeof(uint8_t) * size);

    RC4(key, ciphertext, decrypt, size);

    FILE *g = fopen("salidaRC4Nuestro.png", "w");
    if (g == NULL)
    {
        printf("File Not Found!\n");
        return;
    }

    // printf("decript ");
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%x ", decrypt[i]);
    // }

    printf("\n");

    //fseek(g,,SEEK_SET);
    fwrite(decrypt+4, sizeof(uint8_t), size-8, g);//size-8 para solo copiar el archivo
    fclose(f);
    fclose(g);
    fclose(h);
}

//testea el desencriptado del tamanio
void rc4_image_test_1()
{
    uint32_t size = 4;        //size del cyphertext
    uint8_t *key = malloc(6); //48bits
    //memcpy(key,"4294967295",6);
    uint8_t *ciphertext = malloc(size);

    FILE *f = fopen("salidaRC4", "rb");
    if (f == NULL)
    {
        printf("File Not Found!\n");
        return;
    }

    FILE *h = fopen("files_for_testing/ladoLSBI_corregido.bmp", "rb");
    if (h == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    fseek(h, 54, SEEK_SET);
    fread(key, sizeof(uint8_t), 6, h);

    printf("key ");
    for (int i = 0; i < 6; i++)
    {
        printf("%x ", key[i]);
    }
    printf("\n");

    //fseek(f,4,SEEK_SET);
    fread(ciphertext, sizeof(uint8_t), 4, f);

    printf("chipher ");
    for (int i = 0; i < 6; i++)
    {
        printf("%x ", ciphertext[i]);
    }
    printf("\n");

    //decrypt
    unsigned char *decrypt = malloc(sizeof(uint8_t) * size);

    RC4(key, ciphertext, decrypt, size);

    FILE *g = fopen("salidaRC4.png", "w");
    if (g == NULL)
    {
        printf("File Not Found!\n");
        return;
    }

    printf("decript ");
    for (int i = 0; i < 6; i++)
    {
        printf("%x ", decrypt[i]);
    }

    printf("\n");

    fwrite(decrypt, sizeof(uint8_t), size, g);
    fclose(f);
    fclose(g);
    fclose(h);
}

// long int hex_to_int(uint8_t *hexa, int lengh)
// {
//     long int rta=0;
//     for(int i=0;i<lengh;i++){

//     }
// }

void rc4_image_test()
{

    uint32_t size = 45000;     //size del cyphertext
    uint8_t *key = malloc(48); //48bits
    memcpy(key, "secret", N);
    uint8_t *plaintext = malloc(size);

    FILE *f = fopen("original.png", "rw");
    if (f == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    memcpy(plaintext, f, size);
    for (int i = 0; i < 20; i++)
    {
        printf("%d", plaintext[i]);
    }
    printf("\n");
    uint8_t *ciphertext = malloc(sizeof(uint8_t) * size);
    //encripto
    RC4(key, plaintext, ciphertext, size);

    //decripto
    unsigned char *decrypt = malloc(sizeof(int) * size);
    RC4(key, ciphertext, decrypt, size);
    for (int i = 0; i < 20; i++)
    {
        printf("%d", decrypt[i]);
    }
    printf("\n");

    // FILE *g = fopen("test_create_files/rc4_original.png", "w");
    // if (g == NULL)
    // {
    //     printf("File Not Found!\n");
    //     return ;
    // }
    // fwrite(decrypt, sizeof(uint8_t), size, g);
    //fclose(g);
    fclose(f);

    if (!memcmp(decrypt, plaintext, size))
    {
        assert_true(1 == 1);
        return;
    }
    assert_true(0 == 1);

    return;
}

void rc4_text_test()
{
    uint32_t size = 31;       //size del plaintext/cyphertext
    uint8_t *key = malloc(6); //48bits 6 bytes
    memcpy(key, "secret", N);
    uint8_t *plaintext = malloc(size);

    memcpy(plaintext, "hola como estas todo bien y vos", size);

    uint8_t *ciphertext = malloc(sizeof(uint8_t) * size);
    //encripto
    RC4(key, plaintext, ciphertext, size);

    for (int i = 0, len = size; i < len; i++)
    {
        printf("%x ", ciphertext[i]);
    }
    printf("\n");

    //decripto
    unsigned char *decrypt = malloc(sizeof(int) * size);
    RC4(key, ciphertext, decrypt, size);
    for (int i = 0, len = size; i < len; i++)
    {
        printf("%c ", decrypt[i]);
    }
    printf("\n");

    if (!memcmp(decrypt, plaintext, size))
    {
        assert_true(1 == 1);
        return;
    }

    assert_true(0 == 1);

    return;
}

void rc4_text_test_hexa()
{
    uint32_t size = 31;       //size del plaintext/cyphertext

    uint8_t array[6] = {0xF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    char arr[128] = {0};
    int i = 0;
    unsigned long long res = 0;
    for (i = 0; i < 6; i++)
        sprintf((arr + (i * 2)), "%02x", (array[i] & 0xff));

    printf("arr is %s\n", arr);

    res = strtoll(arr, NULL, 16);
    printf("res is %llu\n", res);

    // uint8_t byteArray[6];

    // // convert from an unsigned long int to a 4-byte array
    // byteArray[0] = (int)((res >> 40) & 0xFF);
    // byteArray[1] = (int)((res >> 32) & 0xFF);
    // byteArray[2] = (int)((res >> 24) & 0xFF);
    // byteArray[3] = (int)((res >> 16) & 0xFF);
    // byteArray[4] = (int)((res >> 8) & 0XFF);
    // byteArray[5] = (int)((res & 0XFF));
    
    uint8_t *plaintext = malloc(size);

    memcpy(plaintext, "hola como estas todo bien y vos", size);

    uint8_t *ciphertext = malloc(sizeof(uint8_t) * size);
    //encripto
    RC4(array, plaintext, ciphertext, size);

    for (int i = 0, len = size; i < len; i++)
    {
        printf("%x ", ciphertext[i]);
    }
    printf("\n");

    //decripto
    unsigned char *decrypt = malloc(sizeof(int) * size);
    RC4(array, ciphertext, decrypt, size);
    for (int i = 0, len = size; i < len; i++)
    {
        printf("%c ", decrypt[i]);
    }
    printf("\n");

    

    assert_true(1 == 1);

    return;
}
