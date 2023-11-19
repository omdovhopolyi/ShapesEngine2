#include "Common.h"
#include "Logger/Logger.h"

namespace shen
{
    KeyEvent::KeyEvent(InputEventType eventType, int keyCode, KeyMode keyMode)
        : type(eventType)
        , code(keyCode)
        , mode(keyMode)
    {
        Logger::Log("Key {}", static_cast<char>(keyCode));
    }

    MouseButtonEvent::MouseButtonEvent(InputEventType eventType, MouseButton mouseBtn, KeyMode keyMode, int posX, int posY)
        : type(eventType)
        , button(mouseBtn)
        , mode(keyMode)
        , x(posX)
        , y(posY)
    {
        Logger::Log("Mouse button");
    }

    MouseMoveEvent::MouseMoveEvent(int posX, int posY, int diffX, int diffY, KeyMode keyMode)
        : x(posX)
        , y(posY)
        , dx(diffX)
        , dy(diffY)
        , mode(keyMode)
    { 
        //Logger::Log("Mouse move");
    }
}
