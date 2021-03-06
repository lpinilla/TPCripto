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

    char *file_name = "files_for_testing/salidaRC4";
    FILE *f = fopen(file_name, "rb");
    if (f == NULL)
    {
        printf("File Not Found! %s\n ", file_name);
        return;
    }

    char *file_name2 = "files_for_testing/ladoLSBI_corregido.bmp";
    FILE *h = fopen(file_name2, "rb");
    if (h == NULL)
    {
        printf("File Not Found! %s\n", file_name2);
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


    char * file_name3 = "tests_output/salidaRC4_nuestro.png";
    FILE *g = fopen(file_name3, "w");
    if (g == NULL)
    {
        printf("File Not Found! %s\n", file_name3);
        return;
    }


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
    memcpy(key, "secret", RC4_N);
    uint8_t *plaintext = malloc(size);

    memcpy(plaintext, "hola como estas todo bien y vos", size);

    uint8_t *ciphertext = malloc(sizeof(uint8_t) * size);
    //encripto
    RC4(key, plaintext, ciphertext, size);

    //decripto
    unsigned char *decrypt = malloc(sizeof(int) * size);
    RC4(key, ciphertext, decrypt, size);
    if (!memcmp(decrypt, plaintext, size))
    {
        assert_true(1 == 1);
        return;
    }

    assert_true(0 == 1);

    return;
}


