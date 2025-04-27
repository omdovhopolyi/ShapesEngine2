#include "FilePath.h"
#include <format>

namespace shen
{
    std::string FilePath::Path(const char* path)
    {
#ifdef _DEBUG
        return std::format("../{}", path);
#endif
        return path;
    }

    std::string FilePath::Path(const std::string& path)
    {
        return Path(path.c_str());
    }
}
