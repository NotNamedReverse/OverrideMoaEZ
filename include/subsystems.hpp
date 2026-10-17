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

// flipper
inline pros::Motor flipperMotor(16);

// clamp
inline pros::Motor clawIntake(14);
inline pros::Motor clawClamp(12);

inline pros::ADIAnalogIn bumper(2);