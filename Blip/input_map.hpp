// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_specification structure interface
/// \ingroup input

#pragma once

#include "blip/input_binding_context.hpp"
#include "blip/input_event.hpp"
#include "blip/xml_converter.hpp"
#include <vector>

namespace sf {

// Forward declarations
struct Event;

}

namespace blip {

// Forward declarations
struct input_action_context;
struct input_action;
struct input_specification;

/// \addtogroup input
/// \{

/// \brief User-defined mapping between actions and bindings
struct input_map
{
    /// \brief List of member binding contexts
    std::vector<input_binding_context> contexts;

    /// \brief Gets a context from the map by action
    /// \param action_context action context of the context
    /// \param action action of the context
    /// \return reference to a context with the given parameters
    input_binding_context const& at(
        input_action_context const* action_context,
        input_action const* action) const;

    /// \brief Gets a context from the map by action
    /// \param action_context action context of the context
    /// \param action action of the context
    /// \return reference to a context with the given parameters
    input_binding_context& at(
        input_action_context const* action_context,
        input_action const* action);

    /// \brief Gets a value indicating whether the map contains a context with
    /// the given action
    /// \param action_context action context of the context
    /// \param action action of the context
    /// \return whether the map contains a context for \p action_context and
    /// \p action
    bool contains(
        input_action_context const* action_context,
        input_action const* action) const;

    /// \brief Removes a context from the specification by action
    /// \param action_context action context of the context
    /// \param action action of the context
    /// \return whether the context was removed
    bool erase(
        input_action_context const* action_context,
        input_action const* action);

    /// \brief Finds a context in the specification by action
    /// \param action_context action context of the context
    /// \param action action of the context
    /// \return iterator for the context
    auto find(
        input_action_context const* action_context,
        input_action const* action) const
        -> decltype(contexts)::const_iterator;

    /// \brief Finds a context in the specification by action
    /// \param action_context action context of the context
    /// \param action action of the context
    /// \return iterator for the context
    auto find(
        input_action_context const* action_context,
        input_action const* action)
        -> decltype(contexts)::iterator;

    /// \brief Attempts to map an SFML event using the bindings in the map
    /// \param from source SFML event
    /// \return list of mapped input events
    std::vector<input_event> map(sf::Event const& from) const;

    /// \brief Attempts to map an SFML event using the bindings in the map
    /// for the given action context
    /// \param from source SFML event
    /// \param action_context action context to map for
    /// \return list of mapped input events
    std::vector<input_event> map(
        sf::Event const& from,
        input_action_context const* action_context) const;
};

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref input_map
template <>
struct xml_converter<input_map>
{
    /// \brief Deserializes a \ref input_map from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t map to input
    /// \param spec input specification to pull action contexts from
    /// \return whether the deserialization was successful
    static bool deserialize(
        xml_deserializer& dx,
        input_map& t,
        input_specification const& spec);

    /// \brief Serializes a \ref input_map to a \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t map to output
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, input_map const& t);
};

/// \}

}
