#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_func.hpp"

namespace BDK {

    const Menu RUSSIONLAN{
        "1 - Русский язык", ru_lan, &LEARN1
    };
    const Menu RUSSIONLIT{
        "2 - Русская литература", ru_lit, &LEARN1
    };
    const Menu MATH{
        "3 - Математика", math, &LEARN1
    };
    const Menu FIZRA{
        "4 - Я люблю физкультуру", fiz_ed, &LEARN1
    };
    const Menu EXITLEARN{
        "0 - Выйти в предыдущее меню", exit_learn, &LEARN1
    };
    namespace {
        const Menu* const study_lan[] = {
            &EXITLEARN,
            &RUSSIONLAN,
            &RUSSIONLIT,
            &MATH,
            &FIZRA
            
        };
        const int subjects_size = sizeof(study_lan) / sizeof(study_lan[0]);
    }
    
    const Menu LEARN1{
        "1 -Изучать предметы 1 класса", show_menu, &LEARN, study_lan, subjects_size
    };
    const Menu LEARN2{
        "2 - Изучать предметы 2 класса",  show_menu, &LEARN, study_lan, subjects_size
    };
    const Menu LEARN3{
        "3 - Изучать предметы 3 класса", show_menu, &LEARN, study_lan, subjects_size
    };
    const Menu EXITMAIN{
        "0 - Выйти в главное меню", exit_learn, &LEARN, study_lan, subjects_size
    };

    namespace {
        const Menu* const study_children[] = {
            &EXITMAIN,
            &LEARN1,
            &LEARN2,
            &LEARN3
            
        };
        const int learn_size = sizeof(study_children) / sizeof(study_children[0]);
    }

    const Menu LEARN{
        "1 - Предметы какого класса школы вы хотите учить?", show_menu, &MAIN, study_children, learn_size  
    };
    const Menu EXIT{
        "0 - Я уже закончил школу и все знаю", exit, &MAIN, study_children, learn_size  
    };

    namespace {
        const Menu* const main_children[] = {
            &EXIT,
            &LEARN
            
        };
        const int main_size = sizeof(main_children) / sizeof(main_children[0]);
    }



    const Menu MAIN{
        nullptr, show_menu, nullptr, main_children, main_size 
    };

}


