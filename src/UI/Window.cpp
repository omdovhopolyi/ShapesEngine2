#include "Window.h"
#include "Utils/Assert.h"

namespace shen
{
    void Window::Init(SystemsManager* systems)
    {
        _systems = systems;
        Assert(_systems, "Invalid ui window initialization");
    }

    void Window::Update(float dt)
    {

    }

    void Window::Draw()
    {

    }
}
