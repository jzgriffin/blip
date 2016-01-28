// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_binding structure family
/// implementations
/// \ingroup input

#include "blip/input_binding.hpp"
#include "blip/input_event.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <SFML/Window/Event.hpp>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace {

/// \brief Mapping between \ref blip::input_device values and their names
constexpr std::pair<blip::input_device, char const*>
input_device_names[] =
{
    {blip::input_device::controller, "Controller"},
    {blip::input_device::keyboard, "Keyboard"},
};

/// \brief Mapping between \ref blip::input_controller_control values and
/// their names
constexpr std::pair<blip::input_controller_control, char const*>
input_controller_control_names[] =
{
    {blip::input_controller_control::axis, "Axis"},
    {blip::input_controller_control::button, "Button"},
};

}

namespace blip {

input_signal input_controller_axis_binding::signal() const noexcept
{
    return activation.signal();
}

bool input_controller_axis_binding::map(
    sf::Event const& from,
    input_event& to) const
{
    if (from.type != sf::Event::JoystickMoved) {
        return false;
    }
    if (static_cast<decltype(code)>(from.joystickMove.axis) != code) {
        return false;
    }
    activation.apply(from.joystickMove.position / 100.0f, to);
    return true;
}

input_signal input_controller_button_binding::signal() const noexcept
{
    return input_signal::digital;
}

bool input_controller_button_binding::map(
    sf::Event const& from,
    input_event& to) const
{
    switch (from.type) {
        case sf::Event::JoystickButtonPressed:
            to.value.digital = true;
            break;

        case sf::Event::JoystickButtonReleased:
            to.value.digital = false;
            break;

        default:
            return false;
    }
    if (static_cast<decltype(code)>(from.joystickButton.button) != code) {
        return false;
    }
    return true;
}

input_signal input_controller_binding::signal() const noexcept
{
    switch (control) {
        case input_controller_control::axis:
            return axis.signal();

        case input_controller_control::button:
            return button.signal();
    }
}

bool input_controller_binding::map(sf::Event const& from, input_event& to)
    const
{
    switch (control) {
        case input_controller_control::axis:
            return axis.map(from, to);

        case input_controller_control::button:
            return button.map(from, to);
    }
}

input_signal input_keyboard_binding::signal() const noexcept
{
    return input_signal::digital;
}

bool input_keyboard_binding::map(sf::Event const& from, input_event& to)
    const
{
    switch (from.type) {
        case sf::Event::KeyPressed:
            to.value.digital = true;
            break;

        case sf::Event::KeyReleased:
            to.value.digital = false;
            break;

        default:
            return false;
    }
    if (static_cast<decltype(code)>(from.key.code) != code) {
        return false;
    }
    return true;
}

input_signal input_binding::signal() const noexcept
{
    switch (device) {
        case input_device::controller:
            return controller.signal();

        case input_device::keyboard:
            return keyboard.signal();
    }
}

bool input_binding::map(sf::Event const& from, input_event& to) const
{
    switch (device) {
        case input_device::controller:
            return controller.map(from, to);

        case input_device::keyboard:
            return keyboard.map(from, to);
    }
}

std::istream& operator>>(std::istream& is, input_device& rhs)
{
    std::istream::sentry sentry{is};
    if (!sentry) {
        return is;
    }

    std::string word;
    is >> word;
    if (!is) {
        return is;
    }

    for (auto&& pair : input_device_names) {
        if (word == pair.second) {
            rhs = pair.first;
            return is;
        }
    }

    is.setstate(std::ios_base::failbit);
    return is;
}

std::ostream& operator<<(std::ostream& os, input_device rhs)
{
    std::ostream::sentry sentry{os};
    if (!sentry) {
        return os;
    }

    for (auto&& pair : input_device_names) {
        if (rhs == pair.first) {
            return os << pair.second;
        }
    }

    throw std::logic_error{"unmapped input_device"};
    return os;
}

std::istream& operator>>(std::istream& is, input_controller_control& rhs)
{
    std::istream::sentry sentry{is};
    if (!sentry) {
        return is;
    }

    std::string word;
    is >> word;
    if (!is) {
        return is;
    }

    for (auto&& pair : input_controller_control_names) {
        if (word == pair.second) {
            rhs = pair.first;
            return is;
        }
    }

    is.setstate(std::ios_base::failbit);
    return is;
}

std::ostream& operator<<(std::ostream& os, input_controller_control rhs)
{
    std::ostream::sentry sentry{os};
    if (!sentry) {
        return os;
    }

    for (auto&& pair : input_controller_control_names) {
        if (rhs == pair.first) {
            return os << pair.second;
        }
    }

    throw std::logic_error{"unmapped input_controller_control"};
    return os;
}

bool xml_converter<input_controller_axis_binding>::deserialize(
    xml_deserializer& dx,
    input_controller_axis_binding& t)
{
    if (!dx.attribute("Code", t.code)) {
        return false;
    }
    auto child = dx.child("Activation");
    if (child) {
        if (!dx.child(child.node, t.activation)) {
            return false;
        }
    }
    else {
        t.activation.condition = input_analog_activation_condition::none;
    }
    return true;
}

bool xml_converter<input_controller_axis_binding>::serialize(
    xml_serializer& sx,
    input_controller_axis_binding const& t)
{
    sx.attribute("Code", t.code);
    if (t.activation.condition != input_analog_activation_condition::none) {
        sx.child("Activation", t.activation);
    }
    return true;
}

bool xml_converter<input_controller_button_binding>::deserialize(
    xml_deserializer& dx,
    input_controller_button_binding& t)
{
    if (!dx.attribute("Code", t.code)) {
        return false;
    }
    return true;
}

bool xml_converter<input_controller_button_binding>::serialize(
    xml_serializer& sx,
    input_controller_button_binding const& t)
{
    sx.attribute("Code", t.code);
    return true;
}

bool xml_converter<input_controller_binding>::deserialize(
    xml_deserializer& dx,
    input_controller_binding& t)
{
    if (!dx.attribute("Control", t.control)) {
        return false;
    }
    switch (t.control) {
        case input_controller_control::axis:
            return xml_converter<input_controller_axis_binding>::deserialize(
                dx,
                t.axis);

        case input_controller_control::button:
            return
                xml_converter<input_controller_button_binding>::deserialize(
                    dx,
                    t.button);
    }
}

bool xml_converter<input_controller_binding>::serialize(
    xml_serializer& sx,
    input_controller_binding const& t)
{
    sx.attribute("Control", t.control);
    switch (t.control) {
        case input_controller_control::axis:
            return xml_converter<input_controller_axis_binding>::serialize(
                sx,
                t.axis);

        case input_controller_control::button:
            return xml_converter<input_controller_button_binding>::serialize(
                sx,
                t.button);
    }
}

bool xml_converter<input_keyboard_binding>::deserialize(
    xml_deserializer& dx,
    input_keyboard_binding& t)
{
    if (!dx.attribute("Code", t.code)) {
        return false;
    }
    return true;
}

bool xml_converter<input_keyboard_binding>::serialize(
    xml_serializer& sx,
    input_keyboard_binding const& t)
{
    sx.attribute("Code", t.code);
    return true;
}

bool xml_converter<input_binding>::deserialize(
    xml_deserializer& dx,
    input_binding& t)
{
    if (!dx.attribute("Device", t.device)) {
        return false;
    }
    switch (t.device) {
        case input_device::controller:
            return xml_converter<input_controller_binding>::deserialize(
                dx,
                t.controller);

        case input_device::keyboard:
            return xml_converter<input_keyboard_binding>::deserialize(
                dx,
                t.keyboard);
    }
}

bool xml_converter<input_binding>::serialize(
    xml_serializer& sx,
    input_binding const& t)
{
    sx.attribute("Device", t.device);
    switch (t.device) {
        case input_device::controller:
            return xml_converter<input_controller_binding>::serialize(
                sx,
                t.controller);

        case input_device::keyboard:
            return xml_converter<input_keyboard_binding>::serialize(
                sx,
                t.keyboard);
    }
}

}
