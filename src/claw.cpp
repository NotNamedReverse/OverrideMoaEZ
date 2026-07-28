#include "claw.hpp"

namespace claw{
    void init()
    {

    }

    void opControl()
    {
        if (master.get_digital_new_press(DIGITAL_Y))
        {
            clawClamp.set(!clawClamp.get());
        }

        if (master.get_digital_new_press(DIGITAL_RIGHT))
        {
            clawVertical.set(!clawVertical.get());
        }
    }
}