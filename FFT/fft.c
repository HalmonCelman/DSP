#include <stdio.h>
#include <math.h>
#include "FFT.h"

#define NOF_SAMPLES 4

complex factors[NOF_SAMPLES/2];

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

void FFT_init(){
    uint8_t i;
    for(i=0; i<NOF_SAMPLES/2; i++){
        factors[i].real = cos(-2 * M_PI * i / NOF_SAMPLES);
        factors[i].imag = sin(-2 * M_PI * i / NOF_SAMPLES);
    }
}

static complex c_mul(complex a, complex b){
    complex tmp;
    tmp.real = a.real * b.real - a.imag * b.imag;
    tmp.imag = a.imag * b.real + a.real * b.imag;

    printf("mul %f + %fj\n", tmp.real, tmp.imag);
    return tmp;
}

static complex c_sum(complex a, complex b){
    complex tmp;
    tmp.real = a.real + b.real;
    tmp.imag = a.imag + b.imag;
    return tmp;
}

static complex c_sub(complex a, complex b){
    complex tmp;
    tmp.real = a.real - b.real;
    tmp.imag = a.imag - b.imag;
    return tmp;
}

static void butterfly(complex* x, complex* y, complex factor){
    complex temp = *x;
    *x = c_sum(temp, c_mul(factor,*y));
    *y = c_sub(temp, c_mul(factor,*y));
}

void FFT_radix2(complex* data, uint8_t size){
    if(size == 2){
        butterfly(&data[0], &data[1], factors[0]);
    } else{
        for(int i=0; i<size; i+=4){
            butterfly(&data[i], &data[i+2], factors[i/4]);
            printf("BF1: real %f imag %f \n", data[i].real, data[i].imag);
            printf("BF2: real %f imag %f \n", data[i+2].real, data[i+2].imag);

            butterfly(&data[i+1], &data[i+3], factors[i/4+1]);
            printf("2BF1: real %f imag %f \n", data[i+1].real, data[i+1].imag);
            printf("2BF2: real %f imag %f \n", data[i+3].real, data[i+3].imag);
        }
        /*
        for(int i=0; i<size; i+=4){
            for(int j=0; j<size/2; j++){
                complex tmp  = data[i+j];
                complex tmp2 = data[i+j+1];
                data[i/4+2*j]   = c_sum(tmp, c_mul(factors[j], tmp2));
                data[i/4+2*j+1] = c_sub(tmp, c_mul(factors[j], tmp2));

                printf("f_r: %f, f_i: %f, o1_r: %f, o1_i: %f, o2_r: %f, o2_i: %f \n --- \n", 
                    factors[j].real,
                    factors[j].imag,
                    data[i/4+2*j].real,
                    data[i/4+2*j].imag,
                    data[i/4+2*j+1].real,
                    data[i/4+2*j+1].imag
                );
            }
        } */
    }
}