#ifndef __ENCRYPT_H
#define __ENCRYPT_H
#include "aes.h"
size_t encrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output, int input_length);
#endif //ifndef __ENCRYPT_H
