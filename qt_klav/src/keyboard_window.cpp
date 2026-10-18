#include "keyboard_window.hpp"

#include <iostream>

#include <QHBoxLayout>
#include <QKeyEvent>       // Добавлено для корректной работы QKeyEvent
#include <QKeySequence>
#include <QLabel>
#include <QPixmap>
#include <QTextCursor>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
    // 1. Разрешаем окну принимать фокус клавиатуры
    setFocusPolicy(Qt::StrongFocus);

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
    
    connect(keyboard, &KeyBoard::key_clicked, this, &KeyBoardWindow::on_key_clicked);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
}

void KeyBoardWindow::open_window() {
    show();
    raise();
    activateWindow();
    setFocus();
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    const int key = event->key(); 
    std::cout << "[Физ. клавиатура] клавиша " << key << std::endl;
    if (!keyboard->is_key_allowed(key)) {
        QWidget::keyPressEvent(event);
        return;
    }
    
    if (key == KEY_SHIFT) {
        keyboard->set_shift_held(true);
        return;
    }
    
    if (key == KEY_CAPS) {
        if (!event->isAutoRepeat()) {
            handle_key(key);
        }
        return;
    }
    
    keyboard->animate_button(key);
    handle_key(key);
}

void KeyBoardWindow::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == KEY_SHIFT) { 
        keyboard->set_shift_held(false);
    }
    
    QWidget::keyReleaseEvent(event);
}

// ----------------------------------------------------------------------------
// 						PRIVATE
// ----------------------------------------------------------------------------
void KeyBoardWindow::on_key_clicked(const int code) {
    if (!keyboard->is_key_allowed(code)) {
        return;
    }
    handle_key(code);
}

void KeyBoardWindow::handle_key(const int code) {
    if (code == KEY_BACKSPACE) {
        delete_last_char();
    } else if (code == KEY_ENTER) {
        insert_text("\n");
    } else if (code == KEY_SPACE) {
        insert_text(" ");
    } else if (code == KEY_TAB) {
        insert_text("\t");
    } else if (code == KEY_SHIFT) {
        keyboard->toggle_shift();
    } else if (code == KEY_CAPS) {
        keyboard->toggle_caps();
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