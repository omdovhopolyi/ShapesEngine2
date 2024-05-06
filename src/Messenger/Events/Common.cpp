#include "Common.h"
#include "Logger/Logger.h"

namespace shen
{
    KeyEvent::KeyEvent(InputEventType eventType, int keyCode, bool altMode, bool shiftMode, bool ctrlMode)
        : type(eventType)
        , code(keyCode)
        , alt(altMode)
        , shift(shiftMode)
        , ctrl(ctrlMode)
    {
        //Logger::Log("Key {}", static_cast<char>(keyCode));
    }

    MouseButtonEvent::MouseButtonEvent(InputEventType eventType, MouseButton mouseBtn, int posX, int posY, bool altMode, bool shiftMode, bool ctrlMode)
        : type(eventType)
        , button(mouseBtn)
        , x(posX)
        , y(posY)
        , alt(altMode)
        , shift(shiftMode)
        , ctrl(ctrlMode)
    {
        //Logger::Log("Mouse button");
    }

    MouseMoveEvent::MouseMoveEvent(int posX, int posY, int diffX, int diffY, bool altMode, bool shiftMode, bool ctrlMode)
        : x(posX)
        , y(posY)
        , dx(diffX)
        , dy(diffY)
        , alt(altMode)
        , shift(shiftMode)
        , ctrl(ctrlMode)
    { 
        //Logger::Log("Mouse move");
    }

    MouseWheelEvent::MouseWheelEvent(int posX, int posY, int scrl, bool altMode, bool shiftMode, bool ctrlMode)
        : x(posX)
        , y(posY)
        , scroll(scrl)
        , alt(altMode)
        , shift(shiftMode)
        , ctrl(ctrlMode)
    {
        //Logger::Log("Mouse wheel scroll");
    }
}
