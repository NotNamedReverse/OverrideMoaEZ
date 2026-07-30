#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor liftA(-13, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);
inline pros::Motor liftB(14, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);

inline pros::Motor intake(15, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

inline ez::Piston clawVertical(5, false);
inline ez::Piston clawClamp(6, true);

inline pros::Optical AutoClamp(7);