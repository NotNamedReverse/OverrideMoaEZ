#pragma once
#include "main.h"

namespace claw{
    inline bool isClamped = false;

    void init();

    void intake();
    void stopIntake();
    
    void toggleClamp();
    void opControl();
}