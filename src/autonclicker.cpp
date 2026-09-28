#include "autonclicker.hpp"

namespace autonclicker
{

    void update()
    {
        int bumperValue = bumper.get_value();
        if (bumperValue < threshold)
        {
            holdTime += 1;
            
            if (!isPressed)
            {
                isPressed = true;
            
                //ez::as::auton_selector.auton_page_current += 1;
                ez::as::page_up();
            }

            if (isPressed && holdTime > 100)
            {
                holdTime = 0;

                ez::as::page_down();
            }
        }
        else if (bumperValue >= threshold)
        {
            holdTime = 0;
            isPressed = false;
        }
    }
}