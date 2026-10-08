#pragma once

#include <QString>

namespace biv {
	struct KeyData {
		const int code;
		const QString text;
	};

	inline constexpr int KEY_BACKSPACE = 8;
	inline constexpr int KEY_ENTER = 13;
	inline constexpr int KEY_SPACE = 32;
}
