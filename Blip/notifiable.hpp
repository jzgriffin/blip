// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::notifiable class interface
/// \ingroup virtual

#pragma once

namespace sf {

// Forward declarations
struct Event;

}

namespace blip {

/// \addtogroup virtual
/// \{

/// \brief Interface implemented by types that can be notified of an event
class notifiable
{
public:
    /// \brief Destructs the \ref notifiable instance
    virtual ~notifiable();

    /// \brief Notifies the object of an event
    /// \param event event to notify of
    /// \return whether or not the event was intercepted
    virtual bool notify(sf::Event const& event) = 0;
};

/// \}

}
