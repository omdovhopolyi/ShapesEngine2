#pragma once

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
}
