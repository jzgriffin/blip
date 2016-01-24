// Blip
// Copyright (c) Xettex 2016

#pragma once

#include "blip/lexical_cast.hpp"
#include "blip/xml_converter.hpp"
#include <pugixml.hpp>
#include <utility>

/// \file
/// \brief Contains the \ref blip::xml_serializer structure interface
/// \ingroup xml

namespace blip {
/// \addtogroup xml
/// \{

/// \brief Interface for serializing to pugixml
struct xml_serializer
{
    pugi::xml_node node; //!< Node to serialize to

    /// \brief Gets a value indicating whether the serializer has a node
    /// \return whether the serializer has a node
    operator bool() const noexcept { return node; }

    /// \brief Appends a child to the node
    /// \param name name of the child
    /// \return serializer for child
    xml_serializer child(char const* name)
    {
        return {node.append_child(name)};
    }

    /// \brief Appends a data child to the node
    /// \tparam T type of value
    /// \param name name of the child
    /// \param val value to give the child
    /// \return whether the child was serialized
    /// \see lexical_cast
    template <typename T>
    bool data(char const* name, T const& val)
    {
        auto ch = node.append_child(name).append_child(pugi::node_cdata);
        if (!ch) {
            return false;
        }
        std::string str;
        if (!try_lexical_cast(val, str)) {
            return false;
        }
        ch.set_value(str.c_str());
        return true;
    }

    /// \brief Appends an attribute to the node
    /// \tparam T type of value
    /// \param name name of the attribute
    /// \param val value to give the attribute
    /// \return whether the attribute was serialized
    /// \see lexical_cast
    template <typename T>
    bool attribute(char const* name, T const& val)
    {
        auto attr = node.append_attribute(name);
        if (!attr) {
            return false;
        }
        std::string str;
        if (!try_lexical_cast(val, str)) {
            return false;
        }
        attr.set_value(str.c_str());
        return true;
    }

    /// \brief Appends a serializable value to the node
    /// \tparam T type of value
    /// \tparam Converter type of converter to use
    /// \tparam Args additional arguments for converter
    /// \param name name of the child
    /// \param val value to give the child
    /// \return whether the child was serialized
    /// \see xml_serializable
    template <
        typename T,
        typename Converter = xml_converter<T>,
        typename... Args>
    bool child(char const* name, T const& val, Args&... args)
    {
        auto sx = child(name);
        if (!sx) {
            return false;
        }
        return Converter::serialize(sx, val, std::forward<Args>(args)...);
    }
};

/// \}
}
