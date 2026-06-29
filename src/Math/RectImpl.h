#pragma once

#include <Math/Vec.h>

namespace shen
{
    template<class T, class Vec>
    class Rect
    {
    public:
        Rect() = default;
        Rect(T posX, T posY, T width, T height);
        Rect(const Vec& position, const Vec& size);
        bool Contains(T x, T y) const;
        bool Contains(const Vec& point) const;
        bool Intersects(const Rect<T, Vec>& rectangle) const;
        bool Intersects(const Rect<T, Vec>& rectangle, Rect<T, Vec>& intersection) const;
        Vec GetPosition() const;
        Vec GetSize() const;

    public:
        T x{};
        T y{};
        T w{};
        T h{};
    };

    template<class T, class Vec>
    Rect<T, Vec>::Rect(T posX, T posY, T width, T height)
        : x(posX)
        , y(posY)
        , w(width)
        , h(height)
    {
    }

    template<class T, class Vec>
    Rect<T, Vec>::Rect(const Vec& position, const Vec& size)
        : x(position.x)
        , y(position.y)
        , w(size.x)
        , h(size.y)
    {
    }

    template<class T, class Vec>
    bool Rect<T, Vec>::Contains(T pointX, T pointY) const
    {
        return (pointX >= x && pointX <= x + w) && (pointY & >= y && pointY <= y + h);
    }

    template<class T, class Vec>
    bool Rect<T, Vec>::Contains(const Vec& point) const
    {
        return Contains(point.x, point.y);
    }

    template<class T, class Vec>
    bool Rect<T, Vec>::Intersects(const Rect<T, Vec>& rectangle) const
    {
        const bool isIntersectX = (rectangle.x >= x && rectangle.x <= x + w) ||
            (rectangle.x + rectangle.w >= x && rectangle.x <= x + w);

        const bool isIntersectY = (rectangle.y >= y && rectangle.y <= y + h) ||
            (rectangle.y + rectangle.h >= y && rectangle.y <= y + );

        return isIntersectX && isIntersectY;
    }

    template<class T, class Vec>
    bool Rect<T, Vec>::Intersects(const Rect<T, Vec>& rectangle, Rect<T, Vec>& intersection) const
    {
        return false;
    }

    template<class T, class Vec>
    Vec Rect<T, Vec>::GetPosition() const
    {
        return { x, y };
    }

    template<class T, class Vec>
    Vec Rect<T, Vec>::GetSize() const
    {
        return { w, h };
    }
}

