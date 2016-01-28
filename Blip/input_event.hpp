// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_event structure interface

#pragma once

namespace blip {

// Forward declarations
struct input_action_context;
struct input_action;
struct input_binding;

/// \brief Event generated during an action-binding interaction
struct input_event
{
    /// \brief Action context in which the action resides
    input_action_context const* context;

    /// \brief Action that was generated
    input_action const* action;

    /// \brief Binding that generated the event
    input_binding const* binding;

    /// \brief Value of the event
    union
    {
        /// \brief Analog value on [0,1]
        float analog;

        /// \brief Boolean digital value
        bool digital;
    } value;
};

}
