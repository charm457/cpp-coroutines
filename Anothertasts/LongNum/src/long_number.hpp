#pragma once

#include <iostream>

namespace bdk {
    class LongNumber {
    private:
        int* numbers;   // Динамический массив для цифр
        int length;     // Количество цифр
        int sign;       // 1 для +, -1 для -, 0 для нуля
        
    public:
        // ----------------------------------------------------------
        // CONSTRUCTORS
        // ----------------------------------------------------------
        LongNumber();
        LongNumber(const char* const str);
        LongNumber(const LongNumber& x);
        LongNumber(LongNumber&& x) noexcept;
        
        ~LongNumber();
        
        // ----------------------------------------------------------
        // ASSIGNMENT OPERATORS
        // ----------------------------------------------------------
        LongNumber& operator = (const char* const str);
        LongNumber& operator = (const LongNumber& x);
        LongNumber& operator = (LongNumber&& x) noexcept;
        
        // ----------------------------------------------------------
        // COMPARISON OPERATORS
        // ----------------------------------------------------------
        bool operator == (const LongNumber& x) const;
        bool operator != (const LongNumber& x) const;
        bool operator > (const LongNumber& x) const;
        bool operator < (const LongNumber& x) const;
        
        // ----------------------------------------------------------
        // ARITHMETIC OPERATORS
        // ----------------------------------------------------------
        LongNumber operator + (const LongNumber& x) const;
        LongNumber operator - (const LongNumber& x) const;
        LongNumber operator * (const LongNumber& x) const;
        LongNumber operator / (const LongNumber& x) const;
        LongNumber operator % (const LongNumber& x) const;
        
        bool is_negative() const noexcept;
        

        friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
        
    private:
        int get_length(const char* const str) const noexcept;
        LongNumber(int length, int sign); 
    };
}