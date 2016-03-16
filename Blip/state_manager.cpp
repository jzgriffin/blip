// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::state_manager class implementation
/// \ingroup state

#include "blip/state_manager.hpp"
#include "blip/iterator.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace blip {

bool state_manager::push_front(pointer_type&& ptr)
{
    return try_job<push_front_job>(std::move(ptr));
}

bool state_manager::push_back(pointer_type&& ptr)
{
    return try_job<push_back_job>(std::move(ptr));
}

bool state_manager::pop_front()
{
    return try_job<pop_front_job>();
}

bool state_manager::pop_back()
{
    return try_job<pop_back_job>();
}

bool state_manager::change_front(pointer_type&& ptr)
{
    auto did_push = push_front(std::move(ptr));
    auto did_pop = pop_front();
    return did_push && did_pop;
}

bool state_manager::change_back(pointer_type&& ptr)
{
    auto did_push = push_back(std::move(ptr));
    auto did_pop = pop_back();
    return did_push && did_pop;
}

bool state_manager::clear()
{
    return try_job<clear_job>();
}

bool state_manager::work()
{
    // Ensure that there are jobs to be done before attempting a lock
    if (_jobs.empty()) {
        return false;
    }

    // Work cannot be done if the mutex cannot be locked, otherwise iterators
    // might be invalidated
    if (!mutex.try_lock()) {
        return false;
    }

    std::lock_guard<mutex_type> lock{mutex, std::adopt_lock_t{}};
    while (!_jobs.empty()) {
        _jobs.front()->apply(*this);
        _jobs.pop();
    }
    return true;
}

bool state_manager::notify(const sf::Event& event)
{
    for (auto&& p : reverse(_list)) {
        if (p->is_focused()) {
            if (p->notify(event)) {
                return true;
            }
        }
    }
    return false;
}

void state_manager::update(float time_step)
{
    for (auto&& p : reverse(_list)) {
        if (p->is_enabled()) {
            p->update(time_step);
        }
    }
}

void state_manager::draw(sf::RenderTarget& target, sf::RenderStates states)
    const
{
    for (auto&& p : _list) {
        if (p->is_visible()) {
            target.draw(*p, states);
        }
    }
}

// Explicit vtable for purely virtual class
state_manager::job::~job() = default;

void state_manager::push_front_job::apply(state_manager& mgr)
{
    // When pushing onto the front, we must toggle off the pushed state
    // depending on the states behind it

    auto dbn = false;
    auto dbu = false;
    auto dbd = false;
    for (auto&& p : mgr._list) {
        if (does_block_notify(p->type)) {
            dbn = true;
        }
        if (does_block_update(p->type)) {
            dbu = true;
        }
        if (does_block_draw(p->type)) {
            dbd = true;
        }
        if (dbn && dbu && dbd) {
            break;
        }
    }

    if (!dbn) {
        ptr->focus();
    }
    if (!dbu) {
        ptr->enable();
    }
    if (!dbd) {
        ptr->show();
    }

    mgr._list.emplace_front(std::move(ptr));
}

void state_manager::push_back_job::apply(state_manager& mgr)
{
    // When pushing onto the back, we must toggle off the states in front of
    // the back depending on the pushed state

    ptr->focus();
    ptr->enable();
    ptr->show();

    auto dbn = does_block_notify(ptr->type);
    auto dbu = does_block_update(ptr->type);
    auto dbd = does_block_draw(ptr->type);
    for (auto&& p : reverse(mgr._list)) {
        if (dbn) {
            p->neglect();
        }
        if (dbu) {
            p->disable();
        }
        if (dbd) {
            p->hide();
        }
    }

    mgr._list.emplace_back(std::move(ptr));
}

void state_manager::pop_front_job::apply(state_manager& mgr)
{
    // When popping off of the front, we don't have to toggle anything

    mgr._list.pop_front();
}

void state_manager::pop_back_job::apply(state_manager& mgr)
{
    // When popping off of the back, we must toggle on the states in front of
    // the back depending on the popped state

    auto ptr = mgr._list.back().get();
    auto dbn = does_block_notify(ptr->type);
    auto dbu = does_block_update(ptr->type);
    auto dbd = does_block_draw(ptr->type);

    mgr._list.pop_back();

    for (auto&& p : reverse(mgr._list)) {
        if (dbn) {
            p->focus();
            dbn = false;
        }
        if (dbu) {
            p->enable();
            dbu = false;
        }
        if (dbd) {
            p->show();
            dbd = false;
        }
        if (!dbn && !dbu && !dbd) {
            break;
        }
    }
}

void state_manager::clear_job::apply(state_manager& mgr)
{
    mgr._list.clear();
}

}
