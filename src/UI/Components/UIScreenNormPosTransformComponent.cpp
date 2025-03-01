#include "UIScreenNormPosTransformComponent.h"
#include "UI/UINode.h"
#include "UI/UIWindow.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"

namespace shen
{
    void UIScreenNormPosTransformComponent::Init()
    {
    }

    void UIScreenNormPosTransformComponent::Update(float)
    {
        if (IsDirty())
        {
            SetDirty(false);
            UpdatePosition();
        }
    }

    void UIScreenNormPosTransformComponent::UpdatePosition()
    {
        auto window = _node->GetWindow();
        auto systems = window->GetSystemsManager();
        auto& world = systems->GetWorld();

        auto renderTargets = systems->GetSystem<SfmlRenderTargetsSystem>();
        auto target = renderTargets->GetRenderTexture(SfmlRenderTargetsSystem::UITargetId);
        auto targetSize = target->getSize();

        sf::Transform transform;
        transform.rotate(_angle);
        transform.scale(_scale);

        sf::Vector2f position;
        position.x = targetSize.x * _normPosition.x;
        position.y = targetSize.y * _normPosition.y;

        transform.translate(position);

        _node->SetTransform(transform);
    }
}

