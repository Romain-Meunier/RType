/*
** EPITECH PROJECT, 2022
** eventsystem.cpp
** File description:
** System
*/

#include <iostream>
#include "Game_engine.hpp"

std::vector<Entity *> filter_by_component(std::vector<Entity *> &list_entity, type_component type);

Eventsystem::Eventsystem(void *conf)
{
    std::cout << "Eventsystem enable\n";
}

Eventsystem::~Eventsystem()
{
    std::cout << "Eventsystem disable\n";
}

event_t &Eventsystem::get_event()
{
    return _event;
}

void Eventsystem::mouse_event(Game_engine *g_e) const 
{
    std::vector<Entity *> filtered_list = filter_by_component(g_e->get_list_entity(), MOUSE_HTBX_C);
    sf::Vector2f mouse_coord = g_e->get_rendersystem()->get_window()->mapPixelToCoords(sf::Mouse::getPosition(*g_e->get_rendersystem()->get_window()));
    Mouse_hitbox_component *tmp_comp;

    for (int i = 0; i < filtered_list.size(); i++)
    {
        tmp_comp = filtered_list[i]->get_component<Mouse_hitbox_component>(MOUSE_HTBX_C);
        if (tmp_comp->is_overlap_hitbox(mouse_coord.x, mouse_coord.y)) {
            switch (_event.type)
            {
            case sf::Event::MouseButtonPressed:
                tmp_comp->exe_pressed_func(g_e);
                return;
            case sf::Event::MouseButtonReleased:
                tmp_comp->exe_released_func(g_e);
                return;
            default:
                tmp_comp->exe_overlay_func(g_e);
                return;
            }
        } else
            tmp_comp->exe_default_func(g_e);
        // if (filtered_list != filter_by_component(list_entity, MOUSE_HTBX_C)) //SOLUTION PERFECT but not opti
        //     return;
    }
}

void Eventsystem::input_event(Game_engine *g_e) const
{
    std::vector<Entity *> filtered_list = filter_by_component(g_e->get_list_entity(), INPUT_C);
    std::vector<std::pair<int, ptr_func_custom>> list_input_key;

    for (int i_entity = 0; i_entity < filtered_list.size(); i_entity++) 
    {
        list_input_key = filtered_list[i_entity]->get_component<Input_component>(INPUT_C)->get_input();
        for (int i = 0; i < list_input_key.size(); i++)
        {
            if (_event.key.code == list_input_key[i].first)
                list_input_key[i].second(g_e);
        }
    }
}
void Eventsystem::custom_event(Game_engine *g_e) const
{
    for (auto custom_func : _custom_event) {
        custom_func.first(g_e);
    }
}

void Eventsystem::add_custom_event(void (* ptr_func)(Game_engine *g_e), const std::string &name_event)
{
    _custom_event.push_back(std::pair<ptr_func_custom, std::string>(ptr_func, name_event));
}

void Eventsystem::del_custom_event(const std::string &name_func)
{
    for (int i = 0; i < _custom_event.size(); i++) {
        if (_custom_event[i].second.compare(name_func.c_str()) == 0) {
            _custom_event.erase(_custom_event.begin() + i);
            return;
        }
    }
}

const bool Eventsystem::event_wdw_close() const
{
    if (_event.type == sf::Event::Closed)
        return true;
    return false;
}

const bool Eventsystem::event_input_keyboard_pressed() const
{
    if (_event.type == sf::Event::KeyPressed)
        return true;
    return false;
}
