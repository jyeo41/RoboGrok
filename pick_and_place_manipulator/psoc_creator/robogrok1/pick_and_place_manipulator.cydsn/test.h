#ifndef TEST_H
#define TEST_H

#include "project.h"
#include "motor.h"
#include "servos.h"
#include "uart.h"

void test_manipulator_workspace();
void test_uart_polling_receive(float* receive);
void test_uart_polling_both_coordinates(float* x, float* y);
void test_motor_counter();
    
#endif  // TEST_H