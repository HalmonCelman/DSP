#ifndef Q_CODE_H
#define Q_CODE_H

#include <stdint.h>

void print_q230(uint32_t number, uint8_t dotpos);
void print_q115(uint16_t number);
uint32_t Q_add(uint16_t a, uint16_t b);
uint32_t Q_sub(uint16_t a, uint16_t b);
uint32_t Q_mul(uint16_t a, uint16_t b);
uint32_t Q_div(uint16_t a, uint16_t b);
void printOperation(int16_t a, int16_t b, int32_t y, char operation);
double calculateQ115(uint16_t val);

#endif