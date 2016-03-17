// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_signal enumeration implementation
/// \ingroup input

#include "blip/input_signal.hpp"
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace {

/// \brief Mapping between \ref blip::input_signal values and their names
constexpr std::pair<blip::input_signal, char const*>
input_signal_names[] =
{
    {blip::input_signal::analog, "Analog"},
    {blip::input_signal::digital, "Digital"},
};

}

namespace blip {

std::istream& operator>>(std::istream& is, input_signal& rhs)
{
    std::istream::sentry sentry{is};
    if (!sentry) {
        return is;
    }

    std::string word;
    is >> word;
    if (!is) {
        return is;
    }

    for (auto&& pair : input_signal_names) {
        if (word == pair.second) {
            rhs = pair.first;
            return is;
        }
    }

    is.setstate(std::ios_base::failbit);
    return is;
}

std::ostream& operator<<(std::ostream& os, input_signal rhs)
{
    std::ostream::sentry sentry{os};
    if (!sentry) {
        return os;
    }

    for (auto&& pair : input_signal_names) {
        if (rhs == pair.first) {
            return os << pair.second;
        }
    }

    throw std::logic_error{"unmapped input_signal"};
}

}
