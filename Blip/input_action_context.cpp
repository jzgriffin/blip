// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_action_context structure
/// implementation
/// \ingroup input

#include "blip/input_action_context.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace blip {

input_action const& input_action_context::at(std::string const& n) const
{
    auto iter = find(n);
    if (iter == std::end(actions)) {
        throw std::runtime_error{"action not found in context"};
    }
    return *iter;
}

input_action& input_action_context::at(std::string const& n)
{
    auto iter = find(n);
    if (iter == std::end(actions)) {
        throw std::runtime_error{"action not found in context"};
    }
    return *iter;
}

bool input_action_context::contains(std::string const& n) const
{
    return find(n) != std::end(actions);
}

bool input_action_context::erase(std::string const& n)
{
    auto iter = find(n);
    if (iter == std::end(actions)) {
        return false;
    }
    actions.erase(iter);
    return true;
}

auto input_action_context::find(std::string const& n) const
    -> decltype(actions)::const_iterator
{
    auto first = std::begin(actions);
    auto last = std::end(actions);
    auto pred = [&n](auto& i) { return i.name == n; };
    return std::find_if(first, last, pred);
}

auto input_action_context::find(std::string const& n)
    -> decltype(actions)::iterator
{
    auto first = std::begin(actions);
    auto last = std::end(actions);
    auto pred = [&n](auto& i) { return i.name == n; };
    return std::find_if(first, last, pred);
}

bool xml_converter<input_action_context>::deserialize(
    xml_deserializer& dx,
    input_action_context& t)
{
    if (!dx.attribute("Name", t.name)) {
        return false;
    }
    for (auto&& child : dx.node.children("Action")) {
        input_action action;
        if (!dx.child(child, action)) {
            return false;
        }
        t.actions.emplace_back(std::move(action));
    }
    return true;
}

bool xml_converter<input_action_context>::serialize(
    xml_serializer& sx,
    input_action_context const& t)
{
    sx.attribute("Name", t.name);
    for (auto&& action : t.actions) {
        sx.child("Action", action);
    }
    return true;
}

}
