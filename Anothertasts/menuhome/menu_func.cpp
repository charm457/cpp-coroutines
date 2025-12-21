#include <iostream>
#include "menu_items.hpp"
#include "menu_func.hpp"

void BDK::greeting(const Menu* current){
    if(current == &MAIN || current->parent == &LEARN){
        std::cout << "Приветствую!" << std::endl;
    }
    else{
        std::cout << "Да начнем же обучение!" << std::endl;
    }
}

const BDK::Menu* BDK::show_menu(const Menu* current) {
    greeting(current);
    
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Обучайка > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;
    return current->children[user_input];
}



// All exits
const BDK::Menu* BDK::exit(const Menu* current) {
    std::exit(0);
}
const BDK::Menu* BDK::exit_learn(const Menu* current) {
    return current->parent->parent;
}
const BDK::Menu* BDK::exit_algebra(const Menu* current) {
    return current->parent->parent;
}
const BDK::Menu* BDK::exit_matan(const Menu* current) {
    return current->parent->parent;
}
//Another functions



const BDK::Menu* BDK::want_plus(const Menu* current) {
    
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}
const BDK::Menu* BDK::want_subtraction (const Menu* current) {
    
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}
const BDK::Menu* BDK::want_multiplication(const Menu* current) {
    
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}
const BDK::Menu* BDK::want_division(const Menu* current) {
    
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const BDK::Menu* BDK::want_dif(const Menu* current) {
    
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}
const BDK::Menu* BDK::want_integral(const Menu* current) {
    
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}