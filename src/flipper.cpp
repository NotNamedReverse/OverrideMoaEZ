#include "flipper.hpp"

// new flipper namespace to prevent having to replace a bunch of code in the autos
namespace flipper{
    void set(bool position){
        flipperMotor.move_absolute(position ? -345 : 0, 127);
    }
}