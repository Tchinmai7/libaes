#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"
//TODO: @Sandhya: Replace this with the derivation
uint8_t sbox[16][16] =  {
 {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
 {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
 {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
 {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
 {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
 {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
 {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
 {0x51 ,0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
 {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
 {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
 {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
 {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
 {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
 {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
 {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
 {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

#define Nb 4
uint8_t get_sbox_value(uint8_t val) 
{
    uint8_t low = val & 0x0F;
    uint8_t high = (val & 0xF0) >> 4;
    return sbox[high][low];
}

void SubWord(uint8_t* input) 
{
    uint8_t temp[4];
#ifdef DEBUG_KEYS
    printf("SubWord: ");
#endif
    for (int i = 0; i < 4; i++) {
        temp[i] = get_sbox_value(input[i]);
#ifdef DEBUG_KEYS
        printf("%02x", temp[i]);
#endif
    }
#ifdef DEBUG_KEYS
    printf("\t");
#endif
    memcpy(input, temp, 4);
}

void RotWord(uint8_t* input) 
{
    uint8_t temp[4] = {0x00};
    temp[0] = input[1];
    temp[1] = input[2];
    temp[2] = input[3];
    temp[3] = input[0];

#ifdef DEBUG_KEYS
    printf("RotWord: %02x%02x%02x%02x\t", temp[0], temp[1], temp[2], temp[3]);
#endif

    memcpy(input, temp, 4);
}

void Xor(uint8_t* input, uint8_t* val)
{
    input[0] = input[0] ^ val[0];
    input[1] = input[1] ^ val[1];
    input[2] = input[2] ^ val[2];
    input[3] = input[3] ^ val[3];

#ifdef DEBUG_KEYS
    printf("Xor: %02x%02x%02x%02x\t", input[0], input[1], input[2], input[3]);
#endif
}
void XorWithReturn(uint8_t* input, uint8_t* val, uint8_t* ret)
{
    ret[0] = input[0] ^ val[0];
    ret[1] = input[1] ^ val[1];
    ret[2] = input[2] ^ val[2];
    ret[3] = input[3] ^ val[3];

#ifdef DEBUG_KEYS
    printf("Xor with Return: %02x%02x%02x%02x\n", ret[0], ret[1], ret[2], ret[3]);
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

// TODO: @Mahati: Replace this with the derivation 
static const uint8_t Rcon[11] = { 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

void expand_key(uint8_t* key, uint8_t Nk, uint8_t* w)
{
    uint8_t i = 0;
    uint8_t temp[4] = {0x00};
    uint8_t rcon_key[4] = {0x00};
    int Nk_bytes = Nk * 4;
    int Nr = getNr(Nk);
    if (Nr < 0 ) {
        printf("Fatal Error., invalid keysize\n");
        return;
    }
    while ( i <  4 * Nk ) {
        temp [0] = key[i];
        temp [1] = key[i + 1];
        temp [2] = key[i + 2];
        temp [3] = key[i + 3];

#ifdef DEBUG_KEYS
        printf("W: %02x%02x%02x%02x\n", temp[0], temp[1], temp[2], temp[3]);
#endif

        memcpy(w + i , temp, 4);
        i += 4;
    }
    i = Nk;
    while (i < Nb * (Nr + 1)) {
            int j = i * 4;
            memcpy(temp, w + j - 4 ,4);

#ifdef DEBUG_KEYS
            printf("I: %d, Temp: %02x%02x%02x%02x\t",i,  temp[0], temp[1], temp[2], temp[3]);
#endif

            if (i % Nk == 0) { 
                RotWord(temp);
                SubWord(temp);
                rcon_key[0] = Rcon[i/Nk];
                Xor(temp, rcon_key);
            }
            else if ((Nk > 6) &&  (i % Nk == 4)) {
                SubWord(temp);
            }

#ifdef DEBUG_KEYS
            printf("W[i-Nk]: %02x%02x%02x%02x\n", *(w + j - Nk_bytes), *(w + j - Nk_bytes + 1), *(w + j - Nk_bytes + 2), *(w + j - Nk_bytes + 3));
#endif

            XorWithReturn(w + j - Nk_bytes , temp, w + j);
            i = i + 1;

#ifdef DEBUG_KEYS
            printf("\n");
#endif
    }
}

void dump_matrix(uint8_t inp[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02x\t", inp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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

void sub_bytes(uint8_t (*in)[4]) 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            in[i][j] = get_sbox_value(in[i][j]);
        }
    }

#ifdef DEBUG_CIPHER
    printf("Sub Bytes:\n");
    dump_matrix(in);
#endif
}

void shift_rows(uint8_t (*in)[4]) 
{
    // Doing this lazily now. Might have to cleanup later
    uint8_t temp = 0x00;
    temp = in[1][0];
    in[1][0] = in[1][1];
    in[1][1] = in[1][2];
    in[1][2] = in[1][3];
    in[1][3] = temp;

    // Swap [2][0] and [2][2]
    temp = in[2][0];
    in[2][0] = in[2][2];
    in[2][2] = temp;

    // Swap [2][1] and [2][3]
    temp = in[2][1];
    in[2][1] = in[2][3];
    in[2][3] = temp;

    temp = in[3][0];
    in[3][0] = in[3][3];
    in[3][3] = in[3][2]; 
    in[3][2] = in[3][1];
    in[3][1] = temp;

#ifdef DEBUG_CIPHER
    printf("Shift Rows:\n");
    dump_matrix(in);
#endif
}

// TODO: TARUN: Change this to something else
uint8_t multiply_by_two(uint8_t val)
{
  return ((val<<1) ^ (((val>>7) & 1) * 0x1b));
}

void mix_columns(uint8_t (*in)[4]) 
{
    uint8_t old_col[4] = {0x00};
    for (int i = 0; i < 4; i++) {
        old_col[0] = in[0][i];
        old_col[1] = in[1][i];
        old_col[2] = in[2][i];
        old_col[3] = in[3][i];
        in[0][i] = (multiply_by_two(old_col[0])) ^ (multiply_by_two(old_col[1]) ^ old_col[1]) ^ old_col[2] ^ old_col[3];
        in[1][i] = old_col[0] ^ multiply_by_two(old_col[1]) ^ (multiply_by_two(old_col[2]) ^ old_col[2]) ^ old_col[3];
        in[2][i] = old_col[0] ^ old_col[1] ^ multiply_by_two(old_col[2]) ^ (multiply_by_two(old_col[3]) ^ old_col[3]);
        in[3][i] = (multiply_by_two(old_col[0]) ^ old_col[0]) ^ old_col[1] ^ old_col[2] ^ multiply_by_two(old_col[3]);
    }

#ifdef DEBUG_CIPHER
    printf("Mix Columns:\n");
    dump_matrix(in);
#endif
}

void cipher(uint8_t* in, uint8_t* out, uint8_t* w, int Nk)
{
    uint8_t state[4][4] = {0x00};
    uint8_t temp[16] = {0x00}; 
    memcpy(temp, w, 16);
    uint8_t roundKey[4][4] = {0x00};
    convert_to_matrix(in, state);

#ifdef DEBUG_CIPHER
    printf("State Matrix:\n");
    dump_matrix(state);
#endif

    convert_to_matrix(temp, roundKey);

#ifdef DEBUG_CIPHER
    printf("Round Key:\n");
    dump_matrix(roundKey);
#endif
    
    add_round_key(state, roundKey);
    
    int Nr = getNr(Nk);
    int round = 1;

    for (round = 1; round < Nr; round++) {
#ifdef DEBUG_CIPHER
        printf("Starting Round:[%d]\n", round);
#endif
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        memcpy(temp, w + (round * 4 * 4), 16);
        convert_to_matrix(temp, roundKey);
        add_round_key(state, roundKey);
    }

#ifdef DEBUG_CIPHER
    printf("Starting Round:[%d]\n", round);
#endif

    sub_bytes(state);
    shift_rows(state);
    memcpy(temp, w + (Nr * 4 * 4), 16);
    convert_to_matrix(temp, roundKey);
    add_round_key(state, roundKey);
    convert_to_array(state, out);
}
