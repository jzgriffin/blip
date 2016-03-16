// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::state class interface
/// \ingroup state

#pragma once

#include "blip/notifiable.hpp"
#include "blip/updatable.hpp"
#include <SFML/Graphics/Drawable.hpp>

namespace blip {

/// \addtogroup state
/// \{

/// \brief Types of states supported by the state management system
enum class state_type
{
    primary, //!< Primary state, which blocks notify, update, and draw
    overlay, //!< Overlay state, which blocks notify
};

/// \brief Abstract base class for all states
class state : public notifiable, public updatable, public sf::Drawable
{
public:
    /// \brief Type of state, which determines its influence on other states
    const state_type type;

    /// \brief Destructs the \ref state instance
    virtual ~state() = default;

    /// \brief Gets a value indicating whether the state is focused and
    /// receiving notifications
    /// \return whether the state is focused
    /// \see focus
    /// \see neglect
    bool is_focused() const noexcept { return _is_focused; }

    /// \brief Focuses the state, allowing it to receive notifications
    /// \see is_focused
    /// \see neglect
    void focus();

    /// \brief Neglects the state, preventing it from receiving notifications
    /// \see is_focused
    /// \see focus
    void neglect();

    /// \brief Gets a value indicating whether the state is enabled and
    /// performing updates
    /// \return whether the state is enabled
    /// \see enable
    /// \see disable
    bool is_enabled() const noexcept { return _is_enabled; }

    /// \brief Enables the state, allowing it to perform updates
    /// \see is_enabled
    /// \see disable
    void enable();

    /// \brief Disables the state, preventing it from performing updates
    /// \see is_enabled
    /// \see enable
    void disable();

    /// \brief Gets a value indicating whether the state is visible and
    /// performing draws
    /// \return whether the state is visible
    /// \see show
    /// \see hide
    bool is_visible() const noexcept { return _is_visible; }

    /// \brief Shows the state, allowing it to perform draws
    /// \see is_visible
    /// \see hide
    void show();

    /// \brief Hides the state, preventing it from performing draws
    /// \see is_visible
    /// \see show
    void hide();

protected:
    /// \brief Initializes a new instance of the \ref state class with the
    /// given type
    /// \param t type of state
    explicit state(state_type t) : type{t} {}

    /// \brief Responds to the state becoming focused
    /// \see is_focused
    /// \see focus
    virtual void focusing() {}

    /// \brief Responds to the state becoming neglected
    /// \see is_focused
    /// \see neglect
    virtual void neglecting() {}

    /// \brief Responds to the state becoming enabled
    /// \see is_enabled
    /// \see enable
    virtual void enabling() {}

    /// \brief Responds to the state becoming disabled
    /// \see is_enabled
    /// \see disable
    virtual void disabling() {}

    /// \brief Responds to the state becoming shown
    /// \see is_visible
    /// \see show
    virtual void showing() {}

    /// \brief Responds to the state becoming hidden
    /// \see is_visible
    /// \see hide
    virtual void hiding() {}

private:
    bool _is_focused{false}; //!< Whether the state is focused
    bool _is_enabled{false}; //!< Whether the state is enabled
    bool _is_visible{false}; //!< Whether the state is visible
};

/// \brief Determines whether a state of the given type will block notify
/// \param type type of state
/// \return whether the type blocks notify
bool does_block_notify(state_type type);

/// \brief Determines whether a state of the given type will block update
/// \param type type of state
/// \return whether the type blocks update
bool does_block_update(state_type type);

/// \brief Determines whether a state of the given type will block draw
/// \param type type of state
/// \return whether the type blocks draw
bool does_block_draw(state_type type);

/// \}

}
