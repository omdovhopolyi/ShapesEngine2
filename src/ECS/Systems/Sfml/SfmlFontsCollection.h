#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <map>
#include <memory>

namespace shen
{
    class SfmlFontsCollection
        : public System
    {
    public:
        void Start() override;
        void Stop() override;

        void LoadFonts();
        sf::Font* LoadFont(const std::string& id, const std::string& fileName);
        sf::Font* GetFont(const std::string& id);
        void RemoveFont(const std::string& id);
        const std::string& GetFontPath(const std::string& id) const;

    public:
        void LoadFontsPaths(const std::string& fileName);

    private:
        std::map<std::string, std::unique_ptr<sf::Font>> _fonts;
        std::map<std::string, std::string> _paths;
    };
}
