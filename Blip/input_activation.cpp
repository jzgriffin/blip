// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the input acitvation structure family implementations
/// \ingroup input

#include "blip/input_activation.hpp"
#include "blip/input_event.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace {

/// \brief Mapping between \ref blip::input_analog_activation_condition values
/// and their names
constexpr std::pair<blip::input_analog_activation_condition, char const*>
input_analog_activation_condition_names[] =
{
    {blip::input_analog_activation_condition::none, "None"},
    {blip::input_analog_activation_condition::equal, "Equal"},
    {blip::input_analog_activation_condition::not_equal, "NotEqual"},
    {blip::input_analog_activation_condition::less, "Less"},
    {blip::input_analog_activation_condition::less_equal, "LessEqual"},
    {blip::input_analog_activation_condition::greater, "Greater"},
    {blip::input_analog_activation_condition::greater_equal, "GreaterEqual"},
};

}

namespace blip {

input_signal input_analog_activation::signal() const noexcept
{
    if (condition == input_analog_activation_condition::none) {
        return input_signal::analog;
    }
    return input_signal::digital;
}

void input_analog_activation::apply(float value, input_event& event)
    const noexcept
{
    switch (condition) {
        case input_analog_activation_condition::none:
            event.value.analog = value;
            break;

        case input_analog_activation_condition::equal:
            event.value.digital = value == threshold;
            break;
            
        case input_analog_activation_condition::not_equal:
            event.value.digital = value != threshold;
            break;
            
        case input_analog_activation_condition::less:
            event.value.digital = value < threshold;
            break;
            
        case input_analog_activation_condition::less_equal:
            event.value.digital = value <= threshold;
            break;
            
        case input_analog_activation_condition::greater:
            event.value.digital = value > threshold;
            break;
            
        case input_analog_activation_condition::greater_equal:
            event.value.digital = value >= threshold;
            break;
    }
}

std::istream& operator>>(
    std::istream& is,
    input_analog_activation_condition& rhs)
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

    for (auto&& pair : input_analog_activation_condition_names) {
        if (word == pair.second) {
            rhs = pair.first;
            return is;
        }
    }

    is.setstate(std::ios_base::failbit);
    return is;
}

std::ostream& operator<<(
    std::ostream& os,
    input_analog_activation_condition rhs)
{
    std::ostream::sentry sentry{os};
    if (!sentry) {
        return os;
    }

    for (auto&& pair : input_analog_activation_condition_names) {
        if (rhs == pair.first) {
            return os << pair.second;
        }
    }

    throw std::logic_error{
        "unmapped input_analog_activation_condition_names"};
    return os;
}

bool xml_converter<input_analog_activation>::deserialize(
    xml_deserializer& dx,
    input_analog_activation& t)
{
    if (!dx.attribute("Condition", t.condition)) {
        return false;
    }
    if (t.condition != input_analog_activation_condition::none) {
        if (!dx.attribute("Threshold", t.threshold)) {
            return false;
        }
    }
    return true;
}

bool xml_converter<input_analog_activation>::serialize(
    xml_serializer& sx,
    input_analog_activation const& t)
{
    sx.attribute("Condition", t.condition);
    if (t.condition != input_analog_activation_condition::none) {
        sx.attribute("Threshold", t.threshold);
    }
    return true;
}

}
