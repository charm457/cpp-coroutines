#include "keyboard_data.hpp"
#include <Qt> 

using biv::KeyData;
using biv::KeyBoardData;

const std::vector<KeyData> KeyBoardData::KEYS = {
    // 1-я линия (цифры и знаки)
    {Qt::Key_QuoteLeft, "Ё"}, 
    {Qt::Key_1, "1"}, {Qt::Key_2, "2"}, {Qt::Key_3, "3"}, {Qt::Key_4, "4"}, 
    {Qt::Key_5, "5"}, {Qt::Key_6, "6"}, {Qt::Key_7, "7"}, {Qt::Key_8, "8"}, 
    {Qt::Key_9, "9"}, {Qt::Key_0, "0"}, 
    {Qt::Key_Minus, "-"}, {Qt::Key_Equal, "="}, 
    
    // 2-я линия
    {Qt::Key_Q, "Й"}, {Qt::Key_W, "Ц"}, {Qt::Key_E, "У"}, {Qt::Key_R, "К"}, 
    {Qt::Key_T, "Е"}, {Qt::Key_Y, "Н"}, {Qt::Key_U, "Г"}, {Qt::Key_I, "Ш"}, 
    {Qt::Key_O, "Щ"}, {Qt::Key_P, "З"}, {Qt::Key_BracketLeft, "Х"}, 
    {Qt::Key_BracketRight, "Ъ"}, {Qt::Key_Backslash, "\\"}, 
    
    // 3-я линия
    {Qt::Key_A, "Ф"}, {Qt::Key_S, "Ы"}, {Qt::Key_D, "В"}, {Qt::Key_F, "А"}, 
    {Qt::Key_G, "П"}, {Qt::Key_H, "Р"}, {Qt::Key_J, "О"}, {Qt::Key_K, "Л"}, 
    {Qt::Key_L, "Д"}, {Qt::Key_Semicolon, "Ж"}, {Qt::Key_Apostrophe, "Э"}, 
    
    // 4-я линия
    {Qt::Key_Z, "Я"}, {Qt::Key_X, "Ч"}, {Qt::Key_C, "С"}, {Qt::Key_V, "М"}, 
    {Qt::Key_B, "И"}, {Qt::Key_N, "Т"}, {Qt::Key_M, "Ь"}, 
    {Qt::Key_Comma, "Б"}, {Qt::Key_Period, "Ю"}, {Qt::Key_Slash, "."}
};

std::vector<KeyData> KeyBoardData::get_line1() const {
	return {KEYS.begin(), KEYS.begin() + 13};
}

std::vector<KeyData> KeyBoardData::get_line2() const {
	return {KEYS.begin() + 13, KEYS.begin() + 26};
}

std::vector<KeyData> KeyBoardData::get_line3() const {
	return {KEYS.begin() + 26, KEYS.begin() + 37};
}

std::vector<KeyData> KeyBoardData::get_line4() const {
	return {KEYS.begin() + 37, KEYS.begin() + 47};
}

bool KeyBoardData::is_key_allowed(const int code) const noexcept {
	for (const KeyData& key: KEYS) {
		if (key.code == code) {
			return true;
		}
	}
	
	return code == KEY_BACKSPACE || code == KEY_TAB || code == KEY_ENTER
		|| code == KEY_SHIFT || code == KEY_CAPS || code == KEY_SPACE;
}
