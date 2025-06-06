#include <stdio.h>
#include <math.h>
#include "fft.h"

#define NOF_SAMPLES 32

complex factors[NOF_SAMPLES/2];


// algorithm modified from https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
static uint32_t reverseUsed(uint32_t value, uint8_t bits) {
    uint32_t reversed = 0;
    for (uint8_t i = 0; i < bits; i++) {
        reversed <<= 1;
        reversed |= (value & 1);
        value >>= 1;
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
    for(i = 0; i < NOF_SAMPLES / 2; i++){
        factors[i].real = cos(-2 * M_PI * i / NOF_SAMPLES);
        factors[i].imag = sin(-2 * M_PI * i / NOF_SAMPLES);
    }
}

static complex c_mul(complex a, complex b){
    complex tmp;
    tmp.real = a.real * b.real - a.imag * b.imag;
    tmp.imag = a.imag * b.real + a.real * b.imag;
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

void FFT_radix2(complex* data, uint32_t size) {
    uint32_t bits = 0;
    uint32_t temp_size = size;
    while (temp_size >>= 1) bits++;

    // Bit reversal permutacja
    for (uint32_t i = 0; i < size; i++) {
        uint32_t rev = reverseUsed(i, bits);
        if (rev > i) {
            complex tmp = data[i];
            data[i] = data[rev];
            data[rev] = tmp;
        }
    }

    // FFT iteracyjne, wykorzystując butterfly
    for (uint32_t s = 1; s <= bits; s++) {
        uint32_t m = 1 << s;           // wielkość grupy
        uint32_t m2 = m >> 1;          // połowa grupy
        uint32_t step = size / m;

        for (uint32_t k = 0; k < size; k += m) {
            for (uint32_t j = 0; j < m2; j++) {
                butterfly(&data[k + j], &data[k + j + m2], factors[j * step]);
            }
        }
    }
}