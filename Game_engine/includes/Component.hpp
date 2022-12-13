/*
** EPITECH PROJECT, 2022
** Component.hpp
** File description:
** Game_engine
*/

#pragma once
#include <iostream>
#include <chrono>
#include "enum.hpp"
#include "config_comp.hpp"

class Game_engine;

///@class
/*
    Tout les components qu'on laisse disponible
    à vous d'en créer pour pouvoir les utiliser si besoin.
*/
class AComponent {
    public:
        const type_component get_type() const {return _type;};
        virtual ~AComponent() = default;
    protected:
        type_component _type;
    private:
};

///@note
/*
 à voir si à l'avenir je fait pas une class parent hitbox, et mouse hitbox est un enfant
 puis sprite hitbox par exemple sera un autre enfant ou quelque chose du genre.
*/
class Mouse_hitbox_component : public AComponent {
    public:
        Mouse_hitbox_component(void *conf);
        ~Mouse_hitbox_component() final;
        hitbox_rect_s get_hitbox_rect() const;
        void exe_pressed_func(Game_engine *g_e);
        void exe_released_func(Game_engine *g_e);
        void exe_overlay_func(Game_engine *g_e);
        void exe_default_func(Game_engine *g_e);
        void set_left_rect(unsigned int left);
        void set_top_rect(unsigned int top);
        void set_width_rect(unsigned int width);
        void set_height_rect(unsigned int height);
        bool is_overlap_hitbox(int pos_x, int pos_y);

    protected:
        hitbox_rect_s _hitbox_rect;
        ptr_func_custom _pressed_func;
        ptr_func_custom _released_func;
        ptr_func_custom _overlay_func;
        ptr_func_custom _default_func;
    private:
};

class Input_component : public AComponent {
    public:
        Input_component(void *conf);
        ~Input_component() final;
        std::vector<std::pair<int, ptr_func_custom>> get_input() const;
    protected:
        std::vector<std::pair<int, ptr_func_custom>> _input_keyboard;
    private:
};

class Movement_component : public AComponent {
     public:
        Movement_component(void *conf);
        ~Movement_component() final;
        void set_speed(const double &new_speed);
        double get_speed() const;
        void set_vector_dir(const double &x, const double &y);
        vector_2f_s get_vector_dir() const;
        void set_position(const double &x, const double &y);
        vector_2f_s get_position() const;
    protected:
        vector_2f_s _vector_dir;
        vector_2f_s _position;
        double _speed;
    private:
};

class Drawable_impl {
    public:
        Drawable_impl(const char *path_sprite);
        ~Drawable_impl();
        sprite_t get_sprite() const;
        void set_texture(const char *path_sprite);
        void set_position(const double x, const double y);
        void set_scale(const double x, const double y);
        void set_color(const color_t &color);
        void set_rotation(const unsigned int degree);
        void set_texture_rect(const unsigned int &left, const unsigned int &top, const unsigned int &width, const unsigned int &height);
        void set_move(const int &x, const int &y);
    protected:
    private:
        texture_t _texture;
        sprite_t _sprite;
};

class Drawable_component : public AComponent {
    public:
        Drawable_component(void *conf);
        ~Drawable_component() final;
        Drawable_impl *get_lib_graph() const;
    protected:
        Drawable_impl *_lib_graph;
    private:
};

class Text_impl {
    public:
        Text_impl(const char *path_font, const char *str_text); //Font/string/Position/Scale/Degree/
        ~Text_impl();
        text_t get_text() const;
        std::string get_string() const;
        void set_text(const char *str_text);
        void set_font(const char *path_font);
        void set_position(const double x, const double y);
        void set_scale(const float x, const float y);
        void set_rotation(const unsigned int degree);

    protected:
    private:
        text_t _text;
        font_t _font;
};

class Text_component : public AComponent {
    public:
        Text_component(void *conf); //Font/string/Position/Scale/Degree/
        ~Text_component() final;
        Text_impl *get_lib_text() const {return _lib_text;}

    protected:
        Text_impl *_lib_text;
    private:
};

class Sound_impl {
    public:
        Sound_impl(const char *path_sound);
        ~Sound_impl();
        sf::SoundSource::Status get_status();
        void play();
        void pause();
        void stop();
        void volume(const double &volume);

    protected:
    private:
        sound_buffer_t _sound_b;
        sound_t _sound;
};

class Sound_component : public AComponent {
    public:
        Sound_component(void *conf);
        ~Sound_component() final;
        std::vector<Sound_impl *> get_lib_sound() const;
    protected:
        std::vector<Sound_impl *> _lib_sound;
    private:
};

class Clock_component : public AComponent {
    public:
        Clock_component(void *conf);
        ~Clock_component() final;
        void restart_time();
        std::chrono::duration<double> get_time();
        void exe_clock_func(Game_engine *g_e);
    protected:
        double _timer;
        std::chrono::time_point<std::chrono::system_clock> _start;
        ptr_func_custom _clock_func;
    private:
};