
#include "project.h"

int main(void)
{
    int counter = 0;
    int pot = 0;
    quaddec_1_Start();
    lcd_char_1_Start();
    ADC_SAR_Seq_1_Start();  // start the ADC block
    ADC_SAR_Seq_1_StartConvert();   // start the conversion process

    for(;;)
    {
        // In top design, we set input range to Vssa to Vdda (single ended) so we can convert analog to digital values using a graph-like relationship
        // We know our voltage is going to range from 0 volts to Vdd from the PSOC so we select this option. From GND to VDD voltage.
        // Resolution is set to 12 bits
        ADC_SAR_Seq_1_IsEndConversion(ADC_SAR_Seq_1_WAIT_FOR_RESULT);   // Tell the ADC not to give us a result until the conversion is complete
        pot = ADC_SAR_Seq_1_GetResult16(0); // save the digital value into "potential" variable
        counter = quaddec_1_GetCounter();
        lcd_char_1_ClearDisplay();
        lcd_char_1_Position(0, 0);
        lcd_char_1_PrintNumber(pot);    // print the value of the potentiometer onto the LCd screen
        CyDelay(50);
        
//        // In top design, we set the drive mode for switch_1 to be pull down resistor because we want the default state to be low
//        // when the switch is not pressed. Otherwise, when button is released the circuit breaks without the pull down resistor.
//        // Switch is connected to VDD so it will read 1 when pressed. 
//        if(switch_1_Read() == 1)
//        {
//            lcd_char_1_ClearDisplay();
//            lcd_char_1_Position(0, 0);
//            lcd_char_1_PrintString("On");
//            CyDelay(50);
//        }
//        else
//        {
//            lcd_char_1_ClearDisplay();
//            lcd_char_1_Position(0, 0);
//            lcd_char_1_PrintString("Off");
//            CyDelay(50);
//        }
    }
}
