#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"
#include "decrypt.h"
#include "aes.h"
#include "inv_aes.h"

int main(int argc, char* argv[])
{
    uint8_t key_128_bit[16] = {  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    aes_params_t* params = init_aes_params();
    set_aes_key(params, AES_128_BIT, key_128_bit); 
    uint8_t input[16] = {0x00};
    if (argv[1] == NULL) {
	printf("Error, enter a value to encrypt!\n");
    	return -1;
    }
    if (strlen(argv[1]) != 16) {
    	printf("Error, input should be a multiple of 16\n");
	return -1;
    }
    memcpy(input, argv[1], 16);
    uint8_t output[16] = {0x00}; 
    printf("128 Bit AES - \n");
    printf("Plain: \t");
    print_word(input, 16);
    printf("%s\n", input);
    
    encrypt(params, input, output);
    printf("Encrypted: \t");
    print_word(output, 16);

    uint8_t plain[16] = {0x00};
    decrypt(params, output, plain);
    printf("Decrypted: \t");
    print_word(plain, 16);
    printf("%s\n", plain);

    uint8_t key_192_bit[24] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
    set_aes_key(params, AES_192_BIT, key_192_bit);
    printf("192 Bit AES - \n");
    printf("Plain: \t");
    print_word(input, 16);
    encrypt(params, input, output);
    printf("Encrypted: \t");
    print_word(output, 16);

    decrypt(params, output, plain);
    printf("Decrypted: \t");
    print_word(plain, 16);
    printf("%s\n", plain);
    
    uint8_t key_256_bit[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    set_aes_key(params, AES_256_BIT, key_256_bit);
    printf("256 Bit AES - \n");
    printf("Plain: \t");
    print_word(input, 16);
    
    encrypt(params, input, output);
    printf("Encrypted: \t");
    print_word(output, 16);

    decrypt(params, output, plain);
    printf("Decrypted: \t");
    print_word(plain, 16);
    printf("%s\n", plain);
    return 0;
}
