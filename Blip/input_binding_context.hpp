// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_binding_context structure interface
/// \ingroup input

#pragma once

#include "blip/input_binding.hpp"
#include "blip/xml_converter.hpp"
#include <vector>

namespace blip {

// Forward declarations
struct input_action_context;
struct input_action;
struct input_specification;

/// \addtogroup input
/// \{

/// \brief Context for attaching bindings to an action in an action context
struct input_binding_context
{
    /// \brief The action context the bindings are attached to
    input_action_context const* action_context;

    /// \brief The action the bindings are attached to
    input_action const* action;

    /// \brief List of member bindings
    std::vector<input_binding> bindings;
};

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref input_binding_context
template <>
struct xml_converter<input_binding_context>
{
    /// \brief Deserializes a \ref input_binding_context from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t action context to input
    /// \param spec input specification to pull action contexts from
    /// \return whether the deserialization was successful
    static bool deserialize(
        xml_deserializer& dx,
        input_binding_context& t,
        input_specification const& spec);

    /// \brief Serializes a \ref input_binding_context to a
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t action context to output
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, input_binding_context const& t);
};

/// \}

}
