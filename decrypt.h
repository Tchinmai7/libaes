#ifndef __DECRYPT_H
#define __DECRYPT_H
#include "aes.h"
// copies a non-null terminated string into the buffer. has space for a null
// It is the responsibility of the caller to null terminate the string
size_t decrypt(aes_params_t* aes_params, uint8_t* input, uint8_t** output, int input_length);
#endif //ifndef __DNCRYPT_H
