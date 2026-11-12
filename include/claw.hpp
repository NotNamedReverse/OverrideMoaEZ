#pragma once
#include "main.h"

namespace claw{
    inline bool isClamped = false;
    inline bool clawButtonPressed = false;
    inline int clawPressTime = false;

    void init();

    void intake();
    void stopIntake();
    
    void toggleClamp();
    void opControl();
}