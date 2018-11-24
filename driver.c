#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char* argv[])
{
    if (argc < 2) {
	    printf("Error, enter a value to encrypt!\n");
    	return -1;
    }
    size_t input_size = strlen(argv[1]);
    
    uint8_t* input = NULL;
    printf("Input size is %ld\n", input_size);
    //input = malloc(input_size);
    input = calloc(input_size, 1);
    if (input == NULL) {
        printf("fatal error, Calloc failure");
        exit(-1);
    }

    memcpy(input, argv[1], input_size);
    
    //TODO: Make key inputtable by user if not, use a secure random key 
    printf("128 Bit AES - \n");
    uint8_t key_128_bit[16] = {  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    test_encryption(key_128_bit, AES_128_BIT, 4, input, input_size); 
    
    printf("192 Bit AES - \n");
    uint8_t key_192_bit[24] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
    test_encryption(key_192_bit, AES_192_BIT, 6, input, input_size); 
    
    printf("256 Bit AES - \n");
    uint8_t key_256_bit[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    test_encryption(key_256_bit, AES_256_BIT, 8, input, input_size); 
    free(input);
    return 0;
}
