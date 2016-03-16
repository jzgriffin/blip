// Blip
// Copyright (c) Xettex 2016

#include "blip/path.hpp"
#include "blip/string.hpp"
#include <stdexcept>
#include <atlbase.h>
#include <shlobj.h>
#include <windows.h>

namespace {

using namespace blip;

/// \brief Finds the resources path
/// \return resources path
std::string find_resources_path()
{
    std::wstring path;
    do {
        path.resize(path.size() + MAX_PATH);
    } while (GetCurrentDirectoryW(path.size(), &path[0]) == 0);
    return narrow(path);
}

/// \brief Finds the preferences path
/// \return preferences path
std::string find_preferences_path()
{
    CComHeapPtr<wchar_t> path;
    auto hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);
    if (FAILED(hr)) {
        throw std::runtime_error{"unable to find system preferences path"};
    }
    return narrow(std::wstring{path});
}

}

namespace blip {

char const native_path_separator = '\\';
char const* path_separators = "\\/";

std::string find_system_path(system_path sys_path)
{
    switch (sys_path) {
        case system_path::resources_path:
            return find_resources_path();

        case system_path::preferences_path:
            return find_preferences_path();
    }
}

bool create_directory(std::string const& path)
{
    auto attr = GetFileAttributesA(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        auto pos = path.find_last_of(path_separators);
        if (pos != std::string::npos) {
            if (!create_directory(path.substr(0, pos))) {
                return false;
            }
        }

        return CreateDirectoryA(path.c_str(), nullptr);
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY)
        || (attr & FILE_ATTRIBUTE_REPARSE_POINT);
}

}
