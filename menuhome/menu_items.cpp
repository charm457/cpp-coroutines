#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_func.hpp"

namespace BDK {

    const Menu PLUS{
        "1 - Хочу научиться складывать", want_plus, &LEARNMATH
    };
    const Menu SUBSTRUCT{
        "2 - Хочу научиться вычитать", want_subtraction, &LEARNMATH
    };
    const Menu MULTIPLICAT{
        "3 - Хочу научиться умножать", want_multiplication, &LEARNMATH
    };
    const Menu DIVISION{
        "4 - Хочу научиться делить", want_division, &LEARNMATH
    };
    const Menu EXITMATH{
        "0 - Вернуться к выбору предметов", exit_algebra, &LEARNMATH
    };
    namespace {
        const Menu* const studyMath_lan[] = {
            &EXITLEARN,
            &PLUS,
            &SUBSTRUCT,
            &MULTIPLICAT,
            &DIVISION
            
        };
        const int subjectsMath_size = sizeof(studyMath_lan) / sizeof(studyMath_lan[0]);
    }
    
    const Menu DIFISCH{
        "1 - Хочу изучить дифференциальное исчисление", want_plus, &LEARNMATAN
    };
    const Menu INTISCH{
        "2 - Хочу изучить интегральное исчисление", want_subtraction, &LEARNMATAN
    };
    const Menu EXITMATAN{
        "0 - Вернуться к выбору предметов", want_multiplication, &LEARNMATAN
    };
    namespace {
        const Menu* const studyMatan_lan[] = {
            &EXITMATAN,
            &DIFISCH,
            &INTISCH,
            
            
        };
        const int subjectsMatan_size = sizeof(studyMatan_lan) / sizeof(studyMatan_lan[0]);
    }

    const Menu&LEARNMATH{
        "1 - Хочу изучить алгебру", show_menu, &LEARN, studyMath_lan, subjectsMath_size
    };
    const Menu LEARNMATAN{
        "2 - хочу изучать математический анализ",  show_menu, &LEARN, studyMath_lan, subjectsMatan_size
    };
    const Menu EXITMAIN{
        "0 - Выйти в главное меню", exit_learn, &LEARN
    };

    namespace {
        const Menu* const study_children[] = {
            &EXITMAIN,
            &LEARNMATH,
            &LEARNMATAN,
            
            
        };
        const int learn_size = sizeof(study_children) / sizeof(study_children[0]);
    }

    const Menu LEARN{
        "1 - Хочу учиться математике?", show_menu, &MAIN, study_children, learn_size  
    };
    const Menu EXIT{
        "0 - Пойду полежу...", exit, &MAIN, study_children, learn_size  
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


