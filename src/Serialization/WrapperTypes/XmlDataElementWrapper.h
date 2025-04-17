#pragma once

#include "Serialization/DataElementWrapper.h"
#include <tinyxml2/tinyxml2.h>
#include <string>
#include <vector>

namespace shen
{
    class SystemsManager;

    class XmlDataElementWrapper final
        : public DataElementWrapper
    {
    public:
        XmlDataElementWrapper(SystemsManager* systems, tinyxml2::XMLElement* element);
        XmlDataElementWrapper(SystemsManager* systems);

        void LoadFile(const std::string& filename) override;
        bool IsValid() const override;

        std::shared_ptr<DataElementWrapper> GetChildElement(const std::string& id) const override;
        bool HasElement(const std::string& id) const override;

        bool GetBool(const std::string& id, bool defaultVal = false) const override;
        int GetInt(const std::string& id, int defaultVal = 0) const override;
        float GetFloat(const std::string& id, float defaultVal = 0.f) const override;
        std::string GetStr(const std::string& id, const std::string& defaultVal = {}) const override;
        sf::Vector2f GetVec2(const std::string& id, sf::Vector2f defaultVal = sf::Vector2f()) const override;
        sf::Vector2i GetIntVec2(const std::string& id, sf::Vector2i defaultVal = sf::Vector2i()) const override;
        sf::FloatRect GetFloatRect(const std::string& id, sf::FloatRect defaultVal = {}) const override;
        sf::IntRect GetIntRect(const std::string& id, sf::IntRect defaultVal = {}) const override;
        sf::Color GetColor(const std::string& id, sf::Color defaultVal = sf::Color::Transparent) const override;
        std::vector<sf::IntRect> GetVectorIntRect(const std::string& id) const override;
        std::vector<std::string> GetVecStr(const std::string& id) const override;
        sf::Transform GetTransform(const std::string& id, const sf::Transform& defaultVal = {}) const override;

        void SetBool(const std::string& id, bool val) override;
        void SetInt(const std::string& id, int val) override;
        void SetFloat(const std::string& id, float val) override;
        void SetStr(const std::string& id, const std::string& val) override;
        void SetVec2(const std::string& id, const sf::Vector2f& val) override;
        void SetFloatRect(const std::string& id, const sf::FloatRect& val) override;
        void SetIntRect(const std::string& id, const sf::IntRect& val) override;
        void SetColor(const std::string& id, const sf::Color& val) override;
        void SetVectorIntRect(const std::string& id, const std::vector<sf::IntRect>& vec) override;
        void SetVecStr(const std::string& id, const std::vector<std::string>& vec) override;
        void SetTransform(const std::string& id, const sf::Transform& transform) override;

        void ForAllChildren(const std::function<void(const DataElementWrapper& element)>& func) const override;
        void ForAllChildren(const std::string& id, const std::function<void(const DataElementWrapper& element)>& func) const override;

    private:
        tinyxml2::XMLElement* _element = nullptr;
        std::shared_ptr<tinyxml2::XMLDocument> _document;
    };
}
