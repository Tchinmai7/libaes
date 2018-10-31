#include <stdio.h>
#include <string.h>
#include "encrypt.h"
#include "utils.h"
size_t aes_ofb_mode_encrypt(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
	int block_size = input_length / 16;
    uint8_t iv[16] = {0x00};
    get_iv(iv, 16);

#ifdef DEBUG_COFB
	printf("The IV is \n");
	print_word(iv, 16);
	printf("the num blocks is %d\n", block_size);
#endif 

    uint8_t block[16] = {0x00};
	uint8_t temp_op[16] = {0x00};
	
	// IV is in the first 16 bytes of the cipher text
	memcpy(output, iv, 16);
	//to account for the IV that's appended.
	size_t output_length = 1;
	for (int i = 0; i < block_size; i++) {
		// First encrypt the IV
		cipher(iv, temp_op, expanded_key, Nk);
		// Use the encrypted value as the IV for next
        memcpy(iv, temp_op,16);
		memcpy(block, input+(i*16), 16);
		// Xor the encrypted val with the plain text
        Xor(temp_op, block, 16);
		memcpy(output+(i*16)+16, temp_op, 16);
		output_length ++;
	}
    return output_length * 16;
}
size_t aes_cfb_mode_encrypt(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    uint8_t iv[16] = {0x00};
    get_iv(iv, 16);
	int block_size = input_length / 16;

#ifdef DEBUG_CFB
	printf("The IV is \n");
	print_word(iv, 16);
	printf("the num blocks is %d\n", block_size);
#endif 
	uint8_t block[16] = {0x00};
	uint8_t temp_op[16] = {0x00};
	
	// IV is in the first 16 bytes of the cipher text
	memcpy(output, iv, 16);
	//to account for the IV that's appended.
	size_t output_length = 1;
	for (int i = 0; i < block_size; i++) {
		// First encrypt the IV
		cipher(iv, temp_op, expanded_key, Nk);
		// Then Xor with plain text
		// Use the result as the IV for next
		memcpy(block, input+(i*16), 16);
		Xor(temp_op, block, 16);
		memcpy(output+(i*16)+16, temp_op, 16);
		memcpy(iv, temp_op,16);
		output_length ++;
	}
    return output_length * 16;
}

size_t aes_ecb_mode_encrypt(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
	int block_size = input_length / 16;
	uint8_t block[16] = {0x00};
	uint8_t temp_op[16] = {0x00};
	
	size_t output_length = 0;
	for (int i = 0; i < block_size; i++) {
		memcpy(block, input+(i*16), 16);
		cipher(block, temp_op, expanded_key, Nk);
		memcpy(output+(i*16), temp_op, 16);
		output_length++;
	}
    return output_length * 16;
}

size_t aes_cbc_mode_encrypt(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    uint8_t iv[16] = {0x00};
    get_iv(iv, 16);
	int block_size = input_length / 16;

#ifdef DEBUG_CBC
	printf("The IV is \n");
	print_word(iv, 16);
	printf("the num blocks is %d\n", block_size);
#endif 
	uint8_t block[16] = {0x00};
	uint8_t temp_op[16] = {0x00};
	
	// IV is in the first 16 bytes of the cipher text
	memcpy(output, iv, 16);
	//to account for the IV that's appended.
	size_t output_length = 1;
	for (int i = 0; i < block_size; i++) {
		memcpy(block, input+(i*16), 16);
		Xor(block, iv, 16);
		cipher(block, temp_op, expanded_key, Nk);
		memcpy(output+(i*16)+16, temp_op, 16);
		memcpy(iv, temp_op,16);
		output_length ++;
	}
    return output_length * 16;
}

size_t encrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output, int input_length)
{
    int Nr = getNr(aes_params->Nk);
    // the last *4 is to convert words to bytes
    int len = 4 * (Nr + 1) * 4;
    uint8_t expanded_key[len]; 
    expand_key(aes_params->key, aes_params->Nk, expanded_key);

#ifdef DEBUG_KEYS
    printf("The expanded key is:\n");
    print_word(expanded_key, len);
#endif
    // implement modes here.
    switch(aes_params->aes_mode) {
	    case AES_MODE_CBC:
		   return aes_cbc_mode_encrypt(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    case AES_MODE_ECB:
	           return aes_ecb_mode_encrypt(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    case AES_MODE_CTR:
	    break;
	    case AES_MODE_OFB:
		   return aes_ofb_mode_encrypt(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    case AES_MODE_CFB:
		   return aes_cfb_mode_encrypt(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    default:
	    break;
    }
    return 0;
}
