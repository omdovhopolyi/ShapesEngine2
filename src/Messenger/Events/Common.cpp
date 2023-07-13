#include "Common.h"

namespace shen
{
    KeyEvent::KeyEvent(KeyEventType eventType, int keyCode)
        : type(eventType)
        , code(keyCode)
    { }
}