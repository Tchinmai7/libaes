#include <stdio.h>
#include "utils.h"

void print_word(uint8_t* word, int len) 
{
    for (int i = 0; i < len; i++) {
        printf("%02x", word[i]); 
    }
    printf("\n\n");
}

void Xor(uint8_t* input, uint8_t* val, int length)
{
	for (int i = 0; i < length; i++) {
		input[i] = input[i] ^ val[i];
	}

#ifdef DEBUG_KEYS
	printf("Xor:\t");
	print_word(input, length);
#endif
}

void xor_with_return(uint8_t* input, uint8_t* val, uint8_t* ret, int length)
{
	for (int i = 0; i < length; i++) {
    		ret[i] = input[i] ^ val[i];
    	}

#ifdef DEBUG_KEYS
    printf("Xor with return:\t");
    print_word(ret, length);
#endif
}

int getNr(int Nk)
{
    if (Nk == 4) 
    {
        return 10;
    }
    else if (Nk == 6)
    {
        return 12;
    }
    else if (Nk == 8)
    {
        return 14;
    }
    return -1;
}

void dump_matrix(uint8_t inp[4][4]) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02x\t", inp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void convert_to_matrix(uint8_t* in, uint8_t (*out)[4])
{
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out[j][i] = in[k];
            k++;
        }
    }   
}

void convert_to_array(uint8_t(*in)[4], uint8_t* out)
{
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out[k] = in[j][i];
            k++;
        }
    }   
}

// TODO: TARUN: Change this to something else
uint8_t multiply_by_two(uint8_t val)
{
  return ((val<<1) ^ (((val>>7) & 1) * 0x1b));
}

void add_round_key(uint8_t (*in)[4], uint8_t (*w)[4]) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            in[i][j] = in[i][j] ^ w[i][j];    
        }
    }

#ifdef DEBUG_CIPHER
    printf("Add Round Key:\n");
    dump_matrix(in);
#endif
}

void get_iv(uint8_t* iv, size_t size)
{
	FILE *f;
    // This is non-blocking, but it is a PRNG.
    // /dev/random is blocking, but it is a TRNG
    // TODO: Read about attacks on urandom/random
	f = fopen("/dev/urandom", "r");
	fread(iv, size, 1, f);
	fclose(f);
}

