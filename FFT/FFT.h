#ifndef FFT_H
#define FFT_H

#include <stdint.h>

typedef struct {
    double real;
    double imag;
} complex;


uint32_t reverseUsed(uint32_t value);
void printBits(uint32_t value);

void FFT_init();
void FFT_radix2(complex* data, uint8_t size);

#endif