#ifndef __DECRYPT_H
#define __DECRYPT_H
#include "aes.h"
size_t decrypt(aes_params_t* aes_params, uint8_t* input, uint8_t* output, int input_length);
#endif //ifndef __DNCRYPT_H
