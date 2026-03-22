#include <iostream>
#include <string>
#include <vector>
#include "long_number.hpp"

using namespace bdk;

struct TestCase {
    std::string name;
    LongNumber a, b, expected;
    char op;
};

void run_tests() {
    std::vector<TestCase> tests = {
        // СЛОЖЕНИЕ
        {"C",    LongNumber("15"),     LongNumber("10"),    LongNumber("25"),  '+'},
        {"C",   LongNumber("99"),     LongNumber("1"),     LongNumber("100"), '+'},
        {"C",     LongNumber("-10"),    LongNumber("-20"),   LongNumber("-30"), '+'},
        {"C",   LongNumber("-10"),    LongNumber("5"),     LongNumber("-5"),  '+'},

        // ВЫЧИТАНИЕ
        {"B",    LongNumber("20"),     LongNumber("5"),     LongNumber("15"),  '-'},
        {"B",  LongNumber("100"),    LongNumber("1"),     LongNumber("99"),  '-'},
        {"B", LongNumber("5"),      LongNumber("10"),    LongNumber("-5"),  '-'},
        {"B",  LongNumber("10"),     LongNumber("-10"),   LongNumber("20"),  '-'},

        // УМНОЖЕНИЕ
        {"Y",    LongNumber("12"),     LongNumber("4"),     LongNumber("48"),  '*'},
        {"Y", LongNumber("500"),    LongNumber("0"),     LongNumber("0"),   '*'},
        {"Y",   LongNumber("-5"),     LongNumber("-6"),    LongNumber("30"),  '*'},
        {"Y",     LongNumber("10000"),  LongNumber("10000"), LongNumber("100000000"), '*'},

        // ДЕЛЕНИЕ И ОСТАТОК
        {"D",    LongNumber("13"),     LongNumber("5"),     LongNumber("2"),   '/'},
        {"D",LongNumber("3"),      LongNumber("10"),    LongNumber("0"),   '/'},
        {"DO",    LongNumber("13"),     LongNumber("5"),     LongNumber("3"),   '%'},
        {"DO",    LongNumber("10"),     LongNumber("10"),    LongNumber("0"),   '%'}
    };

    int passed = 0;
    for (auto& t : tests) {
        LongNumber res;
        if (t.op == '+') res = t.a + t.b;
        else if (t.op == '-') res = t.a - t.b;
        else if (t.op == '*') res = t.a * t.b;
        else if (t.op == '/') res = t.a / t.b;
        else if (t.op == '%') res = t.a % t.b;

        if (res == t.expected) {
            std::cout << "[OK] " << t.name << "\n";
            passed++;
        } else {
            std::cout << "[FAIL] " << t.name << " (Ожидалось одно, вышло другое)\n";
        }
    }
    std::cout << "\nИтог: " << passed << "/" << tests.size() << " пройдено\n";
}

int main() {
    run_tests();
    return 0;
}