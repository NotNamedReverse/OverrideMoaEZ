#include "swirleedbgtool.hpp"

namespace swirleeDebugTool{
    bool openMenuPressed(){
        return master.get_digital_new_press(DIGITAL_DOWN) 
        && master.get_digital_new_press(DIGITAL_RIGHT) 
        && master.get_digital_new_press(DIGITAL_B) 
        && master.get_digital_new_press(DIGITAL_Y);
    }
}