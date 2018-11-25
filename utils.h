// Don't add _ before include guards - DCL37-C in SEI guide
#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#define WORD_SIZE 16
int getNr(int Nk);
void Xor(uint8_t* input, uint8_t* val, int length);
void xor_with_return(uint8_t* input, uint8_t* val, uint8_t* ret, int length);
void add_round_key(uint8_t (*in)[4], uint8_t (*w)[4]);
void convert_to_matrix(uint8_t* in, uint8_t (*out)[4]);
void convert_to_array(uint8_t(*in)[4], uint8_t* out);
void dump_matrix(uint8_t inp[4][4]);
void print_word(uint8_t* word, int len); 
uint8_t multiply_by_two(uint8_t val);
void get_random_bytes(uint8_t* result, size_t size);
#endif
