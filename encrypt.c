#include <stdio.h>
#include <string.h>
#include "encrypt.h"
void aes_cbc_mode(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
	FILE *f;
	uint8_t iv[16] = {0x00};
	f = fopen("/dev/urandom", "r");
	fread(&iv, 16, 1, f);
	fclose(f);
	printf("The IV is \n");
	print_word(iv, 16);
	int block_size = input_length / 16;

	printf("the num blocks is %d\n", block_size);
	uint8_t temp[16] = {0x00};
	uint8_t temp_op[16] = {0x00};
	memcpy(temp, input, 16);
	xor(temp, iv, 16);
	cipher(temp, temp_op, expanded_key, Nk);
	memcpy(output, temp_op, 16);
	for (int i = 1; i < block_size; i++) {
		memcpy(temp, input+(i*16), 16);
		xor(temp, temp_op, 16);
		cipher(temp, temp_op, expanded_key, Nk);
		memcpy(output+(i*16), temp_op, 16);
	}
}

void encrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output, int input_length)
{
    int Nr;
    int len;
    Nr = getNr(aes_params->Nk);
    // the last *4 is to convert words to bytes
    len = 4 * (Nr + 1) * 4;
    uint8_t expanded_key[len]; 
    expand_key(aes_params->key, aes_params->Nk, expanded_key);
    printf("The expanded key is:\n");
    print_word(expanded_key, len);
    // implement modes here.
    switch(aes_params->aes_mode) {
	    case AES_MODE_CBC:
		   aes_cbc_mode(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    case AES_MODE_ECB:
	    break;
	    case AES_MODE_CTR:
	    break;
	    case AES_MODE_OFB:
	    break;
	    case AES_MODE_CFB:
	    break;
	    default:
	    break;
    }
}
