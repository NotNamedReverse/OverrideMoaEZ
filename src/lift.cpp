#include "main.h"

namespace lift{
    void init()
    {
        liftA.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        liftB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }

    void setPosition(double deg, int speed)
    {
        liftA.move_absolute(deg, speed);
        liftB.move_absolute(deg, speed);
    }

    void opControl()
    {
        if (master.get_digital(DIGITAL_R2))
        {
            liftA.move(50);
            liftB.move(50);
        }
        else if (master.get_digital(DIGITAL_L2))
        {
            liftA.move(-100);
            liftB.move(-100);
        }
        else if (master.get_digital_new_press(DIGITAL_DOWN))
        {
            double position = liftA.get_position();

            setPosition(15, 40);
            
            clawVertical.set(false);
            clawClamp.set(true);

            while (liftA.get_position() < 10)
            {
                pros::delay(20);
            }

            clawClamp.set(false);
            clawVertical.set(true);

            setPosition(position, 127);

            while (abs(liftA.get_position()) < abs(position))
            {
                pros::delay(20);
            }
        }

        else if (master.get_digital_new_press(DIGITAL_B))
        {
            setPosition(15, 100);
            
            clawVertical.set(false);
            clawClamp.set(true);
        }

        else
        {
            liftA.move(0);
            liftB.move(0);

            liftA.brake();
            liftB.brake();
        }
    }   
}