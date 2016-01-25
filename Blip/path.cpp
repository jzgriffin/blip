// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the path manipulation function definitions
/// \ingroup path

#include "blip/path.hpp"
#include <algorithm>
#include <cstring>
#include <iterator>
#include <sstream>

namespace blip {

bool is_path_separator(char c)
{
    return std::strchr(path_separators, c) != nullptr;
}

std::string trim_path_before(std::string path)
{
    path.erase(std::begin(path), std::find_if_not(std::begin(path),
        std::end(path), is_path_separator));
    return path;
}

std::string trim_path_after(std::string path)
{
    path.erase(std::find_if_not(std::rbegin(path), std::rend(path),
        is_path_separator).base(), std::end(path));
    return path;
}

std::string trim_path(std::string path)
{
    return trim_path_after(trim_path_before(path));
}

std::string join_path(std::vector<std::string> const& parts)
{
    std::ostringstream os;
    auto is_first = true;
    for (auto part : parts) {
        if (is_first) {
            part = trim_path_after(part);
            is_first = false;
        } else {
            part = trim_path(part);
            if (part.empty()) {
                continue;
            }
            os << native_path_separator;
        }
        os << part;
    }
    return os.str();
}

std::vector<std::string> split_path(std::string const& path)
{
    std::vector<std::string> parts;
    auto first = std::begin(path);
    auto last = std::end(path);
    auto iter_i = first;
    auto iter_f = first;
    while (iter_i != last && iter_f != last) {
        while (iter_f != last && is_path_separator(*iter_f)) {
            ++iter_f;
        }
        while (iter_f != last && !is_path_separator(*iter_f)) {
            ++iter_f;
        }
        parts.emplace_back(iter_i, iter_f);
        while (iter_f != last && is_path_separator(*iter_f)) {
            ++iter_f;
        }
        iter_i = iter_f;
    }
    return parts;
}

}
