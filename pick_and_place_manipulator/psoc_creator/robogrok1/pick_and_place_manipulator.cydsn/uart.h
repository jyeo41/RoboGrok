#ifndef UART_H
#define UART_H

#include "project.h"
    
void uart_polling_receive(float* receive);
void uart_polling_receive_both_coordinates(float* x, float* y);
void uart_print_coordinates(float* x, float* y);

#endif // UART_H