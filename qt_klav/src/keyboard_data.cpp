#include "keyboard_data.hpp"

using biv::KeyData;
using biv::KeyBoardData;

const std::vector<KeyData> KeyBoardData::KEYS = {
	{192, "Ё"}, {49, "1"}, {50, "2"}, {51, "3"}, {52, "4"}, {53, "5"}, {54, "6"}, 
		{55, "7"}, {56, "8"}, {57, "9"}, {48, "0"}, {189, "-"}, {187, "="}, 
	{81, "Й"}, {87, "Ц"}, {69, "У"}, {82, "К"}, {84, "Е"}, {89, "Н"}, {85, "Г"}, 
		{73, "Ш"}, {79, "Щ"}, {80, "З"}, {219, "Х"}, {221, "Ъ"}, {220, "\\"}, 
	{65, "Ф"}, {83, "Ы"}, {68, "В"}, {70, "А"}, {71, "П"}, {72, "Р"}, {74, "О"}, 
		{75, "Л"}, {76, "Д"}, {186, "Ж"}, {222, "Э"}, 
	{90, "Я"}, {88, "Ч"}, {67, "С"}, {86, "М"}, {66, "И"}, {78, "Т"}, {77, "Ь"}, 
		{188, "Б"}, {190, "Ю"}, {191, "."}
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
	
	return code == KEY_BACKSPACE || code == KEY_ENTER || code == KEY_SPACE;
}
