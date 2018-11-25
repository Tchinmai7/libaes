#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"
#include "padding.h"
#include "utils.h"

size_t aes_ctr_mode_encrypt(uint8_t* input, uint8_t** output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    int block_size = input_length / 16;
    int last_block_size = input_length  % 16;
    uint8_t iv[16] = {0x00};
    uint64_t ctr = 0;
    // Get a random byte string of 128 bits
    // Use the last 64bits as the ctr
    get_random_bytes(iv, 16);
    memcpy(&ctr, iv + 8 , 8);
    uint8_t block[16] = {0x00};
    uint8_t temp_op[16] = {0x00};

    // IV is in the first 16 bytes of the cipher text
    memcpy(*output, iv, 16);
    //to account for the IV that's appended.
    size_t output_length = 1;
    for (int i = 0; i < block_size; i++) {
        // First encrypt the IV
        cipher(iv, temp_op, expanded_key, Nk);
        // Increment the counter of the IV.
        ctr ++;
        // Copy the ctr to the last 8 bytes of IV
        memcpy(iv+8, &ctr, 8);
        memcpy(block, input + (i * 16), 16);
        // Xor the encrypted val with the plain text
        Xor(temp_op, block, 16);
        memcpy(*output + (i * 16) + 16, temp_op, 16);
        output_length ++;
    }
    // Deal with the last block here
    cipher(iv, temp_op, expanded_key, Nk);
    memcpy(block, input + (block_size * 16), last_block_size);
    // Xor the encrypted val with the plain text
    Xor(temp_op, block, last_block_size);
    memcpy(*output + (block_size * 16) + 16, temp_op, last_block_size);
    return (output_length * 16) + last_block_size;
}

size_t aes_ofb_mode_encrypt(uint8_t* input, uint8_t** output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    int block_size = input_length / 16;
    int last_block_size = input_length % 16;
    uint8_t iv[16] = {0x00};
    get_random_bytes(iv, 16);
    uint8_t block[16] = {0x00};
    uint8_t temp_op[16] = {0x00};

    // IV is in the first 16 bytes of the cipher text
    memcpy(*output, iv, 16);
    //to account for the IV that's appended.
    size_t output_length = 1;
    for (int i = 0; i < block_size; i++) {
        // First encrypt the IV
        cipher(iv, temp_op, expanded_key, Nk);
        // Use the encrypted value as the IV for next
        memcpy(iv, temp_op,16);
        memcpy(block, input + (i * 16), 16);
        // Xor the encrypted val with the plain text
        Xor(temp_op, block, 16);
        memcpy(*output + (i * 16) + 16, temp_op, 16);
        output_length ++;
    }
    // Process the last incomplete block here
    cipher(iv, temp_op, expanded_key, Nk);
    memcpy(iv, temp_op, 16);
    memcpy(block, input + (block_size * 16), last_block_size);
    // Xor the encrypted val with the plain text
    Xor(temp_op, block, last_block_size);
    memcpy(*output + (block_size * 16) + 16, temp_op, last_block_size);
    
    return (output_length * 16) + last_block_size;
}

size_t aes_cfb_mode_encrypt(uint8_t* input, uint8_t** output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    uint8_t iv[16] = {0x00};
    get_random_bytes(iv, 16);
    int block_size = input_length / 16;
    int last_block_size = input_length % 16;
    uint8_t block[16] = {0x00};
    uint8_t temp_op[16] = {0x00};

    // IV is in the first 16 bytes of the cipher text
    memcpy(*output, iv, 16);
    //to account for the IV that's appended.
    size_t output_length = 1;
    for (int i = 0; i < block_size; i++) {
        // First encrypt the IV
        cipher(iv, temp_op, expanded_key, Nk);
        // Then Xor with plain text
        // Use the result as the IV for next
        memcpy(block, input + (i * 16), 16);
        Xor(temp_op, block, 16);
        memcpy(*output + (i * 16) + 16, temp_op, 16);
        memcpy(iv, temp_op, 16);
        output_length ++;
    }
    // Handle the last incomplete block here
    cipher(iv, temp_op, expanded_key, Nk);
    // Then Xor with `last_block_size` bytes of plain text
    memcpy(block, input + (block_size * 16), last_block_size);
    Xor(temp_op, block, last_block_size);
    memcpy(*output + (block_size * 16) + 16, temp_op, last_block_size);
    
    return (output_length * 16) + last_block_size;
}

size_t aes_ecb_mode_encrypt(uint8_t* input, uint8_t** output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    int block_size = input_length / 16;
    uint8_t block[16] = {0x00};
    uint8_t temp_op[16] = {0x00};

    size_t output_length = 0;
    for (int i = 0; i < block_size; i++) {
        memcpy(block, input + (i * 16), 16);
        cipher(block, temp_op, expanded_key, Nk);
        memcpy(*output + (i * 16), temp_op, 16);
        output_length++;
    }
    return output_length * 16;
}

size_t aes_cbc_mode_encrypt(uint8_t* input, uint8_t** output, uint8_t Nk, uint8_t* expanded_key, int input_length) 
{
    uint8_t iv[16] = {0x00};
    get_random_bytes(iv, 16);
    // TODO: Rename as num_blocks
    int block_size = input_length / 16;
    uint8_t block[16] = {0x00};
    uint8_t temp_op[16] = {0x00};

    // IV is in the first 16 bytes of the cipher text
    memcpy(*output, iv, 16);
    //to account for the IV that's appended.
    size_t output_length = 1;
    for (int i = 0; i < block_size; i++) {
        memcpy(block, input + (i * 16), 16);
        Xor(block, iv, 16);
        cipher(block, temp_op, expanded_key, Nk);
        // a +16 is needed because of the IV
        memcpy(*output + ( i * 16) + 16, temp_op, 16);
        memcpy(iv, temp_op, 16);
        output_length++;
    }
    return output_length * 16;
}

size_t encrypt(aes_params_t* aes_params, uint8_t* ip, uint8_t** output, int ip_len)
{
    int Nr = getNr(aes_params->Nk);
    // the last *4 is to convert words to bytes
    int len = 4 * (Nr + 1) * 4;
    uint8_t expanded_key[len]; 
    expand_key(aes_params->key, aes_params->Nk, expanded_key);
    uint8_t* input = NULL; 
    // Pad the message. We don't care if the message is a multiple of 16. Always Pad.
    size_t input_length = add_padding(ip, &input, ip_len);
    size_t output_length = 0;
    switch(aes_params->aes_mode) {
        case AES_MODE_CBC:
            // We know that the length has to be input_length + 16 (for the IV)
            //*output = malloc(input_length + 16);
            *output = calloc(input_length + 16, 1);
            output_length = aes_cbc_mode_encrypt(input, output, aes_params->Nk, expanded_key, input_length);
            break;
        case AES_MODE_ECB:
            // We know that the length has to be input_length
            // *output = malloc(input_length);
            *output = calloc(input_length, 1);
            output_length = aes_ecb_mode_encrypt(input, output, aes_params->Nk, expanded_key, input_length);
            break;
        case AES_MODE_CTR:
            // AES with CTR mode needs no padding.
            *output = calloc(ip_len + 16, 1);
            output_length = aes_ctr_mode_encrypt(ip, output, aes_params->Nk, expanded_key, ip_len);
            break;
        case AES_MODE_OFB:
            // AES with OFB mode needs no padding.
            *output = calloc(ip_len + 16, 1);
            output_length = aes_ofb_mode_encrypt(ip, output, aes_params->Nk, expanded_key, ip_len);
            break;
        case AES_MODE_CFB:
            // AES with CFB mode needs no padding.
            *output = calloc(ip_len + 16, 1);
            output_length = aes_cfb_mode_encrypt(ip, output, aes_params->Nk, expanded_key, ip_len);
            break;
        default:
            break;
    }

    free(input);
    return output_length;
}
