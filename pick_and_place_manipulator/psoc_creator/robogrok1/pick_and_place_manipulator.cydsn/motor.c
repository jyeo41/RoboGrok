#include "motor.h"

static int counter = 0;        // keep track of current position of rack and pinion using quadrature decoder
static int error = 0;
static int speed = 0;
static int time = 0;
static const float kp = 0.75;


// time_delay parameter is how long we want to give the rack to get to its proper position in milliseconds
void rack_pinion_lower(int time_delay, int target)
{
    time = 0;
    while (time < time_delay)
    {
        counter = quaddec_motor_GetCounter();   // getting the current position of the rack
        error = target - counter; // calculate error to use proportional control algorithm
        
        if (error > 0)  // This means the rack still has distance left to reach the "bottom" position
        {
            speed = kp * error; // as the rack gets closer to the target distance, the speed will lower, speed is positive since error is positive
            if (speed > 100)
            {
                speed = 100;    // this is because the compare value cannot exceed 100
            }
            // making the motor only spin it one direction. Write a 0 to the side we don't want it to turn to
            pwm_motor_WriteCompare1(0);
            pwm_motor_WriteCompare2(speed);
        }
        else    // speed is a product of kp * error so this branch will inevitably turn off the motor
        {
            speed = -kp * error;    // -kp because this condition is error <= 0. Compare value can never be negative
            if (speed > 100)
            {
                speed = 100;
            }
            pwm_motor_WriteCompare1(speed);
            pwm_motor_WriteCompare2(0);        
        }
        CyDelay(10);
//        lcd_display_ClearDisplay();
//        lcd_display_Position(0, 0);
//        lcd_display_PrintNumber(counter);
        time += 10; // increment time variable by the amount of milliseconds of delay from CyDelay() function
    }
}

void rack_pinion_raise(int time_delay, int target)
{
    time = 0;
    while (time < time_delay)
    {
        counter = quaddec_motor_GetCounter();   // getting the current position of the rack
        error = target - counter; // calculate error to use proportional control algorithm
        
        if (error > 0)  // This means the rack still has distance left to reach the "bottom" position
        {
            speed = kp * error; // as the rack gets closer to the target distance, the speed will lower, speed is positive since error is positive
            if (speed > 100)
            {
                speed = 100;    // this is because the compare value cannot exceed 100
            }
            // making the motor only spin it one direction. Write a 0 to the side we don't want it to turn to
            pwm_motor_WriteCompare1(0);
            pwm_motor_WriteCompare2(speed);
        }
        else    // speed is a product of kp * error so this branch will inevitably turn off the motor
        {
            speed = -kp * error;    // -kp because this condition is error <= 0. Compare value can never be negative
            if (speed > 100)
            {
                speed = 100;
            }
            pwm_motor_WriteCompare1(speed);
            pwm_motor_WriteCompare2(0);        
        }
        CyDelay(10);
//        lcd_display_ClearDisplay();
//        lcd_display_Position(0, 0);
//        lcd_display_PrintNumber(counter);
        time += 10; // increment time variable by the amount of milliseconds of delay from CyDelay() function
    }
}