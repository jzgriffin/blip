// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::resource_cache class interface
/// \ingroup resource

#pragma once

#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>

namespace blip {

/// \addtogroup resource
/// \{

/// \brief Interface class for all resource caches
class resource_cache
{
public:
    /// \brief Destructs the \ref resource_cache instance
    virtual ~resource_cache();

    /// \brief Sweeps the cache, removing expired resources
    virtual void sweep() = 0;
};

/// \brief Typed cache for resources
/// \tparam T type of resource
template <typename T>
class typed_resource_cache : public resource_cache
{
public:
    /// \brief Type of resource name used in this cache
    using name_type = std::string;

    /// \brief Type of resource stored in this cache
    using resource_type = T;

    /// \brief Type of shared pointer for resources in this cache
    using ptr_type = std::shared_ptr<T>;

    /// \brief type of resource creation function
    using creator_type = std::function<ptr_type(name_type const&)>;

    /// \brief Initializes a new instance of the \ref typed_resource_cache
    /// class with the given creator
    /// \param creator resource creation function
    explicit typed_resource_cache(creator_type creator)
        : _creator{std::move(creator)}
    {
    }

    /// \brief Deleted copy constructor
    typed_resource_cache(typed_resource_cache const&) = delete;

    /// \brief Destructs the \ref typed_resource_cache instance
    virtual ~typed_resource_cache() = default;

    /// \brief Deleted copy assignment operator
    typed_resource_cache& operator=(typed_resource_cache const&) = delete;

    /// \brief Sweeps the cache, removing expired resources
    virtual void sweep()
    {
        auto iter = std::begin(_resources);
        auto last = std::end(_resources);
        while (iter != last) {
            if (iter->second.expired()) {
                iter = _resources.erase(iter);
            }
            else {
                ++iter;
            }
        }
    }

    /// \brief Gets an existing resource by name
    /// \param name name of the resource
    /// \return pointer to the resource
    virtual ptr_type get(name_type const& name) const
    {
        auto iter = _resources.find(name);
        if (iter == std::end(_resources) || iter->second.expired()) {
            return nullptr;
        }
        return iter->second.lock();
    }

    /// \brief Gets a resource by name
    /// \param name name of the resource
    /// \return pointer to the resource
    ///
    /// If the resource does not exist, it is created.
    virtual ptr_type get(name_type const& name)
    {
        auto iter = _resources.find(name);
        if (iter != std::end(_resources) && !iter->second.expired()) {
            return iter->second.lock();
        }
        auto ptr = _creator(name);
        if (ptr == nullptr) {
            return nullptr;
        }
        if (iter != std::end(_resources)) {
            iter->second = ptr;
        }
        else {
            _resources.emplace(name, ptr);
        }
        return ptr;
    }

private:
    creator_type _creator; //!< Resource creation function
    std::map<name_type, std::weak_ptr<T>> _resources; //!< Resource container
};

/// \}

}
