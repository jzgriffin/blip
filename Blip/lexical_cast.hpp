// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::lexical_cast function family interface
/// \ingroup lexical_cast

#pragma once

#include <sstream>
#include <string>
#include <typeinfo>

namespace blip {

namespace detail {

/// \addtogroup lexical_cast
/// \{

/// \brief Attempts to lexically cast from a string to another type
/// \tparam To output value type
/// \param from string to cast from
/// \param to value to cast to
/// \return whether the cast was successful
template <typename To>
bool try_lexical_cast_to(std::string const& from, To& to)
{
    std::istringstream is{from};
    is >> to;
    return !is.fail();
}

/// \brief Attempts to lexically cast from an arbitrary type to a string
/// \tparam From input value type
/// \param from value to cast from
/// \param to string to cast to
/// \return whether the cast was successful
template <typename From>
bool try_lexical_cast_from(From const& from, std::string& to)
{
    std::ostringstream os;
    os << from;
    if (os.fail()) {
        return false;
    }
    to = os.str();
    return true;
}

/// \}

}

/// \addtogroup lexical_cast
/// \{

/// \brief Attempts to lexically cast from one type to another if both types
/// are the same
/// \tparam To input value type
/// \tparam From output value type
/// \param from value to cast from
/// \param to value to cast to
/// \return \p whether the cast was successful
template <typename To, typename From>
std::enable_if_t<std::is_same<From, To>::value, bool>
try_lexical_cast(From const& from, To& to)
{
    to = from;
    return true;
}

/// \brief Attempts to lexically cast from one type to another if the input
/// type is convertible to the output type
/// \tparam To input value type
/// \tparam From output value type
/// \param from value to cast from
/// \param to value to cast to
/// \return \p whether the cast was successful
template <typename To, typename From>
std::enable_if_t<
    !std::is_same<From, To>::value &&
    std::is_convertible<From, To>::value,
    bool>
try_lexical_cast(From const& from, To& to)
{
    to = std::forward<To>(from);
    return true;
}

/// \brief Attempts to lexically cast from one type to another
/// \tparam To input value type
/// \tparam From output value type
/// \param from value to cast from
/// \param to value to cast to
/// \return \p whether the cast was successful
template <typename To, typename From>
std::enable_if_t<
    !std::is_same<From, To>::value &&
    !std::is_convertible<From, To>::value,
    bool>
try_lexical_cast(From const& from, To& to)
{
    std::string str;
    return detail::try_lexical_cast_from(from, str) &&
        detail::try_lexical_cast_to(str, to);
}

/// \brief Lexically casts from one type to another
/// \tparam To input value type
/// \tparam From output value type
/// \param from value to cast from
/// \return casted value
/// \see try_lexical_cast
///
/// Throws \ref std::bad_cast if the cast is not successful.
template <typename To, typename From>
To lexical_cast(From const& from)
{
    To to;
    if (!try_lexical_cast<To, From>(from, to)) {
        throw std::bad_cast{};
    }
    return to;
}

/// \}

}
