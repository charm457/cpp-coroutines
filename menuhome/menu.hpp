#pragma once

namespace BDK {
    struct Menu {
        const char* const title; // название 
        const Menu* (*func)(const Menu* current); //выполняемая функция 
        const Menu* parent;
        const Menu* const *children;
        const int children_count;
    };
}