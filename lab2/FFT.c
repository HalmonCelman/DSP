#include <stdio.h>
#include "FFT.h"

uint32_t reverseUsed(uint32_t value){
    // algorithm modified from https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
    uint32_t reversed = value & 1;

    for (value >>= 1; value; value >>= 1){
        reversed <<= 1;
        reversed |= value & 1;
    }

    return reversed;
}

void printBits(uint32_t value){
    while(value){
        printf("%u", value & 1);
        value >>= 1;
    }
}