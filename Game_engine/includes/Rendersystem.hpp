/*
** EPITECH PROJECT, 2022
** Rendersystem.hpp
** File description:
** System
*/

#pragma once

#include "SFML_typedef.hpp"

class I_Rendersystem {
    public:
        virtual ~I_Rendersystem() = default;
        virtual void close_wdw() = 0;
        virtual void pre_draw() = 0;
        virtual void draw_sprite(sprite_t sprite) = 0;
        virtual void draw_text(text_t text) = 0;
        virtual void display_wdw() = 0;
        virtual void post_draw() = 0;
        virtual const bool wdw_isopen() = 0;
        virtual const bool get_event_wdw(event_t &event) = 0;
        virtual window_t *get_window() = 0;
    protected:
    private:
};

class Rendersystem : public I_Rendersystem {
    public:
        Rendersystem(void *conf = nullptr);
        ~Rendersystem() final;
        void close_wdw() final;
        void pre_draw() final {};
        void draw_sprite(sprite_t sprite) final;
        void draw_text(text_t text) final;
        void display_wdw() final;
        void post_draw() final {};
        const bool wdw_isopen() final;
        const bool get_event_wdw(event_t &event) final;
        window_t *get_window() final;

    protected:
        window_t *_window;
    private:
};
