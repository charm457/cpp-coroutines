#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QPlainTextEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
	class KeyBoardWindow : public QWidget {
		private:
			QPlainTextEdit* display;
			KeyBoard* keyboard;

		public:
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			void keyPressEvent(QKeyEvent* event) override;

		private:
			void handle_key(const int code);
			void insert_text(const QString& text);
			void delete_last_char();
	};
}
