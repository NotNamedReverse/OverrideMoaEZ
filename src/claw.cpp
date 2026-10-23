#include "claw.hpp"

// contains all thing related to the claw (right now just the driver control)
namespace claw{
    void init()
    {
        clawClamp.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }

    void toggleClamp()
    {
        isClamped = !isClamped;

        clawClamp.move_absolute(isClamped ? 145 : 0, 127);
    }

    void intake()
    {
        clawIntake.move(127);
    }

    void stopIntake()
    {
        clawIntake.move(0);
    }

    // driver control; detetct button presses and toggle the pistons
    void opControl()
    {
        // toggle if the claw is clamped or not
        if (master.get_digital_new_press(DIGITAL_L2))
        {
            toggleClamp();
        }

        if (master.get_digital(DIGITAL_L1))
        {
            intake();
        }
        else
        {
            stopIntake();
        }
    }
}