// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the string manipulation function definitions
/// \ingroup string

#include "blip/string.hpp"
#include <codecvt>
#include <locale>

namespace blip {

std::string narrow(std::wstring const& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    return cvt.to_bytes(str);
}

std::wstring widen(std::string const& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    return cvt.from_bytes(str);
}

}
