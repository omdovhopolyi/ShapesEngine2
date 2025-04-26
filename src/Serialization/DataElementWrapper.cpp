#include "DataElementWrapper.h"
#include "Utils/Assert.h"

namespace shen
{
    DataElementWrapper::DataElementWrapper() = default;

    DataElementWrapper::DataElementWrapper(SystemsManager* systems)
        : _systems(systems)
    {}

    DataElementWrapper::~DataElementWrapper() = default;

    void DataElementWrapper::LoadFile(const std::string& filename)
    {
        Assert(false, "");
    }

    bool DataElementWrapper::IsValid() const
    {
        Assert(false, "");
        return false;
    }

    void DataElementWrapper::SetupFirstElement()
    {
        Assert(false, "");
    }

    std::shared_ptr<DataElementWrapper> DataElementWrapper::GetChildElement(const std::string& id) const
    {
        Assert(false, "");
        return nullptr;
    }

    bool DataElementWrapper::HasElement(const std::string& id) const
    {
        Assert(false, "");
        return false;
    }

    bool DataElementWrapper::GetBool(const std::string& id, bool defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    int DataElementWrapper::GetInt(const std::string& id, int defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    float DataElementWrapper::GetFloat(const std::string& id, float defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    std::string DataElementWrapper::GetStr(const std::string& id, const std::string& defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    sf::Vector2f DataElementWrapper::GetVec2(const std::string& id, sf::Vector2f defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    sf::Vector2i DataElementWrapper::GetIntVec2(const std::string& id, sf::Vector2i defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    sf::FloatRect DataElementWrapper::GetFloatRect(const std::string& id, sf::FloatRect defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    sf::IntRect DataElementWrapper::GetIntRect(const std::string& id, sf::IntRect defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    sf::Color DataElementWrapper::GetColor(const std::string& id, sf::Color defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    std::vector<sf::IntRect> DataElementWrapper::GetVectorIntRect(const std::string& id, const std::string& itemId) const
    {
        Assert(false, "");
        return {};
    }

    std::vector<std::string> DataElementWrapper::GetVecStr(const std::string& id) const
    {
        Assert(false, "");
        return {};
    }

    sf::Transform DataElementWrapper::GetTransform(const std::string& id, const sf::Transform& defaultVal) const
    {
        Assert(false, "");
        return defaultVal;
    }

    void DataElementWrapper::SetBool(const std::string& id, bool val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetInt(const std::string& id, int val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetFloat(const std::string& id, float val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetStr(const std::string& id, const std::string& val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetVec2(const std::string& id, const sf::Vector2f& val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetFloatRect(const std::string& id, const sf::FloatRect& val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetIntRect(const std::string& id, const sf::IntRect& val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetColor(const std::string& id, const sf::Color& val)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetVectorIntRect(const std::string& id, const std::vector<sf::IntRect>& vec)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetVecStr(const std::string& id, const std::vector<std::string>& vec)
    {
        Assert(false, "");
    }

    void DataElementWrapper::SetTransform(const std::string& id, const sf::Transform& transform)
    {
        Assert(false, "");
    }

    void DataElementWrapper::ForAllChildren(const std::function<void(const DataElementWrapper& element)>& element) const
    {
        Assert(false, "");
    }

    void DataElementWrapper::ForAllChildren(const std::string& id, const std::function<void(const DataElementWrapper& element)>& element) const
    {
        Assert(false, "");
    }
}
