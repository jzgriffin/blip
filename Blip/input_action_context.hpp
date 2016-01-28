// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_action_context structure interface
/// \ingroup input

#pragma once

#include "blip/input_action.hpp"
#include "blip/xml_converter.hpp"
#include <string>
#include <vector>

namespace blip {

/// \addtogroup input
/// \{

/// \brief Game-defined context of input actions
struct input_action_context
{
    /// \brief Name of the action context
    std::string name;

    /// \brief List of member actions
    std::vector<input_action> actions;

    /// \brief Gets an action from the context by name
    /// \param name name of the action
    /// \return reference to an action with the given name
    input_action const& at(std::string const& name) const;

    /// \brief Gets an action from the context by name
    /// \param name name of the action
    /// \return reference to an action with the given name
    input_action& at(std::string const& name);

    /// \brief Gets a value indicating whether the context contains an action
    /// with the given name
    /// \param name name of the action
    /// \return whether the context contains an action named \p name
    bool contains(std::string const& name) const;

    /// \brief Removes an action from the context by name
    /// \param name name of the action
    /// \return whether the action was removed
    bool erase(std::string const& name);

    /// \brief Finds an action in the context by name
    /// \param name name of the action
    /// \return iterator for the action
    auto find(std::string const& name) const
        -> decltype(actions)::const_iterator;

    /// \brief Finds an action in the context by name
    /// \param name name of the action
    /// \return iterator for the action
    auto find(std::string const& name)
        -> decltype(actions)::iterator;
};

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref input_action_context
template <>
struct xml_converter<input_action_context>
{
    /// \brief Deserializes a \ref input_action_context from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t action context to input
    /// \return whether the deserialization was successful
    static bool deserialize(xml_deserializer& dx, input_action_context& t);

    /// \brief Serializes a \ref input_action_context to a \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t action context to output
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, input_action_context const& t);
};

/// \}

}
