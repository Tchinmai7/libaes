#include <stdio.h>
#include "encrypt.h"
void aes_cbc_mode(uint8_t* input, uint8_t* output, uint8_t Nk, uint8_t* expanded_key) 
{
	cipher(input, output, expanded_key, Nk);
}

void encrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output)
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
		   aes_cbc_mode(input, output, aes_params->Nk, expanded_key);
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
