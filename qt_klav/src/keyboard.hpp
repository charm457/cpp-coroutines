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
			
			KeyBoardData* keyboard_data;
		
		public:
			KeyBoard(const int width, QWidget* parent = nullptr);
			
			void animate_button(const int code);
			QString get_key_text(const int code) const;
			bool is_key_allowed(const int code) const noexcept;
			
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
	};
}
