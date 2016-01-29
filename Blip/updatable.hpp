// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::updatable class interface
/// \ingroup virtual

#pragma once

namespace blip {

/// \addtogroup virtual
/// \{

/// \brief Interface implemented by types that can updated with time
class updatable
{
public:
    /// \brief Destructs the \ref updatable instance
    virtual ~updatable();

    /// \brief Updates the object state by a time step
    /// \param time_step time step to update by
    virtual void update(float time_step) = 0;
};

/// \}

}
