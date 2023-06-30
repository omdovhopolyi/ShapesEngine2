#include "GameWindow.h"
#include "Logger/Logger.h"

namespace shen
{
    bool GameWindow::Init()
    {
        // TODO assert
		return false;
    }

    void GameWindow::Destroy()
    {
    }

    int GameWindow::GetWidth() const
    {
        return _width;
    }

    void GameWindow::SetWidth(int width)
    {
        _width = width;
    }

    int GameWindow::GetHeight() const
    {
        return _height;
    }

    void GameWindow::SetHeight(int height)
    {
        _height = height;
    }

    void GameWindow::BeginFrame()
    {

    }

    void GameWindow::EndFrame()
    {

    }
}
