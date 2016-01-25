// Blip
// Copyright (c) Xettex 2016

#include "blip/path.hpp"
#include <stdexcept>
#import <Foundation/Foundation.h>

namespace {

/// \brief Finds the resources path
/// \return resources path
std::string find_resources_path()
{
    return [[[NSBundle mainBundle] resourcePath] UTF8String];
}

/// \brief Finds the preferences path
/// \return preferences path
std::string find_preferences_path()
{
    auto paths = NSSearchPathForDirectoriesInDomains(
        NSApplicationSupportDirectory, NSUserDomainMask, YES);
    if (paths == nil || [paths count] == 0) {
        throw std::runtime_error{"unable to find system preferences path"};
    }
    return [[paths objectAtIndex:0] UTF8String];
}

}

namespace blip {

char const native_path_separator = '/';
char const* path_separators = "/";

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
    return [[NSFileManager defaultManager]
        createDirectoryAtPath:[NSString stringWithUTF8String:path.c_str()]
        withIntermediateDirectories:YES attributes:nil error:nil];
}

}
