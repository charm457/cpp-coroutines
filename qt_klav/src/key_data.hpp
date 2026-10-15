#pragma once

#include <QString>
#include <Qt> 

namespace biv {
    struct KeyData {
        const int code;
        const QString text;
    };

    inline constexpr int KEY_BACKSPACE = Qt::Key_Backspace;
    inline constexpr int KEY_TAB       = Qt::Key_Tab;
    inline constexpr int KEY_ENTER     = Qt::Key_Return; // В Qt основной Enter это Key_Return
    inline constexpr int KEY_SHIFT     = Qt::Key_Shift;
    inline constexpr int KEY_CAPS      = Qt::Key_CapsLock;
    inline constexpr int KEY_SPACE     = Qt::Key_Space;
}