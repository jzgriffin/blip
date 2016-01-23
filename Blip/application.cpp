// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::application class implementation

#include "blip/application.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace blip {

application::application()
{
    _window.create({1280, 720}, "Blip");
}

void application::exit(int exit_code) noexcept
{
    _is_running = false;
    _exit_code = exit_code;
}

int application::run()
{
    sf::Clock frame_clock;
    float time_step{0.0f};

    _is_running = true;
    while (_is_running) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            notify(event);
        }
        update(time_step);
        draw();

        time_step = frame_clock.restart().asSeconds();
    }
    return _exit_code;
}

void application::notify(sf::Event const& event)
{
    switch (event.type) {
        case sf::Event::Closed:
            exit();
            break;

        default:
            break;
    }
}

void application::update(float)
{
}

void application::draw()
{
    _window.clear();
    _window.display();
}

}
