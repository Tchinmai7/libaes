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
    AES_128_BIT = 16,
    AES_192_BIT = 24,
    AES_256_BIT = 32
} aes_key_size_t;

typedef struct {
    aes_modes_t aes_mode;
    aes_key_size_t key_size;
    uint8_t Nk;
    uint8_t* key;
} aes_params_t;

aes_params_t* init_aes_params();
void free_aes_params(aes_params_t* params);
void set_aes_key(aes_params_t* param, aes_key_size_t key_size, uint8_t* key);
void SubWord(uint8_t* input);
void RotWord(uint8_t* input);
void Xor(uint8_t* input, uint8_t* val);
int getNr(int Nk);
void expand_key(uint8_t* key, uint8_t Nk, uint8_t* w);
void cipher(uint8_t* in, uint8_t* out, uint8_t* w, int Nk);

// Move these to a different header maybe?
void xor(uint8_t* input, uint8_t* val, int length);
void xor_with_return(uint8_t* input, uint8_t* val, uint8_t* ret, int length);
void add_round_key(uint8_t (*in)[4], uint8_t (*w)[4]);
void convert_to_matrix(uint8_t* in, uint8_t (*out)[4]);
void convert_to_array(uint8_t(*in)[4], uint8_t* out);
void dump_matrix(uint8_t inp[4][4]);
void print_word(uint8_t* word, int len); 
uint8_t multiply_by_two(uint8_t val);
#endif
