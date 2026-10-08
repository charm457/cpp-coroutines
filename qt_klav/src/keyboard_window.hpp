#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QPlainTextEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
	class KeyBoardWindow : public QWidget {
		Q_OBJECT

		private:
			QPlainTextEdit* display;
			KeyBoard* keyboard;

		public:
			KeyBoardWindow(QWidget* parent = nullptr);

		public slots:
			void open_window();

		protected:
			void keyPressEvent(QKeyEvent* event) override;

		private slots:
			void on_key_clicked(const int code);
			
		private:
			void handle_key(const int code);
			void insert_text(const QString& text);
			void delete_last_char();
	};
}
