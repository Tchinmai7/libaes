// Don't add _ before include guards - DCL37-C in SEI guide
#ifndef ENCRYPT_H
#define ENCRYPT_H
#include "aes.h"
size_t encrypt(aes_params_t* aes_params, uint8_t* input, uint8_t** output, int input_length);
#endif //ifndef ENCRYPT_H
