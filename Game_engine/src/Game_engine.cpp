/*
** EPITECH PROJECT, 2022
** Game_engine.cpp
** File description:
** Game_engine
*/

#include "Game_engine.hpp"
#include <iostream>

std::vector<Entity *> filter_by_rfind_name(std::vector<Entity *> &list_entity, const std::string &name)
{
    std::vector<Entity *> new_list_entity;

    for (int i = 0; i < list_entity.size(); i++)
    {
        if (list_entity[i]->get_name_type().compare(0, name.size(), name.c_str()) == 0) {
            new_list_entity.push_back(list_entity[i]);
        }
    }
    return new_list_entity;
}

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name)
{
    std::vector<Entity *> new_list_entity;

    for (int i = 0; i < list_entity.size(); i++)
    {
        if (list_entity[i]->get_name_type().compare(name) == 0) {
            new_list_entity.push_back(list_entity[i]);
        }
    }
    return new_list_entity;
}

std::vector<Entity *> filter_by_component(std::vector<Entity *> &list_entity, type_component type)
{
    std::vector<Entity *> new_list_entity;

    for (int i = 0; i < list_entity.size(); i++)
    {
        if (list_entity[i]->get_ifcomp(type) == 1) {
            new_list_entity.push_back(list_entity[i]);
        }
    }
    return new_list_entity;
}

Game_engine::Game_engine(std::vector<Entity *> &list_entity, bool (* ptrfunc)(Game_engine *g_e))
{
    std::cout << "Game CREATE\n";
    _list_entity = std::move(list_entity);
    _cond_game_loop = ptrfunc;
    _rendersystem = nullptr;
    _eventsystem = nullptr;
    _networksystem = nullptr;
    _soundsystem = nullptr;
}

Game_engine::~Game_engine()
{
    std::cout << "Game DELETE\n";
    while (_list_entity.size() > 0) {
        delete _list_entity.front();
        _list_entity.erase(_list_entity.begin());
    }
    if (_rendersystem != nullptr)
        delete _rendersystem;
    if (_eventsystem != nullptr)
        delete _eventsystem;
    if (_networksystem->connect() == 0)
        _networksystem->udp_write(DISCONNECT, std::string("leave: ") + std::to_string(_networksystem->get_id()));
    // delete _networksystem;
    if (_soundsystem != nullptr)
        delete _soundsystem;
}

void Game_engine::set_cond_game_loop(bool (*ptr_func)(Game_engine *g_e))
{
    _cond_game_loop = ptr_func;
}

const void Game_engine::run()
{
    std::cout << "Run !\n";
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    while (_cond_game_loop(this))
    {
        if (static_cast<std::chrono::duration<double>>(std::chrono::system_clock::now() - start).count() > 0.016) {
            if (_rendersystem != nullptr && _eventsystem != nullptr)
                update_event();
            if (_soundsystem != nullptr)
                update_sound();
            update_custom();
            if (_rendersystem != nullptr)
                update_display();
            start = std::chrono::system_clock::now();
        }
        if (_rendersystem != nullptr && _rendersystem->wdw_isopen() == false)
            return;
    }
}

void Game_engine::update_event()
{
    event_t &event = _eventsystem->get_event();

    while (_rendersystem->get_event_wdw(event)) {
        // std::cout << "EVENT: type = " << event.type << std::endl;
        if (_eventsystem->event_wdw_close())
        {
            _rendersystem->close_wdw();
        }
        if (_eventsystem->event_input_keyboard_pressed()) {
            _eventsystem->input_event(this);
        } else {
            _eventsystem->mouse_event(this);
        }
        _eventsystem->custom_event(this);
    }
}

void Game_engine::update_sound()
{
    _soundsystem->running_music();
    _soundsystem->play_sound_effect();
}

void Game_engine::update_display()
{
    /// @note
    //filtre la list d'entity avec les component drawable
    //boucle tout les éléments filtré et les mettre dans le rendersystem
    //display_wdw()
    std::vector<Entity *> drawable_list = filter_by_component(_list_entity, DRAWABLE_C);
    std::vector<Entity *> text_list = filter_by_component(_list_entity, TEXT_C);

    _rendersystem->pre_draw();
    for (int i = 0; i < drawable_list.size(); i++)
    {
        // std::cout << drawable_list[i]->get_name_type() << std::endl;
        _rendersystem->draw_sprite(drawable_list[i]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite());
    }
    for (int i = 0; i < text_list.size(); i++)
    {
        _rendersystem->draw_text(text_list[i]->get_component<Text_component>(TEXT_C)->get_lib_text()->get_text());
    }
    _rendersystem->display_wdw();
    _rendersystem->post_draw();
}

void Game_engine::update_custom()
{
    std::vector<Entity *> clock_list = filter_by_component(_list_entity, CLOCK_C);

    for (auto clock_func : clock_list) {
        clock_func->get_component<Clock_component>(CLOCK_C)->exe_clock_func(this);
    }
    for (auto custom_func : _custom_function) {
        custom_func.first(this);
    }
}

void Game_engine::add_custom_func(void (* ptr_func)(Game_engine *g_e), const std::string &name_func)
{
    _custom_function.push_back(std::pair<ptr_func_custom, std::string>(ptr_func, name_func));
}

void Game_engine::del_custom_func(const std::string &name_func)
{
    for (int i = 0; i < _custom_function.size(); i++) {
        if (_custom_function[i].second.compare(name_func.c_str()) == 0) {
            _custom_function.erase(_custom_function.begin() + i);
            return;
        }
    }
}
