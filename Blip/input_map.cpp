// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_map structure implementation
/// \ingroup input

#include "blip/input_map.hpp"
#include "blip/input_specification.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace blip {

input_binding_context const& input_map::at(
    input_action_context const* action_context,
    input_action const* action) const
{
    auto iter = find(action_context, action);
    if (iter == std::end(contexts)) {
        throw std::runtime_error{"context not found in map"};
    }
    return *iter;
}

input_binding_context& input_map::at(
    input_action_context const* action_context,
    input_action const* action)
{
    auto iter = find(action_context, action);
    if (iter == std::end(contexts)) {
        throw std::runtime_error{"context not found in map"};
    }
    return *iter;
}

bool input_map::contains(
    input_action_context const* action_context,
    input_action const* action) const
{
    return find(action_context, action) != std::end(contexts);
}

bool input_map::erase(
    input_action_context const* action_context,
    input_action const* action)
{
    auto iter = find(action_context, action);
    if (iter == std::end(contexts)) {
        return false;
    }
    contexts.erase(iter);
    return true;
}

auto input_map::find(
    input_action_context const* action_context,
    input_action const* action) const
    -> decltype(contexts)::const_iterator
{
    auto first = std::begin(contexts);
    auto last = std::end(contexts);
    auto pred = [action_context, action](auto& i)
    { return i.action_context == action_context && i.action == action; };
    return std::find_if(first, last, pred);
}

auto input_map::find(
    input_action_context const* action_context,
    input_action const* action)
    -> decltype(contexts)::iterator
{
    auto first = std::begin(contexts);
    auto last = std::end(contexts);
    auto pred = [action_context, action](auto& i)
    { return i.action_context == action_context && i.action == action; };
    return std::find_if(first, last, pred);
}

std::vector<input_event> input_map::map(sf::Event const& from) const
{
    std::vector<input_event> tos;
    for (auto&& context : contexts) {
        for (auto&& binding : context.bindings) {
            input_event to;
            if (binding.map(from, to)) {
                to.context = context.action_context;
                to.action = context.action;
                to.binding = &binding;
                tos.emplace_back(std::move(to));
            }
        }
    }
    return tos;
}

std::vector<input_event> input_map::map(
    sf::Event const& from,
    input_action_context const* action_context) const
{
    std::vector<input_event> tos;
    for (auto&& context : contexts) {
        if (context.action_context != action_context) {
            continue;
        }
        for (auto&& binding : context.bindings) {
            input_event to;
            if (binding.map(from, to)) {
                to.context = context.action_context;
                to.action = context.action;
                to.binding = &binding;
                tos.emplace_back(std::move(to));
            }
        }
    }
    return tos;
}

bool xml_converter<input_map>::deserialize(
    xml_deserializer& dx,
    input_map& t,
    input_specification const& spec)
{
    for (auto&& child : dx.node.children("BindingContext")) {
        input_binding_context context;
        if (!dx.child(child, context, spec)) {
            return false;
        }
        t.contexts.emplace_back(std::move(context));
    }
    return true;
}

bool xml_converter<input_map>::serialize(
    xml_serializer& sx,
    input_map const& t)
{
    for (auto&& context : t.contexts) {
        sx.child("BindingContext", context);
    }
    return true;
}

}
