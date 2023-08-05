#pragma once

#include <set>

namespace shen
{
    enum class RangeType
    {
        ExcludeBoth,
        IncludeFrom,
        IncludeTo,
        IncludeBoth
    };

    template<class T>
    class Range
    {
    public:
        Range() { }

        Range(const T& from, const T& to, RangeType type)
            : _from(from)
            , _to(to)
            , _type(type)
        { }

        bool IsInRange(const T& value)
        {
            if (_type == RangeType::ExcludeBoth)
            {
                return value > _from && value < _to;
            }
            else if (_type == RangeType::IncludeFrom)
            {
                return value >= _from && value < _to;
            }
            else if (_type == RangeType::IncludeTo)
            {
                return value > _from && value <= _to;
            }
            else
            {
                return value >= _from && value <= _to;
            }
        }

    private:
        T _from{};
        T _to{};
        RangeType _type = RangeType::ExcludeBoth;
    };

    template<class T>
    class Rounder
    {
    public:
        void AddPoint(const T& pointValue)
        {
            _valuePoints.insert(pointValue);
        }

        T Round(const T& value)
        {
            if (value >= *_valuePoints.crbegin())
            {
                return *_valuePoints.crbegin();
            }
            if (value <= *_valuePoints.cbegin())
            {
                return *_valuePoints.cbegin();
            }

            T prev = *_valuePoints.begin();
            T next = *_valuePoints.begin();

            for (const auto& point : _valuePoints)
            {
                if (value == point)
                {
                    return value;
                }

                next = point;

                if (value > point)
                {
                    break;
                }

                prev = point;
            }

            const auto average = (prev + next) / static_cast<T>(2);

            if (value >= average)
            {
                return next;
            }
            else
            {
                return prev;
            }
        }

    private:
        std::set<T> _valuePoints;
    };
}
