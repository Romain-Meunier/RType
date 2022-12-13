/*
** EPITECH PROJECT, 2022
** condition_game_loop.cpp
** File description:
** Game
*/

#include "Game_engine.hpp"

void r_type_lose(Game_engine *g_e);
Entity *create_img_clock(const char *name_component, ...);
std::vector<Entity *> filter_by_rfind_name(std::vector<Entity *> &list_entity, const std::string &name);

bool condition_game_loop(Game_engine *g_e)
{
    return true;
}

void condition_lose(Game_engine *g_e)
{
    std::vector<Entity *> players = filter_by_rfind_name(g_e->get_list_entity(), "PLAYER");
    
    if (players.size() == 0 && g_e->get_network()->_win_or_lose.compare("win") != 0)
    {
        std::vector<Entity *> &tmp_list = g_e->get_list_entity();
        while (tmp_list.size() > 0)
        {
            delete tmp_list[0];
            tmp_list.erase(tmp_list.begin());
        }
        g_e->del_custom_func("move_background_parallax");
        g_e->del_custom_func("send_input_to_network");
        g_e->del_custom_func("check_change_state");
        g_e->del_custom_func("condition_lose");
        while (!g_e->get_soundsystem()->get_sound().empty()) {
            delete g_e->get_soundsystem()->get_sound()[0].first;
            g_e->get_soundsystem()->get_sound().erase(g_e->get_soundsystem()->get_sound().begin());
        }
        g_e->get_soundsystem()->add_sound_effect("../assets/audio/Game_over.wav");
        tmp_list.push_back(create_img_clock("GameOver", "../assets/graphic_2D/Game_over.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
        3.0, &r_type_lose));
    }
}