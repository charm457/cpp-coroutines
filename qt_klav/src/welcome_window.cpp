#include "welcome_window.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using biv::WelcomeWindow;

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent) {
	resize(500, 420);
	setWindowTitle("Добро пожаловать");

	QLabel* smile = new QLabel(this);
	smile->setText("\U0001F60A");
	smile->setAlignment(Qt::AlignCenter);
	smile->setFixedSize(160, 160);
	smile->setStyleSheet("font-size: 96px;");

	QLabel* title = new QLabel("Привет!", this);
	title->setAlignment(Qt::AlignCenter);
	title->setStyleSheet("font-size: 30px; font-weight: bold;");

	QLabel* subtitle = new QLabel("Грустная Клавиатура тебя ждет.", this);
	subtitle->setAlignment(Qt::AlignCenter);
	subtitle->setStyleSheet("font-size: 16px;");

	QPushButton* go_to_keyboard = new QPushButton("Перейти к клавиатуре", this);
	go_to_keyboard->setMinimumHeight(52);
	go_to_keyboard->setStyleSheet("font-size: 18px;");

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addStretch();
	layout->addWidget(smile);
	layout->addWidget(title);
	layout->addWidget(subtitle);
	layout->addSpacing(20);
	layout->addWidget(go_to_keyboard);
	layout->addStretch();

	connect(go_to_keyboard, &QPushButton::clicked, this, &WelcomeWindow::keyboard_requested);
}