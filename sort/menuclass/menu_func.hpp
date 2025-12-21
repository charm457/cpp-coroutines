#pragma once

#include "menu.hpp"

namespace BDK{

    const Menu* show_menu(const Menu* current);

    const Menu* exit(const Menu* current);
    
    const Menu* fiz_ed(const Menu* current);
    const Menu* ru_lan(const Menu* current);
    const Menu* ru_lit(const Menu* current);
    const Menu* math(const Menu* current);
    const Menu* exit_learn(const Menu* current);

    void greeting(const Menu* current);
}