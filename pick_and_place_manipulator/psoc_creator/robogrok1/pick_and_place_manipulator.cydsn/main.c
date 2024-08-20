#include "scara_manipulator.h"
#include "electromagnet.h"

int main(void)
{
    pwm_1_Start();  // first start the pwm block for the two revolute joint servos
    for(;;)
    {
        manipulator_joint_1_angles(135.0, 180.0);   // range from 0.0 to 180.0 degrees
        manipulator_joint_2_angles(-45.0, 0.0);     // range from -90.0 to 90.0 degrees
        
        electromagnet_on();
        CyDelay(2000);
        electromagnet_off();
        CyDelay(10000);
    }
}
