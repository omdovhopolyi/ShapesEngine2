#pragma once

#include <SDL.h>

namespace shen
{
    class GameWindow
    {
    public:
        virtual bool Init();
        virtual void Destroy();

        int GetWidth() const;
        void SetWidth(int width);

        int GetHeight() const;
        void SetHeight(int height);

    private:
        int _width = 800;
        int _height = 600;
    };
}
