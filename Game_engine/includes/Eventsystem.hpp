/*
** EPITECH PROJECT, 2022
** eventsystem.hpp
** File description:
** System
*/

#pragma once

#include "Entity.hpp"

class Game_engine;

class I_Eventsystem {
    public:
        virtual ~I_Eventsystem() = default;
        virtual event_t &get_event() = 0;
        virtual void mouse_event(Game_engine *g_e) const = 0;
        virtual void input_event(Game_engine *g_e) const = 0;
        virtual void custom_event(Game_engine *g_e) const = 0;
        virtual void add_custom_event(ptr_func_custom, const std::string &name_func) = 0;
        virtual void del_custom_event(const std::string &name_func) = 0;
        virtual const bool event_wdw_close() const = 0;
        virtual const bool event_input_keyboard_pressed() const = 0;
    protected:
    private:
};

class Eventsystem : public I_Eventsystem {
    public:
        Eventsystem(void *conf = nullptr);
        ~Eventsystem() final;
        event_t &get_event() final;
        void mouse_event(Game_engine *g_e) const final;
        void input_event(Game_engine *g_e) const final;
        void custom_event(Game_engine *g_e) const final;
        void add_custom_event(ptr_func_custom, const std::string &name_func);
        void del_custom_event(const std::string &name_func);
        const bool event_wdw_close() const final;
        const bool event_input_keyboard_pressed() const final;
    protected:
        event_t _event;
        std::vector<std::pair<ptr_func_custom, std::string>> _custom_event;
    private:
};