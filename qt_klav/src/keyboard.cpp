#include "keyboard.hpp"

using biv::KeyBoard;

KeyBoard::KeyBoard(const int width, QWidget* parent) 
	: button_width(width / 29), QWidget(parent) {

	keyboard_data = new KeyBoardData();
	
    QGridLayout* keys_layout = new QGridLayout(this);
	keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);
	
	// 1-я линия
	create_buttons(keyboard_data->get_line1(), keys_layout, 0, 0);
	
	KeyBoardButton* backspace_btn = new KeyBoardButton("Удалить");
	backspace_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(backspace_btn, 0, 26, 2, 3);
	buttons[KEY_BACKSPACE] = backspace_btn;

	// 2-я линия
	KeyBoardButton* tab_btn = new KeyBoardButton("Tab");
	tab_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(tab_btn, 2, 0, 2, 3);
	
	create_buttons(keyboard_data->get_line2(), keys_layout, 2, 3);
	
	// 3-я линия
	KeyBoardButton* caps_btn = new KeyBoardButton("Caps");
	caps_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(caps_btn, 4, 0, 2, 4);
	
	create_buttons(keyboard_data->get_line3(), keys_layout, 4, 4);
	
	KeyBoardButton* enter_btn = new KeyBoardButton("Enter");
	enter_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(enter_btn, 4, 26, 2, 3);
	buttons[KEY_ENTER] = enter_btn;
	
	// 4-я линия
	KeyBoardButton* left_shift_btn = new KeyBoardButton("Shift");
	left_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(left_shift_btn, 6, 0, 2, 5);
	
	create_buttons(keyboard_data->get_line4(), keys_layout, 6, 5);
	
	KeyBoardButton* right_shift_btn = new KeyBoardButton("Shift");
	right_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(right_shift_btn, 6, 25, 2, 4);

	// 5-я линия
	KeyBoardButton* space = new KeyBoardButton();
	space->setMinimumSize(8 * button_width, button_width);
	keys_layout->addWidget(space, 8, 7, 2, 16);
	buttons[KEY_SPACE] = space;
}

void KeyBoard::animate_button(const int code) {
	buttons.at(code)->animateClick();
}

QString KeyBoard::get_key_text(const int code) const {
	return buttons.at(code)->text();
}

bool KeyBoard::is_key_allowed(const int code) const noexcept {
	return keyboard_data->is_key_allowed(code);
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
void KeyBoard::create_buttons(
	const std::vector<KeyData>& data, 
	QGridLayout* layout, 
	const int line,
	const int start_position
) {
	for (int i = 0; i < data.size(); i++) {
        KeyBoardButton* btn = new KeyBoardButton(data[i].text);
		btn->setMinimumSize(button_width, button_width);
        
		layout->addWidget(btn, line, i * 2 + start_position, 2, 2);
		
		buttons[data[i].code] = btn;
	}
}
