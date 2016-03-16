// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the string manipulation function interfaces
/// \ingroup string

#pragma once

#include <string>

namespace blip {

/// \addtogroup string
/// \{

/// \brief Converts a wide-character string to a UTF-8 string
/// \param str string to convert
/// \return \p str in UTF-8
std::string narrow(std::wstring const& str);

/// \brief Converts a UTF-8 string to a wide-character string
/// \param str string to convert
/// \return \p str in wide-character
std::wstring widen(std::string const& str);

/// \}

}
