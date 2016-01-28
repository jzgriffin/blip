// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_specification structure
/// implementation
/// \ingroup input

#include "blip/input_specification.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace blip {

input_action_context const& input_specification::at(std::string const& n)
    const
{
    auto iter = find(n);
    if (iter == std::end(contexts)) {
        throw std::runtime_error{"context not found in specification"};
    }
    return *iter;
}

input_action_context& input_specification::at(std::string const& n)
{
    auto iter = find(n);
    if (iter == std::end(contexts)) {
        throw std::runtime_error{"context not found in specification"};
    }
    return *iter;
}

bool input_specification::contains(std::string const& n) const
{
    return find(n) != std::end(contexts);
}

bool input_specification::erase(std::string const& n)
{
    auto iter = find(n);
    if (iter == std::end(contexts)) {
        return false;
    }
    contexts.erase(iter);
    return true;
}

auto input_specification::find(std::string const& n) const
    -> decltype(contexts)::const_iterator
{
    auto first = std::begin(contexts);
    auto last = std::end(contexts);
    auto pred = [&n](auto& i) { return i.name == n; };
    return std::find_if(first, last, pred);
}

auto input_specification::find(std::string const& n)
    -> decltype(contexts)::iterator
{
    auto first = std::begin(contexts);
    auto last = std::end(contexts);
    auto pred = [&n](auto& i) { return i.name == n; };
    return std::find_if(first, last, pred);
}

bool xml_converter<input_specification>::deserialize(
    xml_deserializer& dx,
    input_specification& t)
{
    for (auto&& child : dx.node.children("ActionContext")) {
        input_action_context context;
        if (!dx.child(child, context)) {
            return false;
        }
        t.contexts.emplace_back(std::move(context));
    }
    return true;
}

bool xml_converter<input_specification>::serialize(
    xml_serializer& sx,
    input_specification const& t)
{
    for (auto&& context : t.contexts) {
        sx.child("ActionContext", context);
    }
    return true;
}

}
