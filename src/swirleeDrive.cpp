#include "swirleeDrive.hpp";

namespace swirleeDrive{
    void tank_control()
    {
        int32_t leftAxis = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int32_t rightAxis = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        chassis.drive_set(leftAxis, rightAxis);
    }
}