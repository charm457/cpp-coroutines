#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QTextCursor>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");
	
	QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QPlainTextEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setFocusPolicy(Qt::NoFocus);
	display->setPlainText("Помоги мне заработать лучше...");

	keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	const int key = event->nativeVirtualKey();
	if (!keyboard->is_key_allowed(key)) {
		QWidget::keyPressEvent(event);
		return;
	}
	
	keyboard->animate_button(key);
	handle_key(key);
}

// ----------------------------------------------------------------------------
// 						PRIVATE
// ----------------------------------------------------------------------------
void KeyBoardWindow::handle_key(const int code) {
	if (code == KEY_BACKSPACE) {
		delete_last_char();
	} else if (code == KEY_ENTER) {
		insert_text("\n");
	} else if (code == KEY_SPACE) {
		insert_text(" ");
	} else {
		insert_text(keyboard->get_key_text(code));
	}
}

void KeyBoardWindow::insert_text(const QString& text) {
	QTextCursor cursor = display->textCursor();
	cursor.movePosition(QTextCursor::End);
	cursor.insertText(text);
	display->setTextCursor(cursor);
	display->ensureCursorVisible();
}

void KeyBoardWindow::delete_last_char() {
	QTextCursor cursor = display->textCursor();
	cursor.movePosition(QTextCursor::End);
	cursor.deletePreviousChar();
	display->setTextCursor(cursor);
}
