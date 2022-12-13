/*
** EPITECH PROJECT, 2022
** custom_func_network.cpp
** File description:
** PONG
*/

#include <Game_engine.hpp>

void movement_ball(Game_engine *g_e);
std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

void button_default(Game_engine *g_e);
void button_pressed(Game_engine *g_e);
void button_overlay(Game_engine *g_e);
void button_launch_released(Game_engine *g_e);

Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);
Entity *create_drawable(const char *name_component, ...);
Entity *create_img_clock(const char *name_component, ...);
Entity *create_ball(const char *name_component, const unsigned int nbr_sound, ...);
Entity *create_bar(const char *name_component, const unsigned int nbr_sound, ...);

void input_movement_bar_multi(Game_engine *g_e);

void update_player1(Game_engine *g_e, const std::string &line);
void update_player2(Game_engine *g_e, const std::string &line);
void update_ball(Game_engine *g_e, const std::string &line);

std::vector<std::string> parse_string(std::string s, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);

    while (getline(ss, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

void switch_state_in_room(Game_engine *g_e)
{
    filter_by_name(g_e->get_list_entity(), "Background")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture("../assets/graphic_2D/Lobby_pong.jpg");
    g_e->get_list_entity().push_back(create_button("Launch_button", 0, "../assets/graphic_2D/Launch_button.png", 35.0, 60.0, 1.0, 1.0, 0, 0, 0, 612, 314,
    35.0, 60.0, 31.87, 29.07, &button_pressed, &button_launch_released, &button_overlay, &button_default));
    g_e->get_list_entity().push_back(create_drawable("Bar_LEFT", "../assets/graphic_2D/bar_blue.png", 5.0, 32.5, 3.0, 3.0, 0, 0, 0, 20, 120));
}

void waiting_in_room(Game_engine *g_e, const std::string &msg)
{
    int nbr_player_in = msg[8] - 48;

    if (nbr_player_in == 2 && filter_by_name(g_e->get_list_entity(), "Bar_RIGHT").size() == 0)
    {
        g_e->get_list_entity().push_back(create_drawable("Bar_RIGHT", "../assets/graphic_2D/bar_red.png", 93.95, 32.5, 3.0, 3.0, 0, 0, 0, 20, 120));
    }
}

void chrono_start_multi(Game_engine *g_e)
{
    Entity *chrono = filter_by_name(g_e->get_list_entity(), "Chrono")[0];
    Drawable_impl *chrono_sprite = chrono->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
    std::vector<Entity *> &list_tmp = g_e->get_list_entity();
    
    switch (chrono_sprite->get_sprite().getTextureRect().left)
    {
    case 0:
        chrono_sprite->set_texture_rect(1920, 0, 1920, 1080);
        break;
    case 1920:
        chrono_sprite->set_texture_rect(3840, 0, 1920, 1080);
        break;
    case 3840:
        chrono_sprite->set_texture_rect(5760, 0, 1920, 1080);
        break;
    case 5760:
        for (int i = 0; i < list_tmp.size();) {
            if (list_tmp[i]->get_name_type().compare("Chrono") == 0) {
                delete list_tmp[i];
                list_tmp.erase(list_tmp.begin() + i);
            } else {
                i++;
            }
        }
        list_tmp.push_back(create_drawable("Score_RED", "../assets/graphic_2D/chrono.png", 50.0, 0.0, 0.2, 0.2, 0, 7680, 0, 1920, 1080));
        list_tmp.push_back(create_drawable("Score_BLUE", "../assets/graphic_2D/chrono.png", 30.0, 0.0, 0.2, 0.2, 0, 7680, 0, 1920, 1080));
        list_tmp.push_back(create_bar("Bar_LEFT", 1, "../assets/graphic_2D/bar_blue.png", 5.0, 32.5, 3.0, 3.0, 0, 0, 0, 20, 120,
        "../assets/audio/collision_player_pong.wav", 75.0));
        list_tmp.push_back(create_bar("Bar_RIGHT", 1, "../assets/graphic_2D/bar_red.png", 93.95, 32.5, 3.0, 3.0, 0, 0, 0, 20, 120,
        "../assets/audio/collision_player_pong.wav", 75.0));
        list_tmp.push_back(create_ball("Ball", 1, "../assets/graphic_2D/ball_pong.png", 47.0, 44.0, 3.0, 3.0, 0, 0, 0, 40, 40,
        1.5, 1.0, 47.0, 44.0, 0.3,
        "../assets/audio/collision_wall_pong.wav", 75.0));
        g_e->get_soundsystem()->add_music("../assets/audio/music_in_game.wav", "music_in_game");
        g_e->get_soundsystem()->start_playlist();
        g_e->add_custom_func(&input_movement_bar_multi, "input_movement_bar_multi");
        return;
    default:
        break;
    }
    chrono->get_component<Clock_component>(CLOCK_C)->restart_time();
}

void switch_state_game_init(Game_engine *g_e)
{
    std::vector<Entity *> &list_tmp = g_e->get_list_entity();
    
    filter_by_name(list_tmp, "Background")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture("../assets/graphic_2D/Arena_Pong.jpg");
    for (int i = 0; i < list_tmp.size();) {
        if (list_tmp[i]->get_name_type().compare("Launch_button") == 0 ||
        list_tmp[i]->get_name_type().compare("Bar_LEFT") == 0 ||
        list_tmp[i]->get_name_type().compare("Bar_RIGHT") == 0) {
            delete list_tmp[i];
            list_tmp.erase(list_tmp.begin() + i);
        } else {
            i++;
        }
    }
    g_e->get_list_entity().push_back(create_img_clock("Chrono", "../assets/graphic_2D/chrono.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
    1.0, &chrono_start_multi));
    g_e->get_soundsystem()->clear_sound_effect();
    g_e->get_soundsystem()->add_sound_effect("../assets/audio/intro_start_pong.wav");
}


void switch_state_game_running(Game_engine *g_e, const std::string &msg)
{
    // PLAYER/1:100.400|!1|
    // PLAYER/2:100.400|!1|
    // BALL/1:100.400|!1|
    std::vector<std::string> raw_msg_parsed = parse_string(msg, '\n');

    update_player1(g_e, raw_msg_parsed[0]);
    update_player2(g_e, raw_msg_parsed[1]);
    update_ball(g_e, raw_msg_parsed[2]);
}

void delete_game_multi(Game_engine *g_e)
{
    g_e->del_custom_func("input_movement_bar_multi");
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("Bar_LEFT") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Bar_RIGHT") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Ball") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Score_RED") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Score_BLUE") == 0) {
            delete g_e->get_list_entity().at(i);
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else {
            i++;
        }
    }
    g_e->get_soundsystem()->clear_sound_effect();
    g_e->get_soundsystem()->add_sound_effect("../assets/audio/end_game_pong.wav");
    g_e->get_soundsystem()->del_music("music_in_game");
    
}

void victory_multi(Game_engine *g_e)
{
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("VICTORY") == 0) {
            delete g_e->get_list_entity().at(i);
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else {
            i++;
        }
    }
    filter_by_name(g_e->get_list_entity(), "Background")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture("../assets/graphic_2D/Lobby_pong.jpg");
    g_e->get_list_entity().push_back(create_button("Launch_button", 0, "../assets/graphic_2D/Launch_button.png", 35.0, 60.0, 1.0, 1.0, 0, 0, 0, 612, 314,
    35.0, 60.0, 31.87, 29.07, &button_pressed, &button_launch_released, &button_overlay, &button_default));
    g_e->get_list_entity().push_back(create_drawable("Bar_LEFT", "../assets/graphic_2D/bar_blue.png", 5.0, 32.5, 3.0, 3.0, 0, 0, 0, 20, 120));
}

void switch_state_win(Game_engine *g_e, const std::string &msg)
{
    delete_game_multi(g_e);

    if (msg[4] == '0') {
        g_e->get_list_entity().push_back(create_img_clock("VICTORY", "../assets/graphic_2D/Victory_BLUE.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
        3.0, &victory_multi));
    } else {
        g_e->get_list_entity().push_back(create_img_clock("VICTORY", "../assets/graphic_2D/Victory_RED.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
        3.0, &victory_multi));
    }
}

void check_change_state(Game_engine *g_e)
{
    Network *network = g_e->get_network();
    std::string msg;

    if (network->change_state() == 1)
    {
        msg = network->get_info();
        if (msg.compare("JOIN_ROOM") == 0) {
            switch_state_in_room(g_e);
        } else if (msg.compare(0, 7, "IN_ROOM") == 0) {
            waiting_in_room(g_e, msg);
        } else if (msg.compare(0, 9, "GAME_INIT") == 0) {
            switch_state_game_init(g_e);
        } else if (msg.compare(0, 12, "GAME_RUNNING") == 0) {
            msg = msg.substr(msg.find(":") + 1, msg.size() - msg.find(":"));
            switch_state_game_running(g_e, msg);
        } else if (msg.compare(0, 3, "WIN") == 0) {
            switch_state_win(g_e, msg);
        }
    }
}; 
