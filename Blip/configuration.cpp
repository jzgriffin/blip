// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::configuration structure implementation
/// \ingroup application

#include "blip/configuration.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <SFML/Window/VideoMode.hpp>

namespace blip {

configuration::configuration()
{
    auto video_mode = sf::VideoMode::getDesktopMode();
    width = video_mode.width;
    height = video_mode.height;
    depth = video_mode.bitsPerPixel;
}

bool xml_converter<configuration>::deserialize(
    xml_deserializer& dx,
    configuration& t)
{
    dx.data("Width", t.width);
    dx.data("Height", t.height);
    dx.data("Depth", t.depth);
    dx.data("AntialiasingLevel", t.antialiasing_level);
    dx.data("IsFullScreen", t.is_full_screen);
    dx.data("UseVerticalSync", t.use_vertical_sync);
    return true;
}

bool xml_converter<configuration>::serialize(
    blip::xml_serializer& sx,
    blip::configuration const& t)
{
    sx.data("Width", t.width);
    sx.data("Height", t.height);
    sx.data("Depth", t.depth);
    sx.data("AntialiasingLevel", t.antialiasing_level);
    sx.data("IsFullScreen", t.is_full_screen);
    sx.data("UseVerticalSync", t.use_vertical_sync);
    return true;
}

}
