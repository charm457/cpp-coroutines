#include "long_number.hpp"

using bdk::LongNumber;
		
LongNumber::LongNumber() {
	numbers = new int[1]{0};
	length = 1;
	sign = 1;
}

LongNumber::LongNumber(int length, int sign) {
	this->length = length;
	this->sign = sign;
	this->numbers = new int[length]{0};
    for(int i = 0; i < length; i++){
        numbers[i] = 0;
    }
}

LongNumber::LongNumber(const char* const str) {
	int now_length = get_length(str);
	
	if (str[0] == '-')
	{
		sign = -1;
		length = now_length - 1;
	}
	else
	{
		sign = 1;
		length = now_length;
	}
	
	numbers = new int[length];
	for (int i = 0; i < length; i++)
		numbers[i] = str[now_length - 1 - i] - '0';
}

LongNumber::LongNumber(const LongNumber& x) {
	sign = x.sign;
	length = x.length;
	numbers = new int[length];
	for (int i = 0; i < length; i++)
		numbers[i] = x.numbers[i];
}

LongNumber::LongNumber(LongNumber&& x) {
	sign = x.sign;
	length = x.length;
	numbers = x.numbers;
	
	x.numbers = nullptr;
	x.length = 0;
	x.sign = 1;
}

LongNumber::~LongNumber() {
	delete [] numbers;
	length = 0;
	numbers = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int now_length = get_length(str);
	if (str[0] == '-')
	{
		sign = -1;
		length = now_length - 1;
	}
	else
	{
		sign = 1;
		length = now_length;
	}
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++) 
		numbers[i] = str[now_length - 1 - i] - '0';
	
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if(this == &x)
		return *this;
	
	sign = x.sign;
	length = x.length;
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++)
		numbers[i] = x.numbers[i];
	
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	sign = x.sign;
	length = x.length;
	delete [] numbers;
	numbers = x.numbers;
	
	x.numbers = nullptr;
	x.length = 0;
	x.sign = 1;
	
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (sign != x.sign) 
		return false;
	if (length != x.length)
		return false;
	for (int i = 0; i < length; i++)
		if (numbers[i] != x.numbers[i])
			return false;
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return not (*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (this == &x)
		return false;
	
	if (sign != x.sign)
		return sign > x.sign;
	
	else
	{
		if (length != x.length)
		{
			if (sign == 1)
				return length > x.length;
			
			else
				return length < x.length;
		}
		
		else
		{
			for (int i = length - 1; i >= 0 ; i--)
				if (numbers[i] != x.numbers[i])
				{
					if (sign == 1) 
						return numbers[i] > x.numbers[i];
					
					else 
						return numbers[i] < x.numbers[i];
				}
		}
	}
	
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return (*this != x) and (x > *this);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	LongNumber res;
	LongNumber min;
	LongNumber max;
	if (sign == x.sign)
	{
		if (*this > x)
		{
			res = LongNumber(length + 1, sign);
			min = x;
			max = *this;
		}
		else
		{	
			res = LongNumber(x.length + 1, sign);
			min = *this;
			max = x;
		}
		
		for (int i = 0; i < min.length; i++)
			res.numbers[i] = min.numbers[i] + max.numbers[i];
		
		for (int i = min.length; i < max.length; i++)
			res.numbers[i] = max.numbers[i];
		
		for (int i = 0; i < res.length - 1; i++)
		{
			if (res.numbers[i] > 9)
			{
				res.numbers[i] -= 10; //%=
				res.numbers[i + 1]++;
			}
		}
		
		if (res.numbers[res.length - 1] == 0)
			res.length--;
	}
	
	else
	{
		LongNumber abs_x = x;
		LongNumber dividend = *this;
		
		abs_x.sign = 1;
		dividend.sign = 1;
		
		if (dividend > abs_x)
		{
			res = LongNumber(length + 1, sign);
			min = x;
			max = *this;
		}
		else
		{	
			res = LongNumber(x.length + 1, x.sign);
			min = *this;
			max = x;
		}
		
		for (int i = 0; i < max.length; i++)
			res.numbers[i] = max.numbers[i];
		
		for (int i = 0; i < min.length; i++)
			res.numbers[i] = res.numbers[i] - min.numbers[i];
		
		for (int i = 0; i < res.length - 1; i++)
		{
			if (res.numbers[i] < 0)
			{
				res.numbers[i] += 10;
				res.numbers[i + 1]--;
			}
		}
		
		while (res.length > 1 and res.numbers[res.length - 1] == 0)
			res.length--;
		
		if (res.length == 1 and res.numbers[0] == 0)
			res.sign = 1;
	}
	
	return res;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	LongNumber res;
	res = x;
	res.sign = -res.sign;
	
	res = *this + res;
	
	return res;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	LongNumber res;
	res = LongNumber(length + x.length, sign * x.sign);
	for (int i = 0; i < x.length; i++) {
		for (int j = 0; j < length; j++) {
			res.numbers[i + j] += x.numbers[i] * numbers[j];
			if (res.numbers[i + j] > 9)
			{
				int r = res.numbers[i + j] / 10;
            
                res.numbers[i + j + 1] += r;
				res.numbers[i + j] -= r * 10;
			}
		}
	}
	while (res.length > 1 and res.numbers[res.length - 1] == 0)
		res.length--;
	return res;
}


LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x.sign == 0) return LongNumber("0"); // Деление на 0

    LongNumber dividend = *this; dividend.sign = 1;
    LongNumber divisor = x; divisor.sign = 1;

    if (dividend < divisor) return LongNumber("0");

    std::string res_str = "";
    LongNumber current_part("0");

    for (int i = 0; i < length; i++) {
        std::string next_val = "";
        if (!(current_part == LongNumber("0"))) {
            for(int k = 0; k < current_part.length; k++) next_val += (char)(current_part.numbers[k] + '0');
        }
        next_val += (char)(numbers[i] + '0');
        current_part = LongNumber(next_val.c_str());

        int count = 0;
        while (!(current_part < divisor)) {
            current_part = current_part - divisor;
            count++;
        }
        res_str += (char)(count + '0');
    }



    
    size_t first_digit = res_str.find_first_not_of('0');
    if (std::string::npos == first_digit) return LongNumber("0");
    res_str = res_str.substr(first_digit);

    int final_sign = (sign == x.sign) ? 1 : -1;
    if (final_sign == -1) res_str = "-" + res_str;

    return LongNumber(res_str.c_str());
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber res;
    LongNumber abs_x = x;
    LongNumber abs_this = *this;
    
    abs_x.sign = 1;
    abs_this.sign = 1;
    
    LongNumber abs_res = abs_this - (abs_this / abs_x) * abs_x;
    
    if (is_negative())
	{
        if (x.is_negative()) 
		{
            res = abs_res;
            if (abs_res != 0)
                res.sign = -1;
        } 
		else {
            res = x - abs_res;
            if (res == x) {
                res = LongNumber("0");
            }
        }
    } 
	else 
	{
        if (x.is_negative()) 
		{
            res = abs_res - x;
            if (res != 0)
                res.sign = -1;
        } 
		else
            res = abs_res;
    }
    
    return res;
}

bool LongNumber::is_negative() const noexcept {
	return (sign == -1);
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	if (not str)
		return 0;
	
	int length = 0;
	while (str[length] != '\0') 
		length++;
	return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace bdk {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.sign == -1) 
			os << '-';
		for (int i = 0; i < x.length; i++) 
			os << x.numbers[x.length - i - 1];
		return os;
	}
}