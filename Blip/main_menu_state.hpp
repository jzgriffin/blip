// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::main_menu_state class interface
/// \ingroup state

#pragma once

#include "blip/state.hpp"

namespace blip {

// Forward declarations
class application;

/// \addtogroup state
/// \{

/// \brief State presented to the user upon launching the application
class main_menu_state final : public state
{
public:
    /// \brief Initializes a new instance of the \ref main_menu_state class
    /// for the given application
    /// \param a application running the state
    explicit main_menu_state(application& a);

    /// \brief Notifies the state of an event
    /// \param event event to notify of
    /// \return whether or not the event was intercepted
    bool notify(const sf::Event& event) override;

    /// \brief Updates the state by a time step
    /// \param time_step time step to update by
    void update(float time_step) override;

protected:
    /// \brief Draws the state to the given render target
    /// \param target render target to draw to
    /// \param states current render states
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
        override;

private:
    application& _app; //!< Application running the state
};

/// \}

}
