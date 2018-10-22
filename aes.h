#ifndef __AES_H
#define __AES_H
#include <stdint.h>
typedef enum {
    AES_MODE_CBC = 0,
    AES_MODE_ECB = 1,
    AES_MODE_CTR = 2,
    AES_MODE_OFB = 3,
    AES_MODE_CFB = 4
} aes_modes_t;

typedef enum {
    AES_128_BIT = 128,
    AES_192_BIT = 192,
    AES_256_BIT = 256
} aes_key_size_t;

typedef struct {
    aes_modes_t aes_mode;
    uint8_t key_length;
    void* key;
} aes_params_t;

aes_params_t* init_aes_params(uint8_t key_size, void* key);
#endif