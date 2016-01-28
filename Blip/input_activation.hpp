// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the input acitvation structure family interfaces
/// \ingroup input

#pragma once

#include "blip/input_signal.hpp"
#include "blip/xml_converter.hpp"
#include <iosfwd>

namespace blip {

// Forward declarations
struct input_event;

/// \addtogroup input
/// \{

/// \brief Possible activation conditions for analog signals
enum class input_analog_activation_condition
{
    none, //!< No activation necessary; signal is analog
    equal, //!< Digital true if value is equal to threshold
    not_equal, //!< Digital true if value is not equal to threshold
    less, //!< Digital true if value is less than threshold
    less_equal, //!< Digital true if value is less or equal to threshold
    greater, //!< Digital true if value is greater than threshold
    greater_equal, //!< Digital true if value is greater or equal to thresold
};

/// \brief Activation parameters for an analog signal
struct input_analog_activation
{
    /// \brief The condition under which activation occurs
    input_analog_activation_condition condition;

    /// \brief The threshold at which digital activation occurs
    float threshold;

    /// \brief Gets the type of signal produced when the condition activates
    /// \return type of signal
    input_signal signal() const noexcept;

    /// \brief Applies the activation a signal value
    /// \param value signal value
    /// \param event event to store the result in
    void apply(float value, input_event& event) const noexcept;
};

/// \brief Inputs a \ref input_analog_activation_condition from a
/// \ref std::istream
/// \param is stream to input from
/// \param rhs value to input
/// \return \p is
std::istream& operator>>(
    std::istream& is,
    input_analog_activation_condition& rhs);

/// \brief Ouputs a \ref input_analog_activation_condition to a
/// \ref std::ostream
/// \param os stream to output to
/// \param rhs value to output
/// \return \p os
std::ostream& operator<<(
    std::ostream& os,
    input_analog_activation_condition rhs);

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref input_analog_activation
template <>
struct xml_converter<input_analog_activation>
{
    /// \brief Deserializes a \ref input_analog_activation from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t analog activation to input
    /// \return whether the deserialization was successful
    static bool deserialize(xml_deserializer& dx, input_analog_activation& t);

    /// \brief Serializes a \ref input_analog_activation to a
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t analog activation to output
    /// \return whether the serialization was successful
    static bool serialize(
        xml_serializer& sx,
        input_analog_activation const& t);
};

/// \}

}
