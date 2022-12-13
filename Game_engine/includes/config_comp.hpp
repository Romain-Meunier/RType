/*
** EPITECH PROJECT, 2022
** config_comp.hpp
** File description:
** Game_engine
*/

#pragma once
#include "SFML_typedef.hpp"

class Game_engine;
typedef void(*ptr_func_custom)(Game_engine *g_e);

typedef struct hitbox_rect_t {
    double left;
    double top;
    double width;
    double height;
}hitbox_rect_s;

typedef struct texture_rect_t {
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
}texture_rect_s;

typedef struct vector_2ui_t {
    unsigned int x;
    unsigned int y;
}vector_2ui_s;

typedef struct vector_2f_t {
    double x;
    double y;
}vector_2f_s;

typedef struct mouse_hitbox_conf_t {
    hitbox_rect_s rect;
    ptr_func_custom pressed;
    ptr_func_custom released;
    ptr_func_custom overlay;
    ptr_func_custom by_default;
}mouse_hitbox_conf_s;

typedef struct event_conf_t {
    std::vector<std::pair<int, ptr_func_custom>> list_input_func;
}event_conf_s;

typedef struct movement_conf_t {
    vector_2f_s vector_dir;
    vector_2f_s position;
    double speed;
}movement_conf_s;

typedef struct window_conf_t {
    unsigned int width;
    unsigned int height;
    char *title;
}window_conf_s;

typedef struct text_conf_t {
    const char *path_font;
    const char *string_txt;
    vector_2f_s pos;
    vector_2ui_s scale;
    unsigned int degree;
}text_conf_s;

typedef struct drawable_conf_t {
    const char *path_sprite;
    vector_2f_s pos;
    vector_2f_s scale;
    unsigned int degree;
    texture_rect_s rect;
}drawable_conf_s;

typedef struct sound_conf_t {
    std::vector<const char *> path_sound;
    std::vector<double> volume;
}sound_conf_s;

typedef struct clock_conf_t {
    double timer;
    ptr_func_custom clock_func;
}clock_conf_s;