// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::state class implementation
/// \ingroup state

#include "blip/state.hpp"

namespace blip {

bool does_block_notify(state_type type)
{
    switch (type) {
    case state_type::primary:
    case state_type::overlay:
        return true;
    }
}

bool does_block_update(state_type type)
{
    switch (type) {
    case state_type::primary:
        return true;

    case state_type::overlay:
        return false;
    }
}

bool does_block_draw(state_type type)
{
    switch (type) {
    case state_type::primary:
        return true;

    case state_type::overlay:
        return false;
    }
}

void state::focus()
{
    if (!_is_focused) {
        focusing();
        _is_focused = true;
    }
}

void state::neglect()
{
    if (_is_focused) {
        neglecting();
        _is_focused = false;
    }
}

void state::enable()
{
    if (!_is_enabled) {
        enabling();
        _is_enabled = true;
    }
}

void state::disable()
{
    if (_is_enabled) {
        disabling();
        _is_enabled = false;
    }
}

void state::show()
{
    if (!_is_visible) {
        showing();
        _is_visible = true;
    }
}

void state::hide()
{
    if (_is_visible) {
        hiding();
        _is_visible = false;
    }
}

}
