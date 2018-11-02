#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>

uint8_t* addpadding(uint8_t *messagebuf, size_t msglen)
{
    // Msglen % 16 == 0 (blocksize is perfect) - add one fully padded block i.e, bytes to pad = 16
    // bytes to pad = msglen % 16
    // msglen will be input buffer size. 
    // malloc(msglen+bytestopad);
    // memcpy(newbuf, messagebuf, msglen);
    // memset(padding logic);
    // %02x is hex 
    // return newbuf
	size_t	padlen, padbuflen; //padlen is the length of padded bits; padbuflen is length of msg after padding
	uint8_t *padbuf; //msg after padding
	uint8_t multiple; //multiple is Nk value (128 or 192 or 256)
//Have to compute padbuflen
	padlen = multiple - (msglen % multiple);
	if (messagebuf == NULL)
		msglen = 0;

	//if (padlen > padbuflen - datalen) {
		//return (CKR_DATA_LEN_RANGE); //Not sure of the return values
	//}

	bcopy(messagebuf, padbuf, msglen); 
	void memset (padbuf + msglen, padlen & 0xff, padlen);

	return (print_word(padbuf, padbuflen)); 
}

// uncomment the commented portions if required

uint8_t* strippadding(uint8_t *padbuf, size_t *plen)
{
    // Get a padded buffer
    // read the uint8_t lastbyte = padbuf[buflen - 1]
    // (or) lastbyte = padbuf + buflen - 1
    // newbuf = malloc(plen - int(lastbyte))
    // memcpy(newbuf, padbuf, plen-int(lastbyte))
	int	i;
	size_t	padlen;

	/* Recover the padding value, even if padbuf has trailing nulls */
	//while (*plen > 0 && (padlen = padbuf[*plen - 1]) == 0)
		//(*plen)--;

	/* Must have non-zero padding */
	//if (padlen == 0)
		//return (CKR_ENCRYPTED_DATA_INVALID); //Not sure of the return values

	for (i = 0; i < padlen && (*plen - 1 - i) >= 0; i++) {    //Count back from all padding bytes
		//if (padbuf[*plen - 1 - i] != (padlen & 0xff))
			//return (CKR_ENCRYPTED_DATA_INVALID);
	}
	*plen -= i;
	return (print_word(padbuf,plen));
}


int main()
{
    uint8_t message[12] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc};
    /*
    uint8_t* padded_msg = addpadding(message, 12);
    print_word(padded_msg, 16);
    uint8_t *stripped_msg = strippadding(padded_msg, 16);
    print_word(stripped_msg, 12);
    */
    //print_word(message,16);
    //addpadding(uint8_t message,size_t messagelen) //compute messagelen

    return 0;
}
