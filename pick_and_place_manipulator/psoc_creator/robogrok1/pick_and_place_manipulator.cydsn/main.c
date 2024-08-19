#include "project.h"
#include "scara_manipulator.h"

int main(void)
{
    pwm_1_Start();  // first start the pwm block
    for(;;)
    {
        manipulator_joint_1_angles(135.0, 180.0);
        manipulator_joint_2_angles(-45.0, 0.0);
    }
}
