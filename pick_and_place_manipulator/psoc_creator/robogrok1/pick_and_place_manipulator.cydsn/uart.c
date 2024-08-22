#include "uart.h"

// Keep polling until the PSoC receives a valid character. The PSoC treats a 0 as 
void uart_polling_receive(float* receive)
{
    *receive = uart_1_GetChar();
    while (*receive == 0)
    {
        *receive = uart_1_GetChar();
//        lcd_display_ClearDisplay();
//        lcd_display_Position(0, 0);
//        lcd_display_PrintString("POLLING");
    }
}

// Subroutine to receive both coordinates from the python code over pyserial.
// We divide the received value by 10 because when we transmit it, we multiply it by 10.
// The idea is to get float precision to the first decimal.
// If we want to send 6.9 as a coordinate, we first multiply it by 10 so it sends the integer 69 which is within the 0 <= 255 range
//  and then divide it at the received end to convert it back to 1 point precision.
void uart_polling_receive_both_coordinates(float* x, float* y)
{
    uart_polling_receive(x);
    uart_polling_receive(y);
    *x /= 10;                   
    *y /= 10;                   
//    lcd_display_ClearDisplay();
//    lcd_display_Position(0, 0);
//    lcd_display_PrintNumber(*x);
//    lcd_display_Position(0, 3);
//    lcd_display_PrintNumber(*y);
}

// Print function to extract out the digits from the floating point values 
//  of the x and y coordinates and display it on the LCD screen
void uart_print_coordinates(float* x, float* y)
{
    // Local copies of the incoming variables in order to manipulate them
    int x_coordinate = (*x) * 10;
    int y_coordinate = (*y) * 10;
    
    // Divide by 10 to extract out the first digit, modulo 10 to extract out the second digit.
    // Example: float 5.9 - the first digit is 5, the second digit is 9          
    int x_first_digit = x_coordinate / 10;
    int x_second_digit = x_coordinate % 10;
    
    int y_first_digit = y_coordinate / 10;
    int y_second_digit = y_coordinate % 10;
    
    lcd_display_ClearDisplay();
    lcd_display_Position(0, 0);
    lcd_display_PrintNumber(x_first_digit);
    lcd_display_Position(0, 1);
    lcd_display_PrintString(".");
    lcd_display_Position(0, 2);
    lcd_display_PrintNumber(x_second_digit);

    lcd_display_Position(0, 4);
    lcd_display_PrintNumber(y_first_digit);
    lcd_display_Position(0, 5);
    lcd_display_PrintString(".");
    lcd_display_Position(0, 6);
    lcd_display_PrintNumber(y_second_digit);
    
    
}