#include <QApplication>

#include "keyboard_window.hpp"
#include "welcome_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
	
    biv::WelcomeWindow welcome_window;
    biv::KeyBoardWindow keyboard_window;

    QObject::connect(&welcome_window, &biv::WelcomeWindow::keyboard_requested,
        &keyboard_window, &biv::KeyBoardWindow::open_window);
    QObject::connect(&welcome_window, &biv::WelcomeWindow::keyboard_requested,
        &welcome_window, &QWidget::hide);

    welcome_window.show();
	
    return app.exec();
}
