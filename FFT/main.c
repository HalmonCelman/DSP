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

    complex data[4];
    for(int i=0; i<8; i++){
        data[i].imag = 0;
        data[i].real = i+1;
    }

    FFT_init();
    FFT_radix2(data, 4);

    return 0;
}