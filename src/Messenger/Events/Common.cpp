#include "Common.h"

namespace shen
{
    KeyEvent::KeyEvent(KeyEventType eventType, int keyCode)
        : type(eventType)
        , code(keyCode)
    { }

    MouseButtonEvent::MouseButtonEvent(KeyEventType eventType, MouseButton mouseBtn, int posX, int posY)
        : type(eventType)
        , button(mouseBtn)
        , x(posX)
        , y(posY)
    { }

    MouseMoveEvent::MouseMoveEvent(int posX, int posY, int diffX, int diffY)
        : x(posX)
        , y(posY)
        , dx(diffX)
        , dy(diffY)
    { }
}
