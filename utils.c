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
}

void xor_with_return(uint8_t* input, uint8_t* val, uint8_t* ret, int length)
{
	for (int i = 0; i < length; i++) {
    		ret[i] = input[i] ^ val[i];
    	}
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

uint8_t multiply_by_two(uint8_t val)
{
  return ((val << 1) ^ (((val >> 7) & 1) * 0x1b));
}

void add_round_key(uint8_t (*in)[4], uint8_t (*w)[4]) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            in[i][j] = in[i][j] ^ w[i][j];    
        }
    }
}

void get_random_bytes(uint8_t* result, size_t size)
{
	FILE *f;
    // This is non-blocking, and a CPRNG.
    // A popular myth is that /dev/random is `safer` than /dev/urandom, but its not the case.
    // This is the recommended method of fetchig random bytes. It is safe to read upto 32mb of data
    // in one shot from /dev/urandom
	f = fopen("/dev/urandom", "r");
	fread(result, size, 1, f);
	fclose(f);
}
