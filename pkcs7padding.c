#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t* addpadding(uint8_t* messagebuf, size_t msglen)
{
    size_t bytestopad;
    if((msglen%16)==0){
    bytestopad=16-msglen;
    printf("\n\nbytestopad=%02x\n\n", bytestopad);
    uint8_t *newbuf=malloc(msglen+16);
    memcpy(newbuf,messagebuf,msglen);
    memset(newbuf+msglen,bytestopad,16);
    return newbuf;
    }
     
    else{
    bytestopad=16-(msglen%16);
    printf("\n\nbytestopad=%02x i.e %d\n\n", bytestopad,bytestopad);
    uint8_t *newbuf=malloc(msglen+bytestopad);
    memcpy(newbuf,messagebuf,msglen);
    memset(newbuf+msglen,bytestopad,bytestopad);
    return newbuf;
    }
    
}



uint8_t* strippadding(uint8_t* padbuf, int buflen)
{

	size_t lastbyte=padbuf[buflen-1];
	//printf("\n\n%d", lastbyte);
	uint8_t *newbuf=malloc(buflen-(int)lastbyte);
	memcpy(newbuf,padbuf,buflen-(int)lastbyte);
	return newbuf;

}

void print_word(uint8_t* word, int len) 
{
    for (int i = 0; i < len; i++) {
        printf("%02x", word[i]); 
    }
    printf("\n\n");
}
int main()
{
    //uint8_t message[19] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x12, 0x13, 0x14};
    //uint8_t message[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t message[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    uint8_t* padded_msg = addpadding(message, 16);
    print_word(padded_msg,32);
    uint8_t* stripped_msg = strippadding(padded_msg,32);
    print_word(stripped_msg, 16);
    return 0;
}

