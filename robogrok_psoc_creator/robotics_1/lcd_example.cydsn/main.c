#include "project.h"

int main(void)
{
    LCD_Char_1_Start();
    LCD_Char_1_ClearDisplay();
    LCD_Char_1_Position(0, 0);
    LCD_Char_1_PrintString("Hello World");
    for(;;)
    {
        
    }
}
