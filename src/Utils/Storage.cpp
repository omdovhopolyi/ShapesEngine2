#include "Storage.h"

namespace shen
{
    bool Storage::SetVar(const std::string& key, const std::any& var)
    {
        const auto [it, isInserted] = _vars.insert({ key, var });
        return isInserted;
    }

    bool Storage::HasVar(const std::string& key) const
    {
        return _vars.find(key) != _vars.end();
    }
}
