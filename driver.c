#include <stdio.h>
#include <stdlib.h>
#include "aes.h"
int main(int argc, char* argv[])
{
    uint8_t temp[4] = { 0x2a, 0x6c, 0x76 ,0x05};
    uint8_t key[4] = {0x00};
    RotWord(temp);
    SubWord(temp);
    key[0] = 0x02;
    Xor(temp, key);
    return 0;
}
