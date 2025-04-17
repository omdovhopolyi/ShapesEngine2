#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace shen
{
    class SystemsManager;

    class DataElementWrapper
    {
    public:
        DataElementWrapper();
        DataElementWrapper(SystemsManager* systems);
        virtual ~DataElementWrapper();

        SystemsManager* GetSystems() const { return _systems; }

        virtual void LoadFile(const std::string& filename);
        virtual bool IsValid() const;

        virtual void SetupFirstElement();
        
        virtual std::shared_ptr<DataElementWrapper> GetChildElement(const std::string& id) const;
        virtual bool HasElement(const std::string& id) const;

        virtual bool GetBool(const std::string& id, bool defaultVal = false) const;
        virtual int GetInt(const std::string& id, int defaultVal = 0) const;
        virtual float GetFloat(const std::string& id, float defaultVal = 0.f) const;
        virtual std::string GetStr(const std::string& id, const std::string& defaultVal = {}) const;
        virtual sf::Vector2f GetVec2(const std::string& id, sf::Vector2f defaultVal = sf::Vector2f()) const;
        virtual sf::Vector2i GetIntVec2(const std::string& id, sf::Vector2i defaultVal = sf::Vector2i()) const;
        virtual sf::FloatRect GetFloatRect(const std::string& id, sf::FloatRect def = {}) const;
        virtual sf::IntRect GetIntRect(const std::string& id, sf::IntRect def = {}) const;
        virtual sf::Color GetColor(const std::string& id, sf::Color defaultVal = sf::Color::Transparent) const;
        virtual std::vector<sf::IntRect> GetVectorIntRect(const std::string& id) const;
        virtual std::vector<std::string> GetVecStr(const std::string& id) const;
        virtual sf::Transform GetTransform(const std::string& id, const sf::Transform& defaultVal = {}) const;

        virtual void SetBool(const std::string& id, bool val);
        virtual void SetInt(const std::string& id, int val);
        virtual void SetFloat(const std::string& id, float val);
        virtual void SetStr(const std::string& id, const std::string& val);
        virtual void SetVec2(const std::string& id, const sf::Vector2f& val);
        virtual void SetFloatRect(const std::string& id, const sf::FloatRect& val);
        virtual void SetIntRect(const std::string& id, const sf::IntRect& val);
        virtual void SetColor(const std::string& id, const sf::Color& val);
        virtual void SetVectorIntRect(const std::string& id, const std::vector<sf::IntRect>& vec);
        virtual void SetVecStr(const std::string& id, const std::vector<std::string>& vec);
        virtual void SetTransform(const std::string& id, const sf::Transform& transform);

        virtual void ForAllChildren(const std::function<void(const DataElementWrapper& element)>& element) const;
        virtual void ForAllChildren(const std::string& id, const std::function<void(const DataElementWrapper& element)>& element) const;

    private:
        SystemsManager* _systems = nullptr;
    };
}
