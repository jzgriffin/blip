// Blip
// Copyright (c) Xettex 2016

#pragma once

/// \file
/// \brief Contains the \ref blip::xml_converter structure interface
/// \ingroup xml

namespace blip {

// Forward declarations
struct xml_deserializer;
struct xml_serializer;

/// \addtogroup xml
/// \{

/// \brief Specialized by types that are XML-convertible
/// \see xml_deserializer
/// \see xml_serializer
///
/// Specializations must implement the following signatures:
/// \code
/// static bool deserialize(xml_deserializer& dx, T& t);
/// static bool serialize(xml_serializer& sx, T const& t);
/// \endcode
template <typename T>
struct xml_converter
{
};

/// \}
}
