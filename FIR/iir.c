#include "iir.h"

#define BUFOR_LENGTH 3

// filter parameters
const int16_t A_Q[] = {16384, -20732, 10080}; // Q2.14 
const int16_t B_Q[] = {2029, 4058, 2029};     // Q0.15

// input is in Q0.15
int16_t IIR_filterQ(int16_t in_sample) {
    static int16_t in_rec[BUFOR_LENGTH] = {0};
    static int16_t out_rec[BUFOR_LENGTH] = {0};

    int32_t acc = ((int32_t)in_sample * B_Q[0]) >> 15; // Q0.30 => Q0.15
    for (int i = 1; i < BUFOR_LENGTH; i++) {
        // Feedforward – Q0.30 => Q0.15
        acc += ((int32_t)in_rec[i - 1] * B_Q[i]) >> 15;
        // Feedback  – Q2.29 => Q0.15 
        acc -= ((int32_t)out_rec[i - 1] * A_Q[i]) >> 16;
    }

    // Saturation to 16 bits
    if (acc > 32767) acc = 32767;
    else if (acc < -32768) acc = -32768;

    // History
    for (int i = BUFOR_LENGTH - 1; i > 0; i--) {
        in_rec[i] = in_rec[i - 1];
        out_rec[i] = out_rec[i - 1];
    }

    in_rec[0] = in_sample;
    out_rec[0] = (int16_t)acc;

    return (int16_t)acc;
}

// filter parameters
const float B[] = {0.0619, 0.1239, 0.0619};
const float A[] = {1.0, -1.2654, 0.6153};

float IIR_filter(float in_sample) {
    //previous samples
    static float in_rec[BUFOR_LENGTH]  = {0,0,0};
    static float out_rec[BUFOR_LENGTH] = {0,0,0};

    
    float acc = in_sample * B[0]; // accumulator
    for(int i = 1; i<BUFOR_LENGTH; i++){
        // Feedforward
        acc += in_rec[i-1] * B[i];
        // Feedback
        acc -= out_rec[i-1] * A[i];
    }
    
    // History update
    for(int i = BUFOR_LENGTH-1; i>0; i--){
        in_rec[i] = in_rec[i-1];
        out_rec[i] = out_rec[i-1];
    }
    in_rec[0] = in_sample;
    out_rec[0] = acc;
    return acc;
}