#include "swirleeDrive.hpp";

namespace swirleeDrive{
    void tank_control()
    {
        int32_t leftAxis = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int32_t rightAxis = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        chassis.drive_set(leftAxis, rightAxis);
    }

    void arcade_standard_inverted() {
        const int forward = -master.get_analog(ANALOG_LEFT_Y);
        const int turn = -master.get_analog(ANALOG_RIGHT_X);
        int left = forward - turn;
        int right = forward + turn;

        const int max_power = std::max(std::abs(left), std::abs(right));
        if (max_power > 127) {
          left = left * 127 / max_power;
          right = right * 127 / max_power;
        }

        chassis.drive_set(left, right);
    }
}