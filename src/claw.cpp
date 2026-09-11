#include "claw.hpp"

// contains all thing related to the claw (right now just the driver control)
namespace claw{
    void init()
    {

    }

    void toggleClamp()
    {
        clawClamp.set(!clawClamp.get());
    }

    // driver control; detetct button presses and toggle the pistons
    void opControl()
    {
        // toggle if the claw is clamped or not
        if (master.get_digital_new_press(DIGITAL_Y))
        {
            toggleClamp();
        }

        if (master.get_digital(DIGITAL_RIGHT))
        {
            clawIntakeA.move(-127);
            clawIntakeB.move(127);
        }
        else
        {
            clawIntakeA.move(0);
            clawIntakeB.move(0);
        }
    }
}