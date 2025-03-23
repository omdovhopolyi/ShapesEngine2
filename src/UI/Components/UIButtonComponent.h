#pragma once

#include "UIInputComponent.h"
#include "Enums/ButtonSpriteEnum.h"
#include <SFML/Graphics/Sprite.hpp>
#include <functional>

namespace shen
{
    enum class ButtonSignalType
    {
        Down,
        Up
    };

    class ButtonSignal
    {
    public:
        using Callback = std::function<void()>;
        using ListCallbacks = std::vector<std::function<void()>>;

        void Subscribe(ButtonSignalType type, const Callback& callback);
        void Clear();

        void OnEvent(ButtonSignalType type);

    public:
        std::map<ButtonSignalType, ListCallbacks> _subscriptions;
    };

    class UIButtonComponent
        : public UIInputComponent
    {
    public:
        void Draw(sf::RenderTarget& target, const sf::Transform& transform) const override;

        void SetSprite(ButtonSpriteType type, const sf::Sprite& sprite);

        void SetIdle(const sf::Sprite& sprite);
        sf::Sprite& GetIdle();

        void SetPressed(const sf::Sprite& sprite);
        sf::Sprite& GetPressed();

        void SetHovered(const sf::Sprite& sprite);
        sf::Sprite& GetHovered();

        void SetHoverSoundId(const std::string& id);
        void SetPressSoundId(const std::string& id);
        void SetReleaseSoundId(const std::string& id);

        bool ProcessInput(const InputType& inputType, const CommandContext& context) override;

        ButtonSignal& GetSignal() { return _signal; }

    private:
        bool HandleCursorPress(const InputType& inputType, const CommandContext& context);
        bool HandleCursorRelease(const InputType& inputType, const CommandContext& context);
        bool HandleCursorMove(const InputType& inputType, const CommandContext& context);

        bool IsCursorOverButton(const InputType& inputType, const CommandContext& context);

        void SetCurrentSprite(const sf::Sprite& sprite);

        void SetHovered(bool hovered);
        bool IsHovered() const;

        void SetPressed(bool pressed);
        bool IsPressed() const;

    private:
        sf::Sprite _current;
        sf::Sprite _idle;
        sf::Sprite _pressed;
        sf::Sprite _hovered;
        std::string _soundHover;
        std::string _soundPress;
        std::string _soundRelease;
        bool _isHovered = false;
        bool _isPressed = false;
        ButtonSignal _signal;
    };
}
