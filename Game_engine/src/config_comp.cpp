/*
** EPITECH PROJECT, 2022
** create_entity.cpp
** File description:
** Game_engine
*/

#include "Entity.hpp"
#include <cstdarg>

movement_conf_s *config_comp_movement(va_list &vl)
{
    movement_conf_s *config = new movement_conf_s;

    config->vector_dir.x = va_arg(vl, double);
    config->vector_dir.y = va_arg(vl, double);
    config->position.x = va_arg(vl, double);
    config->position.y = va_arg(vl, double);
    config->speed = va_arg(vl, double);
    return config;
}

text_conf_s *config_comp_text(va_list &vl)
{
    text_conf_s *config = new text_conf_s;

    config->path_font = va_arg(vl, const char *);
    config->string_txt = va_arg(vl, const char *);
    config->pos.x = va_arg(vl, double);
    config->pos.y = va_arg(vl, double);
    config->scale.x = va_arg(vl, unsigned int);
    config->scale.y = va_arg(vl, unsigned int);
    config->degree = va_arg(vl, unsigned int);
    return config;
}

sound_conf_s *config_comp_sound(const unsigned int nbr_arg, va_list &vl)
{
    sound_conf_s *config = new sound_conf_s;

    for (int i = 0; i < nbr_arg; i++)
    {
        config->path_sound.push_back(va_arg(vl, const char *));
        config->volume.push_back(va_arg(vl, double));
    }
    return config;
}

event_conf_s *config_comp_input(const unsigned int nbr_arg, va_list &vl)
{
    event_conf_s *config = new event_conf_s;
    std::pair<int, ptr_func_custom> input_x_func;

    for (int i = 0; i < nbr_arg; i++)
    {
        input_x_func.first = va_arg(vl, int);
        input_x_func.second = va_arg(vl, ptr_func_custom);
        config->list_input_func.push_back(std::move(input_x_func));
    }
    return config;
}

drawable_conf_s *config_comp_drawable(va_list &vl)
{
    drawable_conf_s *config = new drawable_conf_s;

    config->path_sprite = va_arg(vl, const char *);
    config->pos.x = va_arg(vl, double);
    config->pos.y = va_arg(vl, double);
    config->scale.x = va_arg(vl, double);
    config->scale.y = va_arg(vl, double);
    config->degree = va_arg(vl, unsigned int);
    config->rect.left = va_arg(vl, unsigned int);
    config->rect.top = va_arg(vl, unsigned int);
    config->rect.width = va_arg(vl, unsigned int);
    config->rect.height = va_arg(vl, unsigned int);
    return config;
}

mouse_hitbox_conf_s *config_comp_mouse_hitbox(va_list &vl)
{
    mouse_hitbox_conf_s *config = new mouse_hitbox_conf_s;

    config->rect.left = va_arg(vl, double);
    config->rect.top = va_arg(vl, double);
    config->rect.width = va_arg(vl, double);
    config->rect.height = va_arg(vl, double);
    config->pressed = va_arg(vl, ptr_func_custom);
    config->released = va_arg(vl, ptr_func_custom);
    config->overlay = va_arg(vl, ptr_func_custom);
    config->by_default = va_arg(vl, ptr_func_custom);
    return config;
}

clock_conf_s *config_comp_clock(va_list &vl)
{
    clock_conf_s *config = new clock_conf_s;

    config->timer = va_arg(vl, double);
    config->clock_func = va_arg(vl, ptr_func_custom);
    return config;
}