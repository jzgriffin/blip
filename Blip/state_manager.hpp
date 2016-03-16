// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::state_manager class interface
/// \ingroup state

#pragma once

#include "blip/notifiable.hpp"
#include "blip/state.hpp"
#include "blip/updatable.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

namespace blip {

/// \addtogroup state
/// \{

/// \brief Manager for several \ref state instances
class state_manager : public notifiable, public updatable, public sf::Drawable
{
public:
    /// \brief Type of owning smart pointer for states
    using pointer_type = std::unique_ptr<state>;

    /// \brief Type of container for states
    using container_type = std::list<pointer_type>;

    /// \brief Type of mutex for using the state list
    using mutex_type = std::mutex;

    /// \brief Mutex for using the state list
    mutex_type mutex;

    /// \brief Pushes a state onto the front of the state list
    /// \param ptr pointer to the state to push
    /// \return whether the change was applied immediately
    /// \see pop_front
    bool push_front(pointer_type&& ptr);

    /// \brief Pushes a state onto the back of the state list
    /// \param ptr pointer to the state to push
    /// \return whether the change was applied immediately
    /// \see pop_back
    bool push_back(pointer_type&& ptr);

    /// \brief Pops a state off of the front of the state list
    /// \return whether the change was applied immediately
    /// \see push_front
    bool pop_front();

    /// \brief Pops a state off of the back of the state list
    /// \return whether the change was applied immediately
    /// \see push_back
    bool pop_back();

    /// \brief Pops off of and pushes onto the front of the state list
    /// \param ptr pointer to the state to push
    /// \return whether the change was applied immediately
    /// \see push_front
    /// \see pop_front
    bool change_front(pointer_type&& ptr);

    /// \brief Pops off of and pushes onto the back of the state list
    /// \param ptr pointer to the state to push
    /// \return whether the change was applied immediately
    /// \see push_back
    /// \see pop_back
    bool change_back(pointer_type&& ptr);

    /// \brief Clears the state list
    /// \return whether the change was applied immediately
    bool clear();

    /// \brief Works through the queue of pending jobs, applying each change
    /// \return whether work was done
    ///
    /// If this method returns false, either the state list could not be
    /// locked or the job queue was empty.
    bool work();

    /// \brief Notifies the focused states of an event
    /// \param event event to notify of
    /// \return whether or not the event was intercepted
    ///
    /// The notification is propagated from back to front until interception.
    bool notify(const sf::Event& event) override;

    /// \brief Updates the enabled states by a time step
    /// \param time_step time step to update by
    ///
    /// The update is propagated from back to front.
    void update(float time_step) override;

protected:
    /// \brief Draws the visible states to the given render target
    /// \param target render target to draw to
    /// \param states current render states
    ///
    /// The draw is propagated from front to back.
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
        override;

private:
    /// \brief Interface implemented by job types
    struct job
    {
        /// \brief Destructs the \ref job instance
        virtual ~job();

        /// \brief Applies the job to the given state manager
        /// \param mgr manager to apply the job to
        virtual void apply(state_manager& mgr) = 0;
    };

    /// \brief Job for pushing onto the front of the state list
    struct push_front_job final : job
    {
        /// \brief Pointer to push
        pointer_type ptr;

        /// \brief Initializes a new instance of the \ref push_front_job
        /// structure with the given pointer to push
        /// \param p pointer to push
        explicit push_front_job(pointer_type&& p)
            : ptr{std::move(p)}
        {
        }

        /// \brief Applies the job to the given state manager
        /// \param mgr manager to apply the job to
        void apply(state_manager& mgr) override;
    };

    /// \brief Job for pushing onto the back of the state list
    struct push_back_job final : job
    {
        /// \brief Pointer to push
        pointer_type ptr;

        /// \brief Initializes a new instance of the \ref push_back_job
        /// structure with the given pointer to push
        /// \param p pointer to push
        explicit push_back_job(pointer_type&& p)
            : ptr{std::move(p)}
        {
        }

        /// \brief Applies the job to the given state manager
        /// \param mgr manager to apply the job to
        void apply(state_manager& mgr) override;
    };

    /// \brief Job for popping off of the front of the state list
    struct pop_front_job final : job
    {
        /// \brief Applies the job to the given state manager
        /// \param mgr manager to apply the job to
        void apply(state_manager& mgr) override;
    };

    /// \brief Job for popping off of the back of the state list
    struct pop_back_job final : job
    {
        /// \brief Applies the job to the given state manager
        /// \param mgr manager to apply the job to
        void apply(state_manager& mgr) override;
    };

    /// \brief Job for clearing the state list
    struct clear_job final : job
    {
        /// \brief Applies the job to the given state manager
        /// \param mgr manager to apply the job to
        void apply(state_manager& mgr) override;
    };

    std::queue<std::unique_ptr<job>> _jobs; //!< Queue of pending jobs
    container_type _list; //!< List of managed states

    /// \brief Tries to perform a job
    /// \tparam Job type of job to perform
    /// \tparam Args types of arguments for the job
    /// \param args arguments for the job
    /// \return whether the change was applied immediately
    ///
    /// If the change could not be applied immediately, it will be placed on
    /// the job queue.
    template <typename Job, typename... Args>
    bool try_job(Args&&... args)
    {
        if (mutex.try_lock()) {
            std::lock_guard<mutex_type> lock{mutex, std::adopt_lock_t{}};
            Job job{std::forward<Args>(args)...};
            job.apply(*this);
            return true;
        }

        _jobs.emplace(
            std::make_unique<Job>(std::forward<Args>(args)...));
        return false;
    }
};

/// \}

}
