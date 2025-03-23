#include "Asset.h"

namespace shen
{
    Asset::~Asset() = default;

    std::vector<std::unique_ptr<SerializableField>>& Asset::GetFields()
    {
        return _fields;
    }
}
