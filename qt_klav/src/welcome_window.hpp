#pragma once

#include <QWidget>

namespace biv {
	class WelcomeWindow : public QWidget {
		Q_OBJECT

		public:
			WelcomeWindow(QWidget* parent = nullptr);

		signals:
			void keyboard_requested();
	};
}