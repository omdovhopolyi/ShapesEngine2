#pragma once

#include <glm/glm.hpp>

namespace shen
{
    class Camera
    {
    public:
        void Init();
        
        void SetPosition(const glm::vec2& position);
        glm::vec2 GetPosition() const;

        void SetSize(const glm::vec2& size);
        glm::vec2 GetSize() const;

        void SetWorldSize(const glm::vec2& size);

        void SetBounds(const glm::vec2& boundsH, const glm::vec2& boundsV);
        void SetBoundsTL(const glm::vec2& bounds);
        void SetBoundsBR(const glm::vec2& bounds);
        glm::vec2 GetBoundsTL() const;
        glm::vec2 GetBoundsBR() const;

        void LookAt(const glm::vec2& target);

    private:
        glm::vec2 _position;
        glm::vec2 _size;
        glm::vec2 _worldSize;
        glm::vec2 _boundsTL;
        glm::vec2 _boundsBR;
    };
}
