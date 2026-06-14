#include "InputType.h"

namespace shen
{
    bool operator < (const InputType& left, const InputType& right)
    {
        if (left.keyCode != right.keyCode)
        {
            return left.keyCode < right.keyCode;
        }
        if (left.mouseButton != right.mouseButton)
        {
            return left.mouseButton < right.mouseButton;
        }
        if (left.type != right.type)
        {
            return left.type < right.type;
        }

        return false;
    }

    bool operator == (const InputType& left, const InputType& right)
    {
        return (left.keyCode == right.keyCode && left.keyCode > -1 &&
            left.mouseButton == right.mouseButton &&
            left.type == right.type &&
            left.alt == right.alt &&
            left.shift == right.shift &&
            left.ctrl == right.ctrl);
    }
}
