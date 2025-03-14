#include <stdio.h>
#include <stdint.h>

/*
    Prints Q2.30 code in binary format
*/
void print_q230(int32_t number, uint8_t dotpos){
    for(int ctr=0; ctr<32; ctr++){
        if(ctr==dotpos) putc('.', stdout);
        putc((number & (1<<31)) ? '1' : '0', stdout);
        number = number<<1;
    }
}

/*
    Prints Q1.15 code in binary format
*/
void print_q115(int16_t number){
    putc('0', stdout);
    putc('b', stdout);
    for(int ctr=0; ctr<16; ctr++){
        if(ctr==1) putc('.', stdout);
        putc((number & (1<<15)) ? '1' : '0', stdout);
        number = number<<1;
    }
}

/*
    Q_add:
    a: Q1.15
    b: Q1.15
    returns: Q2.30
*/
uint32_t Q_add(uint16_t a, uint16_t b) {
    return (a + b)<<15;
}

/*
    Q_sub:
    a: Q1.15
    b: Q1.15
    returns: Q2.30
*/
uint32_t Q_sub(uint16_t a, uint16_t b) {
    return (a - b)<<15;
}

/*
    Q_mul:
    a: Q1.15
    b: Q1.15
    returns: Q2.30
*/
uint32_t Q_mul(uint16_t a, uint16_t b) {
    return (a * b);
}

/*  
    Q_div:
    a: Q1.15
    b: Q1.15
    returns: Q16.16
*/
uint32_t Q_div(uint16_t a, uint16_t b) {
    return (((uint32_t)a<<16) / (uint32_t)b);
}

void printOperation(int16_t a, int16_t b, int32_t y, char operation){
    print_q115(a);
    printf(" %c ",operation);
    print_q115(b);
    printf(" = ");
    print_q230(y, (operation == '/') ? 16 : 2);
    printf("\r\n");
}

double calculateQ115(uint16_t val){
    double div=1;
    double sum=0;

    for(int i=0; i < 16; i++){
        sum += (val & (1<<15))? div : 0;
        val = val << 1;
        div = div/2;
    }

    return sum;
}

int main(){
    uint16_t a, b;

    a = 0x1000;
    b = 0x0001;

    printf("a: %f \n\r", calculateQ115(a));

    printOperation(a, b, Q_add(a, b), '+');
    printOperation(a, b, Q_sub(a, b), '-');
    printOperation(a, b, Q_mul(a, b), '*');
    printOperation(a, b, Q_div(a, b), '/');
    return 0;
}