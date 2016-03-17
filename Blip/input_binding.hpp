// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_binding structure family interfaces
/// \ingroup input

#pragma once

#include "blip/input_activation.hpp"
#include "blip/input_signal.hpp"
#include "blip/xml_converter.hpp"
#include <iosfwd>

namespace sf {

// Forward declarations
class Event;

}

namespace blip {

// Forward declarations
struct input_event;

/// \addtogroup input
/// \{

/// \brief Possible types of input devices
enum class input_device
{
    controller, //!< Game controller device
    keyboard, //!< Keyboard device
};

/// \brief Possible types of controller controls
enum class input_controller_control
{
    axis, //!< Axis control (trigger, stick, etc.)
    button, //!< Button control (button, bumper, etc.)
};

/// \brief Input binding for a controller axis
struct input_controller_axis_binding
{
    /// \brief The identifying code for the axis
    unsigned code;

    /// \brief Activation parameters for the axis
    input_analog_activation activation;

    /// \brief Gets the type of signal produced by this binding
    /// \return type of signal
    input_signal signal() const noexcept;

    /// \brief Attempts to map from an SFML event to an input event through
    /// this binding
    /// \param from source SFML event
    /// \param to target input event
    /// \return whether the event was mappable through this binding
    bool map(sf::Event const& from, input_event& to) const;
};

/// \brief Input binding for a controller button
struct input_controller_button_binding
{
    /// \brief The identifying code for the button
    unsigned code;

    /// \brief Gets the type of signal produced by this binding
    /// \return type of signal
    input_signal signal() const noexcept;

    /// \brief Attempts to map from an SFML event to an input event through
    /// this binding
    /// \param from source SFML event
    /// \param to target input event
    /// \return whether the event was mappable through this binding
    bool map(sf::Event const& from, input_event& to) const;
};

/// \brief Input binding for a controller control
struct input_controller_binding
{
    /// \brief The type of control that is bound
    input_controller_control control;

    // Control bindings
    union
    {
        /// \brief The axis control binding
        input_controller_axis_binding axis;

        /// \brief The button control binding
        input_controller_button_binding button;
    };

    /// \brief Gets the type of signal produced by this binding
    /// \return type of signal
    input_signal signal() const noexcept;

    /// \brief Attempts to map from an SFML event to an input event through
    /// this binding
    /// \param from source SFML event
    /// \param to target input event
    /// \return whether the event was mappable through this binding
    bool map(sf::Event const& from, input_event& to) const;
};

/// \brief Input binding for a keyboard button
struct input_keyboard_binding
{
    /// \brief The identifying code for the button
    unsigned code;

    /// \brief Gets the type of signal produced by this binding
    /// \return type of signal
    input_signal signal() const noexcept;

    /// \brief Attempts to map from an SFML event to an input event through
    /// this binding
    /// \param from source SFML event
    /// \param to target input event
    /// \return whether the event was mappable through this binding
    bool map(sf::Event const& from, input_event& to) const;
};

/// \brief Input binding for an event-generating device
struct input_binding
{
    /// \brief The type of device that is bound
    input_device device;

    // Device bindings
    union
    {
        /// \brief The controller device binding
        input_controller_binding controller;

        /// \brief The keyboard device binding
        input_keyboard_binding keyboard;
    };

    /// \brief Gets the type of signal produced by this binding
    /// \return type of signal
    input_signal signal() const noexcept;

    /// \brief Attempts to map from an SFML event to an input event through
    /// this binding
    /// \param from source SFML event
    /// \param to target input event
    /// \return whether the event was mappable through this binding
    bool map(sf::Event const& from, input_event& to) const;
};

/// \brief Inputs an \ref input_device from a \ref std::istream
/// \param is stream to input from
/// \param rhs value to input
/// \return \p is
std::istream& operator>>(std::istream& is, input_device& rhs);

/// \brief Ouputs an \ref input_device to a \ref std::ostream
/// \param os stream to output to
/// \param rhs value to output
/// \return \p os
std::ostream& operator<<(std::ostream& os, input_device rhs);

/// \brief Inputs an \ref input_controller_control from a \ref std::istream
/// \param is stream to input from
/// \param rhs value to input
/// \return \p is
std::istream& operator>>(std::istream& is, input_controller_control& rhs);

/// \brief Ouputs an \ref input_controller_control to a \ref std::ostream
/// \param os stream to output to
/// \param rhs value to output
/// \return \p os
std::ostream& operator<<(std::ostream& os, input_controller_control rhs);

/// \}

/// \addtogroup xml
/// \{

/// \brief Specifies XML conversion functions for
/// \ref input_controller_axis_binding
template <>
struct xml_converter<input_controller_axis_binding>
{
    /// \brief Deserializes a \ref input_controller_axis_binding from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t binding to input
    /// \return whether the deserialization was successful
    static bool deserialize(
        xml_deserializer& dx,
        input_controller_axis_binding& t);

    /// \brief Serializes a \ref input_controller_axis_binding to a
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t binding to output
    /// \return whether the serialization was successful
    static bool serialize(
        xml_serializer& sx,
        input_controller_axis_binding const& t);
};

/// \brief Specifies XML conversion functions for
/// \ref input_controller_button_binding
template <>
struct xml_converter<input_controller_button_binding>
{
    /// \brief Deserializes a \ref input_controller_button_binding from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t binding to input
    /// \return whether the deserialization was successful
    static bool deserialize(
        xml_deserializer& dx,
        input_controller_button_binding& t);

    /// \brief Serializes a \ref input_controller_button_binding to a
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t binding to output
    /// \return whether the serialization was successful
    static bool serialize(
        xml_serializer& sx,
        input_controller_button_binding const& t);
};

/// \brief Specifies XML conversion functions for
/// \ref input_controller_binding
template <>
struct xml_converter<input_controller_binding>
{
    /// \brief Deserializes a \ref input_controller_binding from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t binding to input
    /// \return whether the deserialization was successful
    static bool deserialize(
        xml_deserializer& dx,
        input_controller_binding& t);

    /// \brief Serializes a \ref input_controller_binding to a
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t binding to output
    /// \return whether the serialization was successful
    static bool serialize(
        xml_serializer& sx,
        input_controller_binding const& t);
};

/// \brief Specifies XML conversion functions for
/// \ref input_keyboard_binding
template <>
struct xml_converter<input_keyboard_binding>
{
    /// \brief Deserializes a \ref input_keyboard_binding from a
    /// \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t binding to input
    /// \return whether the deserialization was successful
    static bool deserialize(
        xml_deserializer& dx,
        input_keyboard_binding& t);

    /// \brief Serializes a \ref input_keyboard_binding to a
    /// \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t binding to output
    /// \return whether the serialization was successful
    static bool serialize(
        xml_serializer& sx,
        input_keyboard_binding const& t);
};

/// \brief Specifies XML conversion functions for \ref input_binding
template <>
struct xml_converter<input_binding>
{
    /// \brief Deserializes a \ref input_binding from a \ref xml_deserializer
    /// \param dx deserializer to input from
    /// \param t binding to input
    /// \return whether the deserialization was successful
    static bool deserialize(xml_deserializer& dx, input_binding& t);

    /// \brief Serializes a \ref input_binding to a \ref xml_serializer
    /// \param sx serializer to output to
    /// \param t binding to output
    /// \return whether the serialization was successful
    static bool serialize(xml_serializer& sx, input_binding const& t);
};

/// \}

}
