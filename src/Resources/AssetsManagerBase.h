#pragma once

namespace shen
{
    class AssetsManagerBase
    {
    public:
        virtual bool Init() { return false; }
        virtual void Clear() {}
    };
}
