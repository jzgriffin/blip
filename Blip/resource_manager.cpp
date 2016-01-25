// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::resource_manager class implementation

#include "blip/resource_manager.hpp"
#include "blip/path.hpp"
#include <iterator>

namespace blip {

std::string resource_manager::path_to(std::string const& path) const
{
    return join_path({base_path, path});
}

void resource_manager::sweep()
{
    for (auto&& pair : _caches) {
        pair.second->sweep();
    }
}

bool resource_manager::has_cache(std::type_index const& type) const
{
    return _caches.find(type) != std::end(_caches);
}

bool resource_manager::add_cache(pair_type&& pair)
{
    return _caches.emplace(std::move(pair)).second;
}

bool resource_manager::remove_cache(std::type_index const& type)
{
    auto iter = _caches.find(type);
    if (iter == std::end(_caches)) {
        return false;
    }
    _caches.erase(iter);
    return true;
}

resource_cache* resource_manager::cache_for(std::type_index const& type)
    const
{
    auto iter = _caches.find(type);
    if (iter == std::end(_caches)) {
        return nullptr;
    }
    return iter->second.get();
}

}
