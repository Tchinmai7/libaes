#include <stdio.h>
#include "inv_aes.h"
#include "decrypt.h"
void decrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output)
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
    inv_cipher(input, output, expanded_key, aes_params->Nk);
}
