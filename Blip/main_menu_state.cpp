// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::main_menu_state class implementation
/// \ingroup state

#include "blip/main_menu_state.hpp"
#include "blip/application.hpp"
#include <SFML/Window/Event.hpp>

namespace blip {

main_menu_state::main_menu_state(application& a)
    : state{state_type::primary}
    , _app{a}
{
}

bool main_menu_state::notify(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    _app.exit();
                    return true;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }

    return false;
}

void main_menu_state::update(float)
{
}

void main_menu_state::draw(sf::RenderTarget&, sf::RenderStates) const
{
}

}
