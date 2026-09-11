#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// this is an actual useful hpp file because its where the code interfaces with all the hardware



// motors

// lift
inline pros::Motor toggleSpinner(2);
inline pros::Motor liftA(6, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);

// intake
inline pros::Motor intake(3, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

// pistons

inline ez::Piston flipper(8, false);

// clamp
inline ez::Piston clawClamp(1, false);

inline pros::Motor clawIntakeA(16);
inline pros::Motor clawIntakeB(17);