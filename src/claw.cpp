#include "claw.hpp"



namespace claw{

    bool clawReleased = false;

    void init()
    {

    }

    void setClawClamp(bool value) {
        clawClamp.set(value);
        if (clawClamp.get() == false) {
            clawReleased = true;
        }
    }

    void opControl()
    {
        if (master.get_digital_new_press(DIGITAL_Y))
        {
            setClawClamp(!clawClamp.get());
        }

        if (master.get_digital_new_press(DIGITAL_RIGHT))
        {
            clawVertical.set(!clawVertical.get());
        }
    }

    void autoClamp_t(){
        AutoClamp.set_led_pwm(100);
        while(true){
            if (AutoClamp.get_proximity() >= 230 ) {
                clawClamp.set(true);
                master.rumble(".");
                if (clawReleased == true) {
                    pros::delay(500);
                    clawReleased = false;
                }
            }
            pros::delay(ez::util::DELAY_TIME);
        }
    }
}