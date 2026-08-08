#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// this is an actual usefull hpp file because its where the code interfaces with all the hardware



// motors

// lift motors
inline pros::Motor liftA(-13, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);
inline pros::Motor liftB(14, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);

// intake
inline pros::Motor intake(15, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

// pistons

// clamp
inline ez::Piston clawVertical(5, false);
inline ez::Piston clawClamp(6, false);