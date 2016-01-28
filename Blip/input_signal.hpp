// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_signal enumeration interface
/// \ingroup input

#pragma once

#include <iosfwd>

namespace blip {

/// \addtogroup input
/// \{

/// \brief Types of signals that can be consumed by input_action
enum class input_signal
{
    analog, //!< Analog signal with a continuous value
    digital, //!< Digital signal with a discrete boolean value
};

/// \brief Inputs a \ref input_signal from a \ref std::istream
/// \param is stream to input from
/// \param rhs value to input
/// \return \p is
std::istream& operator>>(std::istream& is, input_signal& rhs);

/// \brief Ouputs a \ref input_signal to a \ref std::ostream
/// \param os stream to output to
/// \param rhs value to output
/// \return \p os
std::ostream& operator<<(std::ostream& os, input_signal rhs);

/// \}

}
