#include <testing_suite.h>
#include <rc4.h>

void rc4_text_test();
void rc4_image_test_2();


//uint8_t *hex_to_char(uint8_t *hexa);

int main()
{
    create_suite("RC4 Test");
    add_test(rc4_text_test);
    add_test(rc4_image_test_2);

    run_suite();
    clear_suite();
}

//testea la salida del payload de lsbi, que desencripte bien con rc4 y arme la foto
void rc4_image_test_2()
{
    uint32_t size = 44894;        //size del cyphertext completo, 44886 del archivo+4 del tamanio+4 de la extension
    uint8_t *key = malloc(6); //48bits

    uint8_t *ciphertext = malloc(size);

    FILE *f = fopen("files_for_testing/salidaRC4", "rb");
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

    // printf("key ");
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("%x ", key[i]);
    // }
    // printf("\n");

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

    FILE *g = fopen("test_create_files/salidaRC4_nuestro.png", "w");
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


// long int hex_to_int(uint8_t *hexa, int lengh)
// {
//     long int rta=0;
//     for(int i=0;i<lengh;i++){

//     }
// }



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


