/*
** EPITECH PROJECT, 2022
** Mouse_event_component.cpp
** File description:
** Component
*/

#include "Component.hpp"
#include <stdarg.h>

sf::Vector2f modif_graphics_from_screen(float x, float y);

Mouse_hitbox_component::Mouse_hitbox_component(void *conf)
{
    std::cout << "Create Mouse_hitbox_component\n";
    mouse_hitbox_conf_s *conf_tmp = static_cast<mouse_hitbox_conf_s *>(conf);
    sf::Vector2f tmp_hitbox; //c'est pénible d'utiliser sfml ici mais bon.. pas trop le choix ou 4 appels de fonction au pire

    _type = MOUSE_HTBX_C;
    tmp_hitbox = modif_graphics_from_screen(conf_tmp->rect.left, conf_tmp->rect.top);
    _hitbox_rect.left = tmp_hitbox.x;
    _hitbox_rect.top = tmp_hitbox.y;
    tmp_hitbox = modif_graphics_from_screen(conf_tmp->rect.width, conf_tmp->rect.height);
    _hitbox_rect.width = tmp_hitbox.x;
    _hitbox_rect.height = tmp_hitbox.y;
    _pressed_func = conf_tmp->pressed;
    _released_func = conf_tmp->released;
    _overlay_func = conf_tmp->overlay;
    _default_func = conf_tmp->by_default;
    delete conf_tmp;
}

Mouse_hitbox_component::~Mouse_hitbox_component()
{
    std::cout << "Delete Mouse_hitbox_component\n";
}

hitbox_rect_s Mouse_hitbox_component::get_hitbox_rect() const
{
    return _hitbox_rect;
}

void Mouse_hitbox_component::set_left_rect(unsigned int left)
{
    _hitbox_rect.left = left;
}

void Mouse_hitbox_component::set_top_rect(unsigned int top)
{
    _hitbox_rect.top = top;
}

void Mouse_hitbox_component::set_width_rect(unsigned int width)
{
    _hitbox_rect.width = width;
}

void Mouse_hitbox_component::set_height_rect(unsigned int height)
{
    _hitbox_rect.height = height;
}

void Mouse_hitbox_component::exe_pressed_func(Game_engine *g_e)
{
    _pressed_func(g_e);
}

void Mouse_hitbox_component::exe_released_func(Game_engine *g_e)
{
    _released_func(g_e);
}

void Mouse_hitbox_component::exe_overlay_func(Game_engine *g_e)
{
    _overlay_func(g_e);
}

void Mouse_hitbox_component::exe_default_func(Game_engine *g_e)
{
    _default_func(g_e);
}

bool Mouse_hitbox_component::is_overlap_hitbox(int pos_x, int pos_y)
{
    if (_hitbox_rect.left <= pos_x && pos_x <= (_hitbox_rect.left + _hitbox_rect.width))
        if (_hitbox_rect.top <= pos_y && pos_y <= (_hitbox_rect.top + _hitbox_rect.height))
            return true;
    return false;
}