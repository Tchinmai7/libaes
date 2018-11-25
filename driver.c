#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include "encrypt.h"
#include "decrypt.h"
#include "aes.h"
#include "inv_aes.h"
#include "utils.h"

void test_encryption(uint8_t* key, aes_key_size_t key_size, uint8_t Nk, uint8_t* input, size_t input_size)
{
    printf("The key used is\n");
    print_word(key, Nk * 4); 
    aes_params_t* params = init_aes_params();
    if (params == NULL) {
        printf("Fatal error. unable to alloc aes params\n");
        return;
    } 
    set_aes_key(params, key_size, key); 
    printf("Bytes Plain: \t");
    print_word(input, input_size);
    printf("STR: Input: %s\n", input);
    
    uint8_t* output = NULL; 
    size_t enc_len = encrypt(params, input, &output, input_size);
    printf("Encrypted bytes: \t");
    print_word(output, enc_len);

    uint8_t* plain = NULL;
    size_t dec_len = decrypt(params, output, &plain, enc_len);
    // Null terminate the string
    plain[dec_len] = '\0';
    printf("Decrypted bytes: \t");
    print_word(plain, dec_len);
    printf("decrypted_string %s\n", plain);
    free(output);
    free(plain);
    free_aes_params(params);
}

// Returns memory area and fills the key into `key`
uint8_t* generate_secure_random_key(uint8_t* secret_buf, size_t keysize)
{
    struct rlimit limit;
    limit.rlim_cur = 0;
    limit.rlim_max = 0;
    if (setrlimit(RLIMIT_CORE, &limit) != 0) {
        printf("ERROR: Unable to set core size to 0. Exiting\n");
        exit(-1);
    }

    long pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize == -1) {
        printf("ERROR: Page size is reported as -1. Exiting\n");
        exit(-1);
    }
    
    uint8_t *key;
    secret_buf = calloc(keysize+1+pagesize, 1);
    if (!secret_buf) {
        printf("ERROR: Malloc failure. Exiting\n");
        exit(-1);
    }
    
    /* mlock() may require that address be a multiple of PAGESIZE */
    key = (uint8_t*)((((intptr_t)secret_buf + pagesize - 1) / pagesize) * pagesize);

    if (mlock(key, keysize+1) != 0) {
        printf("ERROR: Mlock failure. Exiting\n");
        exit(-1);
    }
    get_random_bytes(key, keysize);    
    return key;
}

void free_secure_random_key(uint8_t* key, uint8_t* secret_buf, size_t keysize)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize == -1) {
        printf("ERROR: Page size is reported as -1. Exiting\n");
        exit(-1);
    }
    if (munlock(key, keysize+1) != 0) {
        printf("ERROR: Mlock failure. Exiting\n");
        exit(-1);
    }
    key = NULL;
    memset(secret_buf, '\0', keysize+1+pagesize);
    free(secret_buf);
    secret_buf = NULL;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
	    printf("Error, enter a value to encrypt!\n");
    	return -1;
    }
    size_t input_size = strlen(argv[1]);
    
    uint8_t* input = NULL;
    printf("Input size is %ld\n", input_size);
    input = calloc(input_size, 1);
    if (input == NULL) {
        printf("fatal error, Calloc failure");
        exit(-1);
    }

    memcpy(input, argv[1], input_size);
    uint8_t* key = NULL;
    uint8_t* secret_buf = NULL;
    printf("128 Bit AES - \n");
    key = generate_secure_random_key(secret_buf, 16);
    test_encryption(key, AES_128_BIT, 4, input, input_size); 
    free_secure_random_key(key, secret_buf, 16);
    
    printf("192 Bit AES - \n");
    key = generate_secure_random_key(secret_buf, 24);
    test_encryption(key, AES_192_BIT, 6, input, input_size); 
    free_secure_random_key(key, secret_buf, 24);
    printf("256 Bit AES - \n");
    key = generate_secure_random_key(secret_buf, 32);
    test_encryption(key, AES_256_BIT, 8, input, input_size); 
    free_secure_random_key(key, secret_buf, 32);
    free(input);
    return 0;
}
