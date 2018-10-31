#include <stdio.h>
#include <string.h>
#include "inv_aes.h"
#include "decrypt.h"

size_t aes_cfb_mode_decrypt(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
	uint8_t iv[16] = {0x00};
	// IV is in the first 16 bytes of the cipher text
	memcpy(iv, input, 16);
	int block_size = (input_length / 16);

#ifdef DEBUG_CFB
	printf("The Decrypt IV is \n");
	print_word(iv, 16);
	print_word(input, input_length);
	printf("the num blocks is %d\n", block_size);
#endif
	uint8_t temp_op[16] = {0x00};
	uint8_t block[16] = {0x00};
	size_t output_length = 0;
	// The first block is the IV
	for (int i = 1; i < block_size; i++) {
		// encrypt the IV
		memcpy(block, input + (i*16), 16);
		cipher(iv, temp_op, expanded_key, Nk);
		xor(temp_op, block, 16);
		memcpy(output+((i-1)*16), temp_op, 16);
		memcpy(iv, block, 16);
		output_length++;
	}
	return output_length * 16;
}
// Returns length of decrypted message
size_t aes_cbc_mode_decrypt(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
	uint8_t iv[16] = {0x00};
	// IV is in the first 16 bytes of the cipher text
	memcpy(iv, input, 16);
	int block_size = (input_length / 16);

#ifdef DEBUG_CBC
	printf("The Decrypt IV is \n");
	print_word(iv, 16);
	print_word(input, input_length);
	printf("the num blocks is %d\n", block_size);
#endif
	uint8_t block[16] = {0x00};
	uint8_t temp_op[16] = {0x00};
	size_t output_length = 0;
	// The first block is the IV
	for (int i = 1; i < block_size; i++) {
		memcpy(block, input + (i*16), 16);
		inv_cipher(block, temp_op, expanded_key, Nk);
		xor(temp_op, iv, 16);
		memcpy(output+((i-1)*16), temp_op, 16);
		memcpy(iv,block,16);
		output_length++;
	}
	return output_length * 16;
}

size_t decrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output, int input_length)
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

    switch(aes_params->aes_mode) {
	    case AES_MODE_CBC:
		   return aes_cbc_mode_decrypt(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    case AES_MODE_ECB:
	    break;
	    case AES_MODE_CTR:
	    break;
	    case AES_MODE_OFB:
	    break;
	    case AES_MODE_CFB:
		   return aes_cfb_mode_decrypt(input, output, aes_params->Nk, expanded_key, input_length);
	    break;
	    default:
	    break;
    }
    return 0;
}
