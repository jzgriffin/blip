// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::application class implementation

#include "blip/application.hpp"

namespace blip {

void application::exit(int exit_code) noexcept
{
    _is_running = false;
    _exit_code = exit_code;
}

int application::run()
{
    _is_running = true;
    while (_is_running) {
    }
    return _exit_code;
}

}
