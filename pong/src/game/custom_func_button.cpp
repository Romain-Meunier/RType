/*
** EPITECH PROJECT, 2022
** custom_func_button.cpp
** File description:
** Pong
*/

#include <Game_engine.hpp>

void chrono_start(Game_engine *g_e);

Entity *create_img_clock(const char *name_component, ...);
void check_change_state(Game_engine *g_e);

void button_default(Game_engine *g_e)
{
}

void button_pressed(Game_engine *g_e)
{
}

void button_overlay(Game_engine *g_e)
{
}

void button_start_released(Game_engine *g_e)
{
    std::vector<Entity *> &list_tmp = g_e->get_list_entity();

    for (int i = 0; i < list_tmp.size(); i++)
    {
        if (list_tmp[i]->get_name_type().compare("Play_button") == 0) {
            delete list_tmp[i];
            list_tmp.erase(list_tmp.begin() + i);
        }
    }
    list_tmp.push_back(create_img_clock("Chrono", "../assets/graphic_2D/chrono.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
    1.0, &chrono_start));
    g_e->get_soundsystem()->clear_sound_effect();
    g_e->get_soundsystem()->add_sound_effect("../assets/audio/intro_start_pong.wav");
}

void button_start_multi_released(Game_engine *g_e)
{
    std::vector<Entity *> &list_tmp = g_e->get_list_entity();

    if (g_e->get_network()->connect() == 0)
    {
        for (int i = 0; i < list_tmp.size(); i++)
        {
            if (list_tmp[i]->get_name_type().compare("Play_button") == 0) {
                delete list_tmp[i];
                list_tmp.erase(list_tmp.begin() + i);
            }
        }
        g_e->add_custom_func(&check_change_state, "check_change_state");
        g_e->get_network()->tcp_write("join", "PONG");
    }
}

void button_launch_released(Game_engine *g_e)
{
    g_e->get_network()->udp_write(LAUNCH_GAME, "Start game");
}