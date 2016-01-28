// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_action structure interface
/// \ingroup input

#pragma once

#include "blip/input_signal.hpp"
#include "blip/xml_converter.hpp"
#include <string>

namespace blip {

/// \addtogroup input
/// \{

/// \brief Game-defined action that corresponds to some input event
struct input_action
{
    /// \brief Name of the action
    std::string name;

    /// \brief Signal required by the action
    input_signal signal;
};

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref input_action
template <>
struct xml_converter<input_action>
{
    /// \brief Deserializes a \ref input_action from a \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t action to input
    /// \return whether the deserialization was successful
    static bool deserialize(xml_deserializer& dx, input_action& t);

    /// \brief Serializes a \ref input_action to a \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t action to output
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, input_action const& t);
};

/// \}

}
