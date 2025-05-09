#include <stdio.h>
#include "FFT.h"

int main(){
    uint32_t someValue = 0b001101001;

    printf("Testing reversal from FFT library!");
    printf("\n Input value: \t");
    printBits(someValue);
    printf("\n Output value: \t");
    printBits(reverseUsed(someValue));
    printf("\n");

    return 0;
}