// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the iterator utility function interfaces
/// \ingroup iterator

#pragma once

#include <iterator>

namespace blip {

/// \addtogroup iterator
/// \{

/// \brief Wrapper for iterating a container in reverse
/// \tparam T container type
template <typename T>
struct reversion_wrapper
{
    /// \brief Container to iterate in reverse
    T& iterable;
};

/// \brief Obtains an iterator to the beginning of the given container
/// reversion wrapper
/// \tparam T container type
/// \param c container reversion wrapper
/// \return iterator to the beginning of \p c
template <typename T>
auto begin(reversion_wrapper<T> c)
{
    return std::rbegin(c.iterable);
}

/// \brief Obtains an iterator to the end of the given container reversion
/// wrapper
/// \tparam T container type
/// \param c container reversion wrapper
/// \return iterator to the end of \p c
template <typename T>
auto end(reversion_wrapper<T> c)
{
    return std::rend(c.iterable);
}

/// \brief Obtains a reversion wrapper for a container
/// \tparam T container type
/// \param iterable container to wrap
/// \return reversion wrapper for \p c
template <typename T>
reversion_wrapper<T> reverse(T&& iterable)
{
    return {iterable};
}

/// \}

}
