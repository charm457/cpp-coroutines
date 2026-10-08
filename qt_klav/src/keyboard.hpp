#pragma once

#include <cstddef>
#include <unordered_map>

#include <QGridLayout>
#include <QWidget>

#include "keyboard_button.hpp"
#include "keyboard_data.hpp"
#include "key_data.hpp"

namespace biv {
	class KeyBoard : public QWidget {
		Q_OBJECT
		
		private:
			const int button_width;
			std::unordered_map<int, KeyBoardButton*> buttons;
			std::vector<KeyBoardButton*> shift_buttons;
			
			KeyBoardData* keyboard_data;
			
			bool shift_on = false;    // экранный Shift (защёлка)
			bool shift_held = false;  // физический Shift зажат
			bool caps_on = false;     // CapsLock
		
		public:
			KeyBoard(const int width, QWidget* parent = nullptr);
			
			void animate_button(const int code);
			QString get_key_text(const int code) const;
			bool is_key_allowed(const int code) const noexcept;
			
			void toggle_shift();
			void toggle_caps();
			void set_shift_held(const bool held);
			
		signals:
			void key_clicked(const int code);
			
		private:
			void create_buttons(
				const std::vector<KeyData>& data, 
				QGridLayout* layout, 
				const int line,
				const int start_position
			);
			
			void register_button(KeyBoardButton* btn, const int code);
			void update_shift_buttons();
	};
}
