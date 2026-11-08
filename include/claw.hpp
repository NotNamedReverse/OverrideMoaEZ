#pragma once
#include "main.h"

namespace claw{
    inline bool isClamped = false;
    inline bool clawButtonPressed = false;
    inline int clawPressTime = 0;

    void init();

    void intake();
    void stopIntake();
    
    void toggleClamp();
    void opControl();
}