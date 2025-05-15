#include "fir.h"
#include "../Q_CODE/q_code.h"
#define NOF_SAMPLES 16

const float fir_coeff[NOF_SAMPLES]  = {0.034, 0.074, 0.0188, 0.0395, 0.0677, 0.0984, 0.1248, 0.1400, 0.1400, 0.1248, 0.0984, 0.0677, 0.0395, 0.0188, 0.074, 0.034};
const float firQ_coeff[NOF_SAMPLES] = {112,   243,   618,    1293,   2217,   3225,   4089,   4587,   4587,   4089,   3225,   2217,   1293,   618,    243,   112  };

float circural_buff[NOF_SAMPLES];
int16_t circural_Qbuff[NOF_SAMPLES];

static void bufferStep(float new_sample){
    uint8_t sampleCtr;
    for(sampleCtr = NOF_SAMPLES-1; sampleCtr > 0; sampleCtr--)
        circural_buff[sampleCtr] = circural_buff[sampleCtr-1];

    circural_buff[0] = new_sample;
}

static void bufferQStep(int16_t new_sample){
    uint8_t sampleCtr;
    for(sampleCtr = NOF_SAMPLES-1; sampleCtr > 0; sampleCtr--)
        circural_Qbuff[sampleCtr] = circural_Qbuff[sampleCtr-1];

    circural_Qbuff[0] = new_sample;
}

/*
    FIR_filter:
    Calculates one FIR output and gets one input
*/
float FIR_filter(float data){
    float Accumulator = 0;
    uint8_t sampleCtr;

    bufferStep(data);

    for(sampleCtr = 0; sampleCtr < NOF_SAMPLES; sampleCtr++)
        Accumulator += circural_buff[sampleCtr] * fir_coeff[sampleCtr];

    return Accumulator;
}

/*
    FIR_Init:
    Clears circural buffer
*/
void FIR_Init(void){
    uint8_t sampleCtr;
    for(sampleCtr = 0; sampleCtr < NOF_SAMPLES; sampleCtr++){
        circural_buff[sampleCtr] = 0;
    }
}

/*
    FIRQ_filter:
    Calculates one FIR output and gets one input
*/
int16_t FIRQ_filter(int16_t data){
    int32_t Accumulator = 0;
    uint8_t sampleCtr;

    bufferQStep(data);

    for(sampleCtr = 0; sampleCtr < NOF_SAMPLES; sampleCtr++)
        Accumulator += (int32_t)circural_Qbuff[sampleCtr] * (int32_t)firQ_coeff[sampleCtr];

    return (int16_t)Accumulator;
}

/*
    FIRQ_Init:
    Clears circural buffer
*/
void FIRQ_Init(void){
    uint8_t sampleCtr;
    for(sampleCtr = 0; sampleCtr < NOF_SAMPLES; sampleCtr++){
        circural_Qbuff[sampleCtr] = 0;
    }
}