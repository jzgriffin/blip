// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::application class interface

#pragma once

namespace blip {

/// \brief Encapsulates the application
class application
{
public:
    /// \brief Gets a value indicating whether the application is running
    /// \return whether the application is running
    bool is_running() const noexcept { return _is_running; }

    /// \brief Gets the application exit status
    /// \return application exit status
    int exit_code() const noexcept { return _exit_code; }

    /// \brief Exits the application
    /// \param exit_code application exit status
    void exit(int exit_code = 0) noexcept;

    /// \brief Runs the application
    /// \return application exit status
    int run();

private:
    bool _is_running{false}; //!< Whether the application is running
    int _exit_code{0}; //!< Application exit status
};

}
