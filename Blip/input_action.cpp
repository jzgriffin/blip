// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::input_action structure implementation
/// \ingroup input

#include "blip/input_action.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"

namespace blip {

bool xml_converter<input_action>::deserialize(
    xml_deserializer& dx,
    input_action& t)
{
    if (!dx.attribute("Name", t.name)) {
        return false;
    }
    if (!dx.attribute("Signal", t.signal)) {
        return false;
    }
    return true;
}

bool xml_converter<input_action>::serialize(
    xml_serializer& sx,
    input_action const& t)
{
    sx.attribute("Name", t.name);
    sx.attribute("Signal", t.signal);
    return true;
}

}
