#include "claw.hpp"

// contains all thing related to the claw (right now just the driver control)
namespace claw{
    void init()
    {

    }

    // driver control; detetct button presses and toggle the pistons
    void opControl()
    {
        // toggle if the claw is clamped or not
        if (master.get_digital_new_press(DIGITAL_Y))
        {
            clawClamp.set(!clawClamp.get());
        }

        // toggle if the claw should be vertical
        if (master.get_digital_new_press(DIGITAL_RIGHT))
        {
            clawVertical.set(!clawVertical.get());
        }
    }
}