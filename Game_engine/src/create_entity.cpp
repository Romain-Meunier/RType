/*
** EPITECH PROJECT, 2022
** create_entity.cpp
** File description:
** Game_engine
*/

#include "Entity.hpp"
#include <cstdarg>

mouse_hitbox_conf_s *config_comp_mouse_hitbox(va_list &vl);
drawable_conf_s *config_comp_drawable(va_list &vl);
event_conf_s *config_comp_input(const unsigned int nbr_arg, va_list &vl);
sound_conf_s *config_comp_sound(const unsigned int nbr_arg, va_list &vl);
text_conf_s *config_comp_text(va_list &vl);
clock_conf_s *config_comp_clock(va_list &vl);

/// @tparam
/// @def @copyright @example

Entity *create_player(const char *name_component, const unsigned int nbr_input, const unsigned int nbr_sound, ...)
{
    Entity *player = new Entity(name_component);
    va_list vl;
    
    va_start(vl, nbr_sound);
    player->add_component<Drawable_component>(config_comp_drawable(vl));
    player->add_component<Input_component>(config_comp_input(nbr_input, vl));
    player->add_component<Clock_component>(config_comp_clock(vl));
    player->add_component<Sound_component>(config_comp_sound(nbr_sound, vl));
    va_end(vl);
    return player;
}


Entity *create_drawable_sound(const char *name_component, const unsigned int nbr_sound, ...)
{
    Entity *drawable_sound = new Entity(name_component);
    va_list vl;

    va_start(vl, nbr_sound);
    drawable_sound->add_component<Drawable_component>(config_comp_drawable(vl));
    drawable_sound->add_component<Sound_component>(config_comp_sound(nbr_sound, vl));
    va_end(vl);
    return drawable_sound;
}

Entity *create_img_clock_sound(const char *name_component, const unsigned int nbr_sound, ...)
{
    Entity *img_clock_sound = new Entity(name_component);
    va_list vl;

    va_start(vl, nbr_sound);
    img_clock_sound->add_component<Drawable_component>(config_comp_drawable(vl));
    img_clock_sound->add_component<Clock_component>(config_comp_clock(vl));
    img_clock_sound->add_component<Sound_component>(config_comp_sound(nbr_sound, vl));
    va_end(vl);
    return img_clock_sound;
}

Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...)
{
    Entity *button = new Entity(name_component);
    va_list vl;

    va_start(vl, nbr_arg);
    button->add_component<Drawable_component>(config_comp_drawable(vl));
    button->add_component<Mouse_hitbox_component>(config_comp_mouse_hitbox(vl));
    button->add_component<Sound_component>(config_comp_sound(nbr_arg, vl));
    va_end(vl);
    return button;
}

Entity *create_chat(const char *name_component, ...)
{
    Entity *chat = new Entity(name_component);
    va_list vl;

    va_start(vl, name_component);
    chat->add_component<Drawable_component>(config_comp_drawable(vl));
    chat->add_component<Mouse_hitbox_component>(config_comp_mouse_hitbox(vl));
    chat->add_component<Text_component>(config_comp_text(vl));
    va_end(vl);
    return chat;
}

Entity *create_img_clock(const char *name_component, ...)
{
    Entity *img_clock = new Entity(name_component);
    va_list vl;

    va_start(vl, name_component);
    img_clock->add_component<Drawable_component>(config_comp_drawable(vl));
    img_clock->add_component<Clock_component>(config_comp_clock(vl));
    va_end(vl);
    return img_clock;
}

Entity *create_clock(const char *name_component, ...)
{
    Entity *clock = new Entity(name_component);
    va_list vl;

    va_start(vl, name_component);
    clock->add_component<Clock_component>(config_comp_clock(vl));
    va_end(vl);
    return clock;
}


Entity *create_text(const char *name_component, ...)
{
    Entity *text_entity = new Entity(name_component);
    va_list vl;

    va_start(vl, name_component);
    text_entity->add_component<Text_component>(config_comp_text(vl));
    va_end(vl);
    return text_entity;
}

Entity *create_drawable(const char *name_component, ...)
{
    Entity *drawable = new Entity(name_component);
    va_list vl;

    va_start(vl, name_component);
    drawable->add_component<Drawable_component>(config_comp_drawable(vl));
    va_end(vl);
    return drawable;
}
/// @endif