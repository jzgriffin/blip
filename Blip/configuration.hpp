// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::configuration structure interface
/// \ingroup application

#pragma once

#include "blip/xml_converter.hpp"

namespace blip {

/// \addtogroup application
/// \{

/// \brief Contains the user-configurable options for the \ref application
struct configuration
{
    unsigned width; //!< Width of the render window
    unsigned height; //!< Height of the render window
    unsigned depth; //!< Depth of the render window in bits per pixel
    unsigned antialiasing_level{0}; //!< Antialiasing level of the renderer
    bool is_full_screen{true}; //!< Whether the render window is full screen
    bool use_vertical_sync{false}; //!< Whether the renderer uses vsync

    /// \brief Initializes a new instance of the \ref configuration structure
    configuration();
};

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for \ref configuration
template <>
struct xml_converter<configuration>
{
    /// \brief Deserializes from a \ref xml_deserializer to a
    /// \ref configuration instance
    /// \param dx deserializer to input from
    /// \param t configuration to input to
    /// \return whether the deserialization was successful
    static bool deserialize(xml_deserializer& dx, configuration& t);

    /// \brief Serializes from a \ref configuration instance to a \ref
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t configuration to output from
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, configuration const& t);
};

/// \}

}
