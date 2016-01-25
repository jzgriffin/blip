// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the path manipulation function interfaces
/// \ingroup path

#pragma once

#include <string>
#include <vector>

namespace blip {

/// \addtogroup path
/// \{

/// \brief Findable system path names
enum class system_path
{
    resources_path, //!< Application resources path
    preferences_path, //!< System preferences path
};

/// \brief Native path separator for this platform
extern char const native_path_separator;

/// \brief Possible path separators for this platform
extern char const* path_separators;

/// \brief Determines whether the given character is a path separator
/// \param c character
/// \return whether \p c is a path separator
bool is_path_separator(char c);

/// \brief Trims a path of its leading separators
/// \param path path to trim
/// \return \p path without its leading separators
/// \see is_path_separator
/// \see trim_path_after
/// \see trim_path
std::string trim_path_before(std::string path);

/// \brief Trims a path of its trailing separators
/// \param path path to trim
/// \return \p path without its trailing separators
/// \see is_path_separator
/// \see trim_path_before
/// \see trim_path
std::string trim_path_after(std::string path);

/// \brief Trims a path of its leading and trailing separators
/// \param path path to trim
/// \return \p path without its leading and trailing separators
/// \see is_path_separator
/// \see trim_path_before
/// \see trim_path_after
std::string trim_path(std::string path);

/// \brief Joins a collection of parts into a complete path
/// \param parts parts to join
/// \return joined paths from \p parts
/// \see split_path
std::string join_path(std::vector<std::string> const& parts);

/// \brief Splits a path into its individual parts
/// \param path path to split
/// \return parts of \p path
/// \see join_path
std::vector<std::string> split_path(std::string const& path);

/// \brief Gets a path from the system
/// \param sys_path name of the system path
/// \return system path
std::string find_system_path(system_path sys_path);

/// \brief Creates the given directory and its intermediates
/// \param path path to the directory
/// \return whether the directory was created or already existed
bool create_directory(std::string const& path);

/// \}

}
