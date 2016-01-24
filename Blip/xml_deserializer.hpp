// Blip
// Copyright (c) Xettex 2016

#pragma once

#include "blip/lexical_cast.hpp"
#include "blip/xml_converter.hpp"
#include <pugixml.hpp>
#include <utility>

/// \file
/// \brief Contains the \ref blip::xml_deserializer structure interface
/// \ingroup xml

namespace blip {
/// \addtogroup xml
/// \{

/// \brief Interface for deserializing from pugixml
struct xml_deserializer
{
    pugi::xml_node node; //!< Node to deserialize from

    /// \brief Gets a value indicating whether the deserializer has a node
    /// \return whether the deserializer has a node
    operator bool() const noexcept { return node; }

    /// \brief Gets a child from the node
    /// \param name name of the child
    /// \return deserializer for child
    xml_deserializer child(char const* name) const
    {
        return {node.child(name)};
    }

    /// \brief Gets a data child from the node
    /// \tparam T type of value
    /// \param ch child to deserialize
    /// \param val where to store the value
    /// \return whether the child was deserialized
    /// \see lexical_cast
    template <typename T>
    bool data(pugi::xml_node ch, T& val) const
    {
        return try_lexical_cast(ch.child_value(), val);
    }

    /// \brief Gets a data child from the node
    /// \tparam T type of value
    /// \param name name of the child
    /// \param val where to store the value
    /// \return whether the child was deserialized
    /// \see lexical_cast
    template <typename T>
    bool data(char const* name, T& val) const
    {
        return data(node.child(name), val);
    }

    /// \brief Gets an attribute from the node
    /// \tparam T type of value
    /// \param attr attribute to deserialize
    /// \param val where to store the value
    /// \return whether the attribute was deserialized
    /// \see lexical_cast
    template <typename T>
    bool attribute(pugi::xml_attribute attr, T& val) const
    {
        return try_lexical_cast(attr.value(), val);
    }

    /// \brief Gets an attribute from the node
    /// \tparam T type of value
    /// \param name name of the attribute
    /// \param val where to store the value
    /// \return whether the attribute was deserialized
    /// \see lexical_cast
    template <typename T>
    bool attribute(char const* name, T& val) const
    {
        return attribute(node.attribute(name), val);
    }

    /// \brief Gets a deserializable child from the node
    /// \tparam T type of value
    /// \tparam Converter type of converter to use
    /// \tparam Args types of additional arguments for converter
    /// \param ch child to deserialize
    /// \param val where to store the value
    /// \param args additional arguments for converter
    /// \return whether the child was deserialized
    /// \see xml_converter
    template <
        typename T,
        typename Converter = xml_converter<T>,
        typename... Args>
    bool child(pugi::xml_node ch, T& val, Args&... args)
    {
        xml_deserializer dx{ch};
        if (!dx) {
            return false;
        }
        return Converter::deserialize(dx, val, std::forward<Args>(args)...);
    }

    /// \brief Gets a deserializable child from the node
    /// \tparam T type of value
    /// \tparam Converter type of converter to use
    /// \tparam Args types of additional arguments for converter
    /// \param name name of the child
    /// \param val where to store the value
    /// \param args additional arguments for the converter
    /// \return whether the child was deserialized
    /// \see xml_converter
    template <
        typename T,
        typename Converter = xml_converter<T>,
        typename... Args>
    bool child(char const* name, T& val, Args&... args)
    {
        auto dx = child(name);
        if (!dx) {
            return false;
        }
        return Converter::deserialize(dx, val, std::forward<Args>(args)...);
    }
};

/// \}
}
