#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "padding.h"

size_t add_padding(uint8_t* messagebuf, uint8_t **output_buf, int input_msglen)
{
    size_t bytestopad;
    if ((input_msglen % 16) == 0) {
        bytestopad = 16;
        *output_buf = malloc(input_msglen + 16);
        memcpy(*output_buf,messagebuf,input_msglen);
        memset(*output_buf + input_msglen, bytestopad, 16);
        return input_msglen + bytestopad;
    }

    else {
        bytestopad = 16 - (input_msglen % 16);
        *output_buf = malloc(input_msglen + bytestopad);
        memcpy(*output_buf, messagebuf, input_msglen);
        memset(*output_buf + input_msglen, bytestopad, bytestopad);
        return input_msglen + bytestopad;
    }
}

size_t strip_padding(uint8_t* padbuf,  uint8_t **outputbuf, int buflen)
{
    uint8_t lastbyte = padbuf[buflen - 1];
    *outputbuf = malloc(buflen - lastbyte);
    memcpy(*outputbuf, padbuf, (buflen - lastbyte));
    return (buflen - lastbyte);
}

#ifdef PADDING_TEST
int main()
{
    uint8_t message[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t* padded_msg = NULL;
    uint8_t padlen = addpadding(message, &padded_msg,  16);
    print_word(padded_msg, padlen);
    uint8_t* stripped_msg =  NULL;
    uint8_t orig_len = strippadding(padded_msg, &stripped_msg, padlen);
    print_word(stripped_msg, orig_len);
    return 0;
}
#endif
