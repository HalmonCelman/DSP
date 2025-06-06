#include <stdio.h>
#include "fir.h"
#include "iir.h"

#define NUM_OF_SAMPLES 16

void main(){
    float response[NUM_OF_SAMPLES];
    int16_t responseQ[NUM_OF_SAMPLES];
    float responseIIR[NUM_OF_SAMPLES];
    int16_t responseIIRQ[NUM_OF_SAMPLES];
    uint8_t sampleNum;

    FIR_Init();
    FIRQ_Init();

    // create unit impulse signal and pass it to FIR
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++) {
        response[sampleNum]     = sampleNum ? FIR_filter(0)  : FIR_filter(1);
        responseQ[sampleNum]    = sampleNum ? FIRQ_filter(0) : FIRQ_filter(1);
        responseIIR[sampleNum]  = sampleNum ? IIR_filter(0)  : IIR_filter(1);
        responseIIRQ[sampleNum] = sampleNum ? IIR_filterQ(0) : IIR_filterQ(32767); // 1 in Q0.15
    }
    // FIR
    printf("Testing FIR library, FIR on float response to unit impulse signal:\n");
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++)
        printf("%f ", response[sampleNum]);

    // FIRQ
    printf("\n\nFIR on Q_CODE response to unit impulse signal:\n");
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++)
        printf("%d ", responseQ[sampleNum]);

    // IIR
    printf("\n\nIIR response to unit impulse signal:\n");
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++)
        printf("%f ", responseIIR[sampleNum]);

    // IIRQ
    printf("\n\nIIRQ response to unit impulse signal:\n");
    for(sampleNum = 0; sampleNum < NUM_OF_SAMPLES; sampleNum++)
        printf("%d ", responseIIRQ[sampleNum]);
    printf("\n");
}