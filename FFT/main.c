#include <stdio.h>
#include "fft.h"

int main(){
    printf("\nTesting FFT_radix2!\n");
    
    for(int test=0; test<4; test++){
        printf("=========================\n");
        printf("TEST %d\n", test+1);
        printf("=========================\n");
        printf("Input data:\n");
        complex data[4][32];
        for(int i=0; i<32; i++){
            switch (test)
            {
            case 0: data[test][i].real = i   ? 0 : 1;   break;
            case 1: data[test][i].real = 1;             break;
            case 2: data[test][i].real = i%2 ?  1 : -1; break;
            case 3: 
                switch (i%4){
                case 0: data[test][i].real = 0;     break; 
                case 1: data[test][i].real = -1;    break; 
                case 2: data[test][i].real = 0;     break; 
                case 3: data[test][i].real = 1;     break; 
                }
            break;
            }
            data[test][i].imag = 0;
            printf("[%d] %f+%fi\n",i,data[test][i].real, data[test][i].imag);
        }

        FFT_init();
        FFT_radix2(data[test], 32);

        printf("Output data:\n");
        for(int i=0; i<32; i++){
            printf("[%d] %f+%fi\n",i,data[test][i].real, data[test][i].imag);
        }
    }
    return 0;
}