#include "claw.hpp"

namespace claw{
    void init()
    {

    }

    void opControl()
    {
        if (master.get_digital(DIGITAL_Y))
        {
            clawClamp.set(!clawClamp.get());
        }

        if (master.get_digital(DIGITAL_RIGHT))
        {
            clawVertical.set(!clawVertical.get());
        }
    }
}