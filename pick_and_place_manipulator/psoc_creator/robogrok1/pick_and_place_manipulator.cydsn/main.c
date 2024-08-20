#include "scara_manipulator.h"
#include "electromagnet.h"

int main(void)
{
    int counter = 0;
    quaddec_motor_Start();
    pwm_1_Start();  // first start the pwm block for the two revolute joint servos
    lcd_display_Start();
    for(;;)
    {
//        manipulator_joint_1_angles(135.0, 180.0);   // range from 0.0 to 180.0 degrees
//        manipulator_joint_2_angles(-45.0, 0.0);     // range from -90.0 to 90.0 degrees
//        
//        electromagnet_on();
//        CyDelay(2000);
//        electromagnet_off();
//        CyDelay(10000);
        counter = quaddec_motor_GetCounter();
        lcd_display_ClearDisplay();
        lcd_display_Position(0, 0);
        lcd_display_PrintNumber(counter);
        CyDelay(50);
    }
}
