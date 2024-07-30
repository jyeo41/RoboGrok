#include "project.h"

int main(void)
{
    led_white_Write(0);
    uint8_t i = 0;
    for(;;)
    {
        for (i = 0; i < 3; i++)
        {
            led_blue_Write(1);
            CyDelay(250);
            led_blue_Write(0);
            CyDelay(250);
        }
        
        led_white_Write(1);
        CyDelay(250);
        led_white_Write(0);
        CyDelay(250);
    }
}