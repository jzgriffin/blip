// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref blip::application class implementation
/// \ingroup application

#include "blip/application.hpp"
#include "blip/main_menu_state.hpp"
#include "blip/path.hpp"
#include "blip/xml_deserializer.hpp"
#include "blip/xml_serializer.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <stdexcept>

namespace blip {

application::application()
    : _resource_mgr{join_path({
        find_system_path(system_path::resources_path), "Resources"})}
{
    add_resource_caches();
    load_input_spec();
    load_config();

    sf::VideoMode video_mode{_config.width, _config.height, _config.depth};
    auto window_style = _config.is_full_screen
        ? sf::Style::Fullscreen
        : sf::Style::Default;
    sf::ContextSettings context_settings;
    context_settings.antialiasingLevel = _config.antialiasing_level;
    _window.create(video_mode, product, window_style, context_settings);
    _window.setVerticalSyncEnabled(_config.use_vertical_sync);
}

application::~application()
{
    save_config();
}

void application::exit(int exit_code) noexcept
{
    _is_running = false;
    _exit_code = exit_code;
}

int application::run()
{
    _state_mgr.push_back(std::make_unique<main_menu_state>(*this));

    sf::Clock frame_clock;
    float time_step{0.0f};

    _is_running = true;
    while (_is_running) {
        _state_mgr.work();

        // After working on the state manager, we must lock in order to
        // perform notifications/updates/draws
        std::lock_guard<decltype(_state_mgr.mutex)> lock{_state_mgr.mutex};
        
        sf::Event event;
        while (_window.pollEvent(event)) {
            notify(event);
        }
        update(time_step);
        draw();

        time_step = frame_clock.restart().asSeconds();
    }
    return _exit_code;
}

void application::notify(sf::Event const& event)
{
    if (_state_mgr.notify(event)) {
        return;
    }

    switch (event.type) {
        case sf::Event::Closed:
            exit();
            break;

        default:
            break;
    }
}

void application::update(float time_step)
{
    _state_mgr.update(time_step);
}

void application::draw()
{
    _window.clear();
    _window.draw(_state_mgr);
    _window.display();
}

void application::add_resource_caches()
{
    using sound_buffer_cache_type = typed_resource_cache<sf::SoundBuffer>;
    _resource_mgr.add_cache<sound_buffer_cache_type::resource_type>(
        std::make_unique<sound_buffer_cache_type>([this](
            sound_buffer_cache_type::name_type const& name)
                -> sound_buffer_cache_type::ptr_type
        {
            auto ptr =
                std::make_shared<sound_buffer_cache_type::resource_type>();
            auto path = _resource_mgr.path_to(join_path({"Sounds", name}));
            if (!ptr->loadFromFile(path)) {
                return nullptr;
            }
            return ptr;
        }));

    using font_cache_type = typed_resource_cache<sf::Font>;
    _resource_mgr.add_cache<font_cache_type::resource_type>(
        std::make_unique<font_cache_type>([this](
            font_cache_type::name_type const& name)
                -> font_cache_type::ptr_type
        {
            auto ptr =
                std::make_shared<font_cache_type::resource_type>();
            auto path = _resource_mgr.path_to(join_path({"Fonts", name}));
            if (!ptr->loadFromFile(path)) {
                return nullptr;
            }
            return ptr;
        }));

    using image_cache_type = typed_resource_cache<sf::Image>;
    _resource_mgr.add_cache<image_cache_type::resource_type>(
        std::make_unique<image_cache_type>([this](
            image_cache_type::name_type const& name)
                -> image_cache_type::ptr_type
        {
            auto ptr =
                std::make_shared<image_cache_type::resource_type>();
            auto path = _resource_mgr.path_to(join_path({"Images", name}));
            if (!ptr->loadFromFile(path)) {
                return nullptr;
            }
            return ptr;
        }));

    using texture_cache_type = typed_resource_cache<sf::Texture>;
    _resource_mgr.add_cache<texture_cache_type::resource_type>(
        std::make_unique<texture_cache_type>([this](
            texture_cache_type::name_type const& name)
                -> texture_cache_type::ptr_type
        {
            auto ptr =
                std::make_shared<texture_cache_type::resource_type>();
            auto path = _resource_mgr.path_to(join_path({"Images", name}));
            if (!ptr->loadFromFile(path)) {
                return nullptr;
            }
            return ptr;
        }));
}

void application::load_input_spec()
{
    pugi::xml_document doc;
    auto path = _resource_mgr.path_to(join_path(
        {"Configurations", "InputSpecification.xml"}));
    if (!doc.load_file(path.c_str())) {
        throw std::runtime_error{"unable to load input specification"};
    }

    xml_deserializer dx{doc};
    if (!dx.child("InputSpecification", _input_spec)) {
        throw std::runtime_error{"unable to load input specification"};
    }
}

void application::load_config()
{
    _config_path = join_path({find_system_path(system_path::preferences_path),
        company, product});
    if (!create_directory(_config_path)) {
        throw std::runtime_error{"unable to create preferences directory"};
    }
    _config_path = join_path({_config_path, "Application.xml"});

    pugi::xml_document doc;
    if (doc.load_file(_config_path.c_str())) {
        xml_deserializer dx{doc.child("Application")};
        if (dx) {
            dx.child("Configuration", _config);
            dx.child("InputMap", _input_map, _input_spec);
        }
    }

    if (_input_map.contexts.empty()) {
        auto path = _resource_mgr.path_to(join_path(
            {"Configurations", "InputMap.xml"}));
        if (doc.load_file(path.c_str())) {
            xml_deserializer{doc}.child("InputMap", _input_map, _input_spec);
        }
    }

    if (_input_map.contexts.empty()) {
        throw std::runtime_error{"unable to load input map"};
    }
}

void application::save_config() const
{
    pugi::xml_document doc;
    xml_serializer sx{doc.append_child("Application")};
    sx.child("Configuration", _config);
    sx.child("InputMap", _input_map);
    doc.save_file(_config_path.c_str());
}

}
