#include <stdio.h>
#include <stdlib.h>
#include "aes.h"

void print_word(uint8_t* word, int len) 
{
    for (int i = 0; i < len; i++) {
        printf("%02x", word[i]); 
    }
    printf("\n\n");
}

int main(int argc, char* argv[])
{
    uint8_t key_128_bit[16] = {  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    int Nr;
    int len;
    Nr = getNr(4);
    len = 4 * (Nr + 1) * 4;
    uint8_t word_128[len]; 
    expand_key(key_128_bit, 4, word_128);
    uint8_t input[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t output[16] = {0x00}; 
    printf("128 Bit AES - \n");
    printf("Plain: \t");
    print_word(input, 16);
    printf("Key Schedule[128]:\t ");
    print_word(word_128, len);
    cipher(input, output, word_128, 4);
    printf("Encrypted: \t");
    print_word(output, 16);


    uint8_t key_192_bit[24] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
    Nr = getNr(6);
    len = 4 * (Nr + 1) * 4;
    uint8_t word_192[len]; 
    expand_key(key_192_bit, 6, word_192);
    printf("192 Bit AES - \n");
    printf("Plain: \t");
    print_word(input, 16);
    printf("Key Schedule[192]:\t ");
    print_word(word_192, len);
    cipher(input, output, word_192, 6);
    printf("Encrypted: \t");
    print_word(output, 16);
    
    
    uint8_t key_256_bit[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
    Nr = getNr(8);
    len = 4 * (Nr + 1) * 4;
    uint8_t word_256[len]; 
    expand_key(key_256_bit, 8, word_256);
    printf("256 Bit AES - \n");
    printf("Plain: \t");
    print_word(input, 16);
    printf("Key Schedule[256]:\t ");
    print_word(word_256,len);
    printf("Encrypted: \t");
    cipher(input, output, word_256, 8);
    print_word(output, 16);
    return 0;
}
