#ifndef INV_AES_H
#define INV_AES_H
#include <stdint.h>
void inv_cipher(uint8_t* in, uint8_t* out, uint8_t* w, int Nk);
#endif
