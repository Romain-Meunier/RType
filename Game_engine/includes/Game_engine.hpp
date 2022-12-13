/*
** EPITECH PROJECT, 2022
** Game_engine.hpp
** File description:
** Game_engine
*/

#pragma once
#include "Rendersystem.hpp"
#include "Eventsystem.hpp"
#include "Network.hpp"
#include "Soundsystem.hpp"

class Game_engine {
    public:
        Game_engine(std::vector<Entity *> &list_entity, bool (* ptr_func)(Game_engine *g_e));
        ~Game_engine();

        template <typename render_class>
        void enable_rendersystem(void *conf = nullptr)
        {
            _rendersystem = new render_class(conf);
        }

        template <typename input_class>
        void enable_eventsystem(void *conf = nullptr)
        {
            _eventsystem = new input_class(conf);
        }

        template <typename sound_class>
        void enable_soundsystem(void *conf = nullptr)
        {
            _soundsystem = new sound_class(conf);
        }
        void enable_networksystem(Network *network) {_networksystem = network;};
        void set_cond_game_loop(bool (*ptr_func)(Game_engine *g_e));
        const void run(); //Game_loop
        void update_event();
        void update_sound();
        void update_display();
        void update_custom();
        void add_custom_func(ptr_func_custom, const std::string &name_func);
        void del_custom_func(const std::string &name_func);
        std::vector<Entity *> &get_list_entity() {return _list_entity;}
        I_Rendersystem *get_rendersystem() {return _rendersystem;}
        I_Eventsystem *get_eventsystem() {return _eventsystem;}
        I_Soundsystem *get_soundsystem() {return _soundsystem;}
        Network *get_network() {return _networksystem;}
        std::vector<std::pair<ptr_func_custom, std::string>> get_custom_func() {return _custom_function;}

    protected:
    private:
        std::vector<Entity *> _list_entity; //list D'entité du jeu
        bool (* _cond_game_loop)(Game_engine *g_e);
        std::vector<std::pair<ptr_func_custom, std::string>> _custom_function;
        I_Rendersystem *_rendersystem;
        I_Eventsystem *_eventsystem;
        Network *_networksystem;
        I_Soundsystem *_soundsystem;
};
