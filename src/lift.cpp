#include "main.h"

// container for things/utils related to the lift
namespace lift{
    void init()
    {
        // make sure the lift motors lock in place
        liftA.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }

    // allows direct setting of the lift position
    void setPosition(double deg, int speed)
    {
        liftA.move_absolute(deg, speed);
    }

    // driver control
    void opControl()
    {
        // gradually move lift down
        if (master.get_digital(DIGITAL_R1))
        {
            liftA.move(127);
        }
        else if (master.get_digital(DIGITAL_L1)) // gradually move lift up
        {
            liftA.move(-127);
        }

        else // if no input is detected then stop the lift and hold it in place
        {
            liftA.move(0);

            liftA.brake();
        }
    }   
}