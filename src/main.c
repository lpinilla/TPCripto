#include <memory.h>
#include <options.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define UNUSED(x) (void)(x)



void _embed(struct options *options) {
    UNUSED(options);
}

void _extract(struct options * options) {
    UNUSED(options);
}

void print_options(struct options *options) {
    printf("-- Options --\n");
    printf("Operation: %s\n", options->operation == embed? "Embed": "Extract");
    if (options->operation == embed) {
        printf("In: %s\n", options->in);    
    }
    printf("Out: %s\n", options->out);
    printf("P: %s\n", options->p);
    switch (options->stego_type) {
        case lsb1:
            printf("Stego type: lsb1\n");
            break;
        case lsb4:
            printf("Stego type: lsb4\n");
            break;
        case lsbi:
            printf("Stego type: lsbi\n");
            break;
    }
    if (options->encrypted) {
        printf("Encription password: %s\n", options->encription_password);
        switch (options->encription_algorithm) {
            case des:
                printf("Encription Algorithm: des\n");
                break;
            case aes128:
                printf("Encription Algorithm: aes128\n");
                break;
            case aes192:
                printf("Encription Algorithm: aes192\n");
                break;
            case aes256:
                printf("Encription Algorithm: aes256\n");
                break;
        }
        switch (options->encription_mode) {
            case ecb:
                printf("Encription mode: ecb\n");
                break;
            case cfb:
                printf("Encription mode: cfb\n");
                break;
            case ofb:
                printf("Encription mode: ofb\n");
                break;
            case cbc:
                printf("Encription mode: cbc\n");
                break;
        }
    }

    
}

struct options* get_parameters(const int argc, char *const argv[]) {
    // Por la consigna vamos a asumir que el primer argumento
    // Tiene que ser o -embed o -extract
    // A partir de ahi generamos las estructuras de opciones
    struct options * options = malloc(sizeof(struct options));
    if (argc <= 1) {
        printf("Parameter for either -embed or -extract is required\n");
        goto fail;
    }
    if (strcmp(argv[1], "-embed") == 0) {
        options->operation = embed;
    } else if (strcmp(argv[1], "-extract") == 0) {
        options->operation = extract;
    } else {
        printf("First parameter should be  either -embed or -extract\n");
        goto fail;
    }

    bool in_set = false;
    bool out_set = false;
    bool p_set = false;
    bool steg_set = false;

    // Default options
    options->encription_mode = cbc;
    options->encription_algorithm = aes128;
    options->encrypted = false;
    bool failed = false;
    // Parse options
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-in") == 0) {
            i++;
            strcpy(options->in, argv[i]);
            in_set = true;
        } else if (strcmp(argv[i], "-out") == 0) {
            i++;
            strcpy(options->out, argv[i]);
            out_set = true;
        } else if (strcmp(argv[i], "-p") == 0) {
            i++;
            strcpy(options->p, argv[i]);
            p_set = true;
        } else if (strcmp(argv[i], "-steg") == 0) {
            i++;
            if (strcmp(argv[i], "LSB1") == 0) {
                options->stego_type = lsb1;
            } else if (strcmp(argv[i], "LSB4") == 0) {
                options->stego_type = lsb4;
            } else if (strcmp(argv[i], "LSBI") == 0) {
                options->stego_type = lsbi;
            } else {
                failed = true;
                printf("Invalid -steg argument\n");
            }
            steg_set = true;
        } else if (strcmp(argv[i], "-a") == 0) {
            i++;
            if (strcmp(argv[i], "aes128") == 0) {
                options->encription_algorithm = aes128;
            } else if (strcmp(argv[i], "aes192") == 0) {
                options->encription_algorithm = aes192;
            } else if (strcmp(argv[i], "aes256") == 0) {
                options->encription_algorithm = aes256;
            } else if (strcmp(argv[i], "des") == 0) {
                options->encription_algorithm = des;
            } else {
                failed = true;
                printf("Invalid -a argument\n");
            }
        } else if (strcmp(argv[i], "-m") == 0) {
            i++;
            if (strcmp(argv[i], "ecb") == 0) {
                options->encription_mode = ecb;
            } else if (strcmp(argv[i], "cfb") == 0) {
                options->encription_mode = cfb;
            } else if (strcmp(argv[i], "ofb") == 0) {
                options->encription_mode = ofb;
            } else if (strcmp(argv[i], "cbc") == 0) {
                options->encription_mode = cbc;
            } else {
                failed = true;
                printf("Invalid -m argument\n");
            }
        } else if (strcmp(argv[i], "-pass") == 0) {            
            i++;
            strcpy(options->encription_password, argv[i]);
            options->encrypted = true;
        }
    }
    
    if (options->operation == embed && !in_set) {
        printf("-in parameter was not set (required in embed operation)\n");
        failed = true;
    }
    if (!out_set) {
        printf("-out parameter was not set\n");
        failed = true;
    }
    if (!p_set) {
        printf("-p parameter was not set\n");
        failed = true;
    }
    if (!steg_set) {
        printf("-steg parameter was not set\n");
        failed = true;
    }
    if (failed){
        goto fail;
    }        
    return options;
fail:
    free(options);
    return 0;
}

int main(const int argc, char *const argv[]) {
    
    struct options * options = get_parameters(argc, argv);
    if (options == 0) {
        exit(-1);
    }

    print_options(options);

    

    if (options->operation == embed) {
        _embed(options);
    }
    if (options->operation == extract) {
        _extract(options);
    }

    free(options);
    
    
}
