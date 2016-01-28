// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_binding_context structure
/// implementation
/// \ingroup input

#include "blip/input_binding_context.hpp"
#include "blip/input_action_context.hpp"
#include "blip/input_action.hpp"
#include "blip/input_specification.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace blip {

bool xml_converter<input_binding_context>::deserialize(
    xml_deserializer& dx,
    input_binding_context& t,
    input_specification const& spec)
{
    std::string action_context_name;
    if (!dx.attribute("ActionContext", action_context_name)) {
        return false;
    }
    auto action_context_iter = spec.find(action_context_name);
    if (action_context_iter == std::end(spec.contexts)) {
        return false;
    }
    t.action_context = &*action_context_iter;

    std::string action_name;
    if (!dx.attribute("Action", action_name)) {
        return false;
    }
    auto action_iter = t.action_context->find(action_name);
    if (action_iter == std::end(t.action_context->actions)) {
        return false;
    }
    t.action = &*action_iter;

    for (auto&& child : dx.node.children("Binding")) {
        input_binding binding;
        if (!dx.child(child, binding)) {
            return false;
        }
        t.bindings.emplace_back(std::move(binding));
    }
    return true;
}

bool xml_converter<input_binding_context>::serialize(
    xml_serializer& sx,
    input_binding_context const& t)
{
    sx.attribute("ActionContext", t.action_context->name);
    sx.attribute("Action", t.action->name);
    for (auto&& binding : t.bindings) {
        sx.child("Binding", binding);
    }
    return true;
}

}
