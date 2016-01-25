// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::application class interface
/// \ingroup application

#pragma once

#include "blip/configuration.hpp"
#include "blip/resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace blip {

/// \addtogroup application
/// \{

/// \brief Encapsulates the application
class application
{
public:
    static constexpr char const* company = "Xettex"; //!< Company name
    static constexpr char const* product = "Blip"; //!< Product name

    /// \brief Initializes a new instance of the \ref application class
    application();

    /// \brief Deleted copy constructor
    application(application const&) = delete;

    /// \brief Destructs the \ref application instance
    ~application();

    /// \brief Deleted copy assignment operator
    application& operator=(application const&) = delete;

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

    /// \brief Gets a reference to the resource manager
    /// \return resource manager
    resource_manager& resource_mgr() noexcept { return _resource_mgr; }

    /// \brief Gets a reference to the application configuration
    /// \return application configuration
    configuration& config() noexcept { return _config; }

    /// \brief Gets a reference to the rendering window
    /// \return rendering window
    sf::RenderWindow& window() noexcept { return _window; }

private:
    bool _is_running{false}; //!< Whether the application is running
    int _exit_code{0}; //!< Application exit status

    resource_manager _resource_mgr; //!< Resource manager
    std::string _config_path; //!< Application configuration file path
    configuration _config; //!< Application configuration

    sf::RenderWindow _window; //!< Rendering window

    /// \brief Notifies the application of an event
    /// \param event event to notify of
    void notify(sf::Event const& event);

    /// \brief Updates the application state by a time step
    /// \param time_step time step to update by
    void update(float time_step);

    /// \brief Draws the application scene
    void draw();
};

/// \}

}
