#include "main.h"

// container for things/utils related to the lift
namespace lift{
    void init()
    {
        // make sure the lift motors lock in place
        liftA.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        liftB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }

    // allows direct setting of the lift position
    void setPosition(double deg, int speed)
    {
        liftA.move_absolute(deg, speed);
        liftB.move_absolute(deg, speed);
    }

    // driver control
    void opControl()
    {
        // gradually move lift down
        if (master.get_digital(DIGITAL_R2))
        {
            liftA.move(50);
            liftB.move(50);
        }
        else if (master.get_digital(DIGITAL_L2)) // gradually move lift up
        {
            liftA.move(-100);
            liftB.move(-100);
        }
        else if (master.get_digital_new_press(DIGITAL_DOWN)) // automatically drop lower the clamp and lower the lift to a position for grabbing the pins from the intake
        {
            setPosition(5, 40);

            clawVertical.set(false);
            clawClamp.set(true);
            
            // wait for the lift to reach the position before opening the clamp
            while (liftA.get_position() < 5)
            {
                pros::delay(10);
            }

            clawVertical.set(true);
            clawClamp.set(false);
        }
        else if (master.get_digital_new_press(DIGITAL_B)) // a random thing luke wanted
        {
            setPosition(15, 100);
            
            clawVertical.set(false);
            clawClamp.set(true);
        }

        else // if no input is detected then stop the lift and hold it in place
        {
            liftA.move(0);
            liftB.move(0);

            liftA.brake();
            liftB.brake();
        }
    }   
}