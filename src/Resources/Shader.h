#pragma once

namespace shen
{
    class Shader
    {
    public:
        void Use();

        void SetId(unsigned int id) { _id = id; }
        unsigned int GetId() const { return _id; }

    private:
        unsigned int _id = 0;
    };
}
