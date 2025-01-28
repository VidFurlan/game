#pragma once

#include <iostream>
#include "callback_interface.hpp"

class Callee : public CallbackInterface {
    public:
        int callbackFunction(int i) {
            std::cout << "Callee::callbackFunction(" << i << ") called" << std::endl;
            return 2 * i;
        }
};
