// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::configuration structure interface

#pragma once

namespace blip {

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

}
