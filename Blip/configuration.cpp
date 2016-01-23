// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::configuration structure implementation

#include "blip/configuration.hpp"
#include <SFML/Window/VideoMode.hpp>

namespace blip {

configuration::configuration()
{
    auto video_mode = sf::VideoMode::getDesktopMode();
    width = video_mode.width;
    height = video_mode.height;
    depth = video_mode.bitsPerPixel;
}

}
