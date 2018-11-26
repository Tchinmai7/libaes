#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

void print_word(uint8_t* word, int len) 
{
    assert(valid_pointer(word) != 0);
    for (int i = 0; i < len; i++) {
        printf("%02x", word[i]); 
    }
    printf("\n\n");
}

void Xor(uint8_t* input, uint8_t* val, int length)
{
    assert(valid_pointer(input) != 0);
    assert(valid_pointer(val) != 0);
	for (int i = 0; i < length; i++) {
		input[i] = input[i] ^ val[i];
	}
}

void xor_with_return(uint8_t* input, uint8_t* val, uint8_t* ret, int length)
{
    assert(valid_pointer(input) != 0);
    assert(valid_pointer(val) != 0);
    assert(valid_pointer(ret) != 0);
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

void dump_matrix(uint8_t inp[WORD_SIZE][WORD_SIZE]) 
{
    for (int i = 0; i < WORD_SIZE; i++) {
        for (int j = 0; j < WORD_SIZE; j++) {
            printf("%02x\t", inp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void convert_to_matrix(uint8_t* in, uint8_t (*out)[WORD_SIZE])
{
    assert(valid_pointer(in) != 0);
    assert(valid_pointer(out) != 0);
    int k = 0;
    for (int i = 0; i < WORD_SIZE; i++) {
        for (int j = 0; j < WORD_SIZE; j++) {
            out[j][i] = in[k];
            k++;
        }
    }   
}

void convert_to_array(uint8_t(*in)[WORD_SIZE], uint8_t* out)
{
    assert(valid_pointer(in) != 0);
    assert(valid_pointer(out) != 0);
    int k = 0;
    for (int i = 0; i < WORD_SIZE; i++) {
        for (int j = 0; j < WORD_SIZE; j++) {
            out[k] = in[j][i];
            k++;
        }
    }   
}

uint8_t multiply_by_two(uint8_t val)
{
  return ((val << 1) ^ (((val >> 7) & 1) * 0x1b));
}

void add_round_key(uint8_t (*in)[WORD_SIZE], uint8_t (*w)[WORD_SIZE]) 
{
    //MEM10-C: check pointer validity
    assert(valid_pointer(in) != 0);
    assert(valid_pointer(w) != 0);
    for (int i = 0; i < WORD_SIZE; i++) {
        for (int j = 0; j < WORD_SIZE; j++) {
            in[i][j] = in[i][j] ^ w[i][j];    
        }
    }
}

void get_random_bytes(uint8_t* result, size_t size)
{
    //always check if the pointer is valid
    assert(valid_pointer(result) != 0);
    // This is non-blocking, and a CPRNG.
    // A popular myth is that /dev/random is `safer` than /dev/urandom, but its not the case.
    // This is the recommended method of fetchig random bytes. It is safe to read upto 32mb of data
    // in one shot from /dev/urandom
    // implement POS01-C: Prevent following symlinks
    int fd = open("/dev/urandom", O_NOFOLLOW | O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        printf("Error opening /dev/urandom. Aborting \n");
        abort();
    }
    size_t bytes_read = read(fd, result, size);
    int ret = close(fd);
    assert(bytes_read == size);
    assert(ret >= 0);
#if 0
	FILE *f;
	f = fopen("/dev/urandom", "r");
    if (f == NULL) {
        printf("Error opening /dev/urandom. Aborting \n");
        abort();
    }
	size_t val = fread(result, size, 1, f);
    assert(val == 1);
	assert(fclose(f) >= 0);
#endif
}

int valid_pointer(void *p)
{
  extern char _etext;
  return (p != NULL) && ((char*) p > &_etext);
}
