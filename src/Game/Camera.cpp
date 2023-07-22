#include "Camera.h"

#include "ManagersProvider.h"
#include "GameWindow.h"

namespace shen
{
    void Camera::Init()
    {
        auto window = ManagersProvider::Instance().GetGameWindow();
        
        glm::vec2 size;
        size.x = window->GetWidth();
        size.y = window->GetHeight();

        SetSize(size);

        SetBounds(glm::vec2(-50.f, -50.f), glm::vec2(50.f, 50.f));
    }

    void Camera::SetPosition(const glm::vec2& position)
    {
        _position = position;
    }

    glm::vec2 Camera::GetPosition() const
    {
        return _position;
    }

    void Camera::SetSize(const glm::vec2& size)
    {
        _size = size;
    }

    glm::vec2 Camera::GetSize() const
    {
        return _size;
    }

    void Camera::SetWorldSize(const glm::vec2& size)
    {
        _worldSize = size;
    }

    void Camera::SetBounds(const glm::vec2& boundsTL, const glm::vec2& boundsBR)
    {
        _boundsTL = boundsTL;
        _boundsBR = boundsBR;
    }

    void Camera::SetBoundsTL(const glm::vec2& bounds)
    {
        _boundsTL = bounds;
    }

    void Camera::SetBoundsBR(const glm::vec2& bounds)
    {
        _boundsBR = bounds;
    }

    glm::vec2 Camera::GetBoundsTL() const
    {
        return _boundsTL;
    }

    glm::vec2 Camera::GetBoundsBR() const
    {
        return _boundsBR;
    }

    void Camera::LookAt(const glm::vec2& target)
    {
        auto center = _size / 2.f;
        _position = target - center;

        if (_position.x < _boundsTL.x)
        {
            _position.x = _boundsTL.x;
        }
        else if (_position.x + _size.x > _worldSize.x + _boundsBR.x)
        {
            _position.x = _worldSize.x + _boundsBR.x - _size.x;
        }

        if (_position.y < _boundsTL.y)
        {
            _position.y = _boundsTL.y;
        }
        else if (_position.y + _size.y > _worldSize.y + _boundsBR.y)
        {
            _position.y = _worldSize.y + _boundsBR.y - _size.y;
        }
    }
}
