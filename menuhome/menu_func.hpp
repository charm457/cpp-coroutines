#pragma once

#include "menu.hpp"

namespace BDK{

    const Menu* show_menu(const Menu* current);

    const Menu* exit(const Menu* current);
    
    const Menu* want_plus(const Menu* current);
    const Menu* want_subtraction(const Menu* current);
    const Menu* want_multiplication(const Menu* current);
    const Menu* want_division(const Menu* current);
    const Menu* exit_algebra(const Menu* current);

    const Menu* want_dif(const Menu* current);
    const Menu* want_integral(const Menu* current);
    const Menu* exit_matan(const Menu* current);

    void greeting(const Menu* current);
}