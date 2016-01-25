// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::resource_manager class interface

#pragma once

#include "resource_cache.hpp"
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <utility>

namespace blip {

/// \addtogroup resource
/// \{

/// \brief Manager for several \ref resource_cache instances
class resource_manager
{
public:
    /// \brief Type of keys for the cache mapping
    using key_type = std::type_index;

    /// \brief Type of unique pointer for caches
    using ptr_type = std::unique_ptr<resource_cache>;

    /// \brief Type of map for storing caches
    using map_type = std::map<key_type, ptr_type>;

    /// \brief Type of pairs mapping types and caches
    using pair_type = map_type::value_type;

    /// \brief Base resource path
    std::string base_path;

    /// \brief Initializes a new instance of the \ref resource_manager class
    /// with the given base path
    /// \param bp base resource path
    explicit resource_manager(std::string bp)
        : base_path{std::move(bp)}
    {
    }

    /// \brief Deleted copy constructor
    resource_manager(resource_manager const&) = delete;

    /// \brief Deleted copy assignment operator
    resource_manager& operator=(resource_manager const&) = delete;

    /// \brief Gets the path to a resource
    /// \param path resource path
    /// \return full resource path
    std::string path_to(std::string const& path) const;

    /// \brief Sweeps the caches, removing expired resources
    void sweep();

    /// \brief Gets a value indicating whether the manager contains a cache
    /// for the given resource type
    /// \param type type of resource
    //// \return whether the manager contains a matching cache
    bool has_cache(std::type_index const& type) const;

    /// \brief Adds a cache to the manager
    /// \param pair type-cache pair to add
    /// \return whether the cache was added
    bool add_cache(pair_type&& pair);

    /// \brief Removes a cache from the manager
    /// \param type type of resource
    /// \return whether the cache was removed
    bool remove_cache(std::type_index const& type);

    /// \brief Gets the cache for the given type
    /// \param type type of resource
    /// \return pointer to the cache
    resource_cache* cache_for(std::type_index const& type) const;

    /// \brief Gets a value indicating whether the manager contains a cache
    /// for the given resource type
    /// \tparam T type of resource
    //// \return whether the manager contains a matching cache
    template <typename T>
    bool has_cache() const
    {
        return has_cache(typeid(T));
    }

    /// \brief Adds a cache to the manager
    /// \tparam T type of resource
    /// \param ptr pointer to the cache
    /// \return whether the cache was added
    template <typename T>
    bool add_cache(std::unique_ptr<typed_resource_cache<T>>&& ptr)
    {
        return add_cache({typeid(T), std::move(ptr)});
    }

    /// \brief Removes a cache from the manager
    /// \tparam T type of resource
    /// \return whether the cache was removed
    template <typename T>
    bool remove_cache()
    {
        return remove_cache(typeid(T));
    }

    /// \brief Gets the cache for the given type
    /// \tparam T type of resource
    /// \return pointer to the cache
    template <typename T>
    typed_resource_cache<T>* cache_for() const
    {
        return dynamic_cast<typed_resource_cache<T>*>(cache_for(typeid(T)));
    }

    /// \brief Gets an existing resource from a cache by name
    /// \tparam T type of resource
    /// \param name name of the resource
    /// \return pointer to the resource
    template <typename T>
    typename typed_resource_cache<T>::ptr_type get(
        typename typed_resource_cache<T>::name_type const& name) const
    {
        auto cache = cache_for<T>();
        if (cache == nullptr) {
            return nullptr;
        }
        return cache->get(name);
    }

    /// \brief Gets a resource from a cache by name
    /// \tparam T type of resource
    /// \param name name of the resource
    /// \return pointer to the resource
    template <typename T>
    typename typed_resource_cache<T>::ptr_type get(
        typename typed_resource_cache<T>::name_type const& name)
    {
        auto cache = cache_for<T>();
        if (cache == nullptr) {
            return nullptr;
        }
        return cache->get(name);
    }

private:
    map_type _caches; //!< Cache container
};

/// \}

}
