#include <stdio.h>
#include "q_code.h"

void main(){
    uint16_t a, b;

    a = 0x1000;
    b = 0x0001;

    printf("a: %f \n\r", calculateQ115(a));

    printOperation(a, b, Q_add(a, b), '+');
    printOperation(a, b, Q_sub(a, b), '-');
    printOperation(a, b, Q_mul(a, b), '*');
    printOperation(a, b, Q_div(a, b), '/');
}