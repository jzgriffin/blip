// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_specification structure interface
/// \ingroup input

#pragma once

#include "blip/input_action_context.hpp"
#include "blip/xml_converter.hpp"
#include <string>
#include <vector>

namespace blip {

/// \addtogroup input
/// \{

/// \brief Game-defined specification of possible input contexts
struct input_specification
{
    /// \brief List of member action contexts
    std::vector<input_action_context> contexts;

    /// \brief Gets a context from the specification by name
    /// \param name name of the context
    /// \return reference to a context with the given name
    input_action_context const& at(std::string const& name) const;

    /// \brief Gets a context from the specification by name
    /// \param name name of the context
    /// \return reference to a context with the given name
    input_action_context& at(std::string const& name);

    /// \brief Gets a value indicating whether the specification contains a
    /// context with the given name
    /// \param name name of the context
    /// \return whether the specification contains a context named \p name
    bool contains(std::string const& name) const;

    /// \brief Removes a context from the specification by name
    /// \param name name of the context
    /// \return whether the context was removed
    bool erase(std::string const& name);

    /// \brief Finds a context in the specification by name
    /// \param name name of the context
    /// \return iterator for the context
    auto find(std::string const& name) const
        -> decltype(contexts)::const_iterator;

    /// \brief Finds a context in the specification by name
    /// \param name name of the context
    /// \return iterator for the context
    auto find(std::string const& name)
        -> decltype(contexts)::iterator;
};

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref input_specification
template <>
struct xml_converter<input_specification>
{
    /// \brief Deserializes a \ref input_specification from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t specification to input
    /// \return whether the deserialization was successful
    static bool deserialize(xml_deserializer& dx, input_specification& t);

    /// \brief Serializes a \ref input_specification to a \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t specification to output
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, input_specification const& t);
};

/// \}

}
