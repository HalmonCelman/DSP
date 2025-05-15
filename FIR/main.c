#include <stdio.h>
#include "fir.h"

#define NUM_OF_SAMPLES 16

void main(){
    float response[NUM_OF_SAMPLES];
    int16_t responseQ[NUM_OF_SAMPLES];
    uint8_t sampleNum;

    FIR_Init();
    FIRQ_Init();

    // create unit impulse signal and pass it to FIR
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++) {
        response[sampleNum]  = sampleNum ? FIR_filter(0)  : FIR_filter(1);
        responseQ[sampleNum] = sampleNum ? FIRQ_filter(0) : FIRQ_filter(1);
    }
    // print out result
    printf("Testing FIR library, FIR on float response to unit impulse signal:\n");
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++)
        printf("%f ", response[sampleNum]);
    printf("\n\nFIR on Q_CODE response to unit impulse signal:\n");
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++)
        printf("%d ", responseQ[sampleNum]);
    printf("\n");
}