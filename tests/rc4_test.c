#include <testing_suite.h>
#include <rc4.h>

void rc4_text_test();
void rc4_image_test();

int main(){
    create_suite("RC4 Test");
    add_test(rc4_text_test);
    add_test(rc4_image_test);
     run_suite();
    clear_suite();
}
void rc4_image_test(){
    
    uint32_t size=45000; //size del plaintext/cyphertext
    uint8_t* key=malloc(48); //48bits
    memcpy(key,"secret",N);
    uint8_t* plaintext=malloc(size);

    FILE *f = fopen("original.png", "rw");
    if (f == NULL)
    {
        printf("File Not Found!\n");
        return ;
    }    
    memcpy(plaintext,f,size);
    for(int i=0;i<20;i++){
        printf("%d",plaintext[i]);
    }
    printf("\n");
    uint8_t *ciphertext = malloc(sizeof(uint8_t) * size);
    //encripto
    RC4(key,plaintext, ciphertext,size);

    //decripto
    unsigned char *decrypt = malloc(sizeof(int) * size);
    RC4(key,ciphertext, decrypt,size);
    for(int i=0;i<20;i++){
        printf("%d",decrypt[i]);
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

    if(!memcmp(decrypt,plaintext,size)){
            assert_true(1 == 1);
            return;
    }
    assert_true(0 == 1);
   

    return;
}

void rc4_text_test(){
    uint32_t size=31; //size del plaintext/cyphertext
    uint8_t* key=malloc(48); //48bits
    memcpy(key,"secret",N);
    uint8_t* plaintext=malloc(size);
    
    memcpy(plaintext,"hola como estas todo bien y vos",size);
    
    uint8_t *ciphertext = malloc(sizeof(uint8_t) * size);
     //encripto
    RC4(key,plaintext, ciphertext,size);

    for(int i = 0, len = size; i < len; i++){
        //printf("JOLA");
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    //decripto
    unsigned char *decrypt = malloc(sizeof(int) * size);
    RC4(key,ciphertext, decrypt,size);
    for(int i = 0, len = size; i < len; i++){
        //printf("JOLA");
        printf("%c ", decrypt[i]);
    }
        printf("\n");

    if(!memcmp(decrypt,plaintext,size)){
            assert_true(1 == 1);
            return;
    }
    
    assert_true(0 == 1);
   

    return;
}

