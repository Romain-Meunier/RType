/*
** EPITECH PROJECT, 2022
** custom_func_network.cpp
** File description:
** Game
*/

#include <Game_engine.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);
Entity *create_drawable(const char *name_component, ...);
Entity *create_player(const char *name_component, const unsigned int nbr_input, const unsigned int nbr_sound, ...);
Entity *create_img_clock(const char *name_component, ...);
Entity *create_text(const char *name_component, ...);
Entity *create_clock(const char *name_component, ...);

void button_play_default(Game_engine *g_e);
void button_play_pressed(Game_engine *g_e);
void button_play_overlay(Game_engine *g_e);
void button_play_released(Game_engine *g_e);

void button_settings_default(Game_engine *g_e);
void button_settings_pressed(Game_engine *g_e);
void button_settings_overlay(Game_engine *g_e);
void button_settings_released(Game_engine *g_e);

void send_input_to_network(Game_engine *g_e);
void right_movement(Game_engine *g_e);
void left_movement(Game_engine *g_e);
void up_movement(Game_engine *g_e);
void down_movement(Game_engine *g_e);
void shoot_bullet(Game_engine *g_e);
void swap_weapon_action(Game_engine *g_e);

void update_game_from_snapshot(std::string type, std::string line, Game_engine *g_e);

void move_background_parallax(Game_engine *g_e);
void r_type_win(Game_engine *g_e);
void condition_lose(Game_engine *g_e);
void interpolation_game_loop(Game_engine *g_e);
void lvl1_transition(Game_engine *g_e);

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
    g_e->get_list_entity().push_back(create_drawable("Background_lobby", "../assets/graphic_2D/Menu.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080));
    g_e->get_list_entity().push_back(create_drawable("Player", "../assets/graphic_2D/r-type_spaceship.gif", 12.0, 7.0, 8.0, 8.0, 0, 66, 0, 33, 17));
    g_e->get_list_entity().push_back(create_button("Play", 2, "../assets/graphic_2D/button_Play.png", 42.5, 67.0, 2.0, 2.0, 0, 0, 0, 200, 100,
        42.5, 67.0, 20.832, 18.518, &button_play_pressed, &button_play_released, &button_play_overlay, &button_play_default,
        "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
    g_e->get_list_entity().push_back(create_button("Settings", 2, "../assets/graphic_2D/button_Settings.png", 81.0, 80.0, 1.0, 1.0, 0, 0, 0, 200, 100,
        81.0, 80.0, 10.416, 9.259, &button_settings_pressed, &button_settings_released, &button_settings_overlay, &button_settings_default,
        "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("Join") == 0 || 
            g_e->get_list_entity()[i]->get_name_type().compare("Create") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Disconnect") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Name_Room") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Background") == 0) {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else {
            i++;
        }
    }
}

void player_in_room(Game_engine *g_e, const std::string &msg)
{
    std::vector<Entity *> player_in = filter_by_name(g_e->get_list_entity(), "Player");
    int nbr_player_in = msg[8] - 48;
    int i = player_in.size();

    while (i < nbr_player_in)
    {
        g_e->get_list_entity().push_back(create_drawable("Player", "../assets/graphic_2D/r-type_spaceship.gif", 12.0, 7.0 + (23.5 * i), 8.0, 8.0, 0, 66, 17 * i, 33, 17));
        i++;
    }
}


void switch_state_game_init(Game_engine *g_e, std::string &msg)
{
    std::vector<std::string> raw_msg_parsed = parse_string(parse_string(msg, '$')[1], '\n');
    std::vector<std::string> coords_parsed;
    std::string name_player = "PLAYER";
    int id = g_e->get_network()->get_id() + 1;
    int state = 0;

    //deleting menu entity
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("Player") == 0 || 
            g_e->get_list_entity()[i]->get_name_type().compare("Play") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Settings") == 0) {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else if (g_e->get_list_entity()[i]->get_name_type().compare("Background_lobby") == 0) {
            g_e->get_list_entity()[i]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture("../assets/graphic_2D/sky.png");
            i++;
        } else {
            i++;
        }
    }

    //creating player
    g_e->get_list_entity().push_back(create_drawable("Background_parralax", "../assets/graphic_2D/sky.png", 100.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080));
    g_e->add_custom_func(&move_background_parallax, "move_background_parallax");
    for (int i = 0; i < raw_msg_parsed.size(); i++)
    {
        if (raw_msg_parsed[i].rfind("B_", 0) == 0)
            break;
        coords_parsed = parse_string(parse_string(parse_string(raw_msg_parsed[i], ':')[1], '|')[0], '.');
        name_player.append(std::to_string(i + 1));
        if (id == i + 1) {
            g_e->get_list_entity().push_back(create_player(name_player.c_str(), 3, 0, "../assets/graphic_2D/r-type_spaceship.gif", std::stod(coords_parsed[0]) * 100.0/1920.0, std::stod(coords_parsed[1]) * 100.0/1080.0, 3.0, 3.0, 0, 66, 17 * i, 33, 17,
            sf::Keyboard::Up, &up_movement, sf::Keyboard::Down, &down_movement, sf::Keyboard::X, &swap_weapon_action,
            0.6, &shoot_bullet));
            g_e->add_custom_func(&send_input_to_network, "send_input_to_network");
        } else {
            g_e->get_list_entity().push_back(create_drawable(name_player.c_str(), "../assets/graphic_2D/r-type_spaceship.gif", std::stod(coords_parsed[0]) * 100.0/1920.0, std::stod(coords_parsed[1]) * 100.0/1080.0, 3.0, 3.0, 0, 66, 17 * i, 33, 17));
        }
        name_player.erase(name_player.end() - 1);
    }
    //create HUD weapon
    g_e->get_list_entity().push_back(create_text("HUD_weapon", "../assets/font/Retro_Gaming.ttf", std::string("Current weapon: Blaster\nPress X to swap").c_str(), 0.0, 0.0, 1, 1, 0));
    g_e->get_soundsystem()->del_music("Menu_music");
    g_e->get_soundsystem()->add_music("../assets/audio/Lvl1_music.wav", "Lvl1_music");
    g_e->get_soundsystem()->start_playlist();
    g_e->get_list_entity().push_back(create_clock("Lvl1_transition", 60.0, &lvl1_transition));
    g_e->add_custom_func(&interpolation_game_loop, "interpolation_game_loop");
    g_e->add_custom_func(&condition_lose, "condition_lose");
}

void switch_state_game_running(Game_engine *g_e, std::string &msg)
{
    std::vector<std::string> raw_msg_parsed = parse_string(parse_string(msg, '$')[1], '\n');

    for (auto line : raw_msg_parsed)
    {
        for (auto type : map_of_type)
        {
            if (type.first.compare(parse_string(line, '/')[0]) == 0) 
            {
                if (!g_e->get_list_entity().empty())
                    update_game_from_snapshot(type.first, line, g_e);
            }
        }
    }
}

void switch_state_game_win(Game_engine *g_e)
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
    g_e->del_custom_func("interpolation_game_loop");
    g_e->get_soundsystem()->del_music("Boss_music");
    g_e->get_soundsystem()->add_sound_effect("../assets/audio/Victory.wav");

    tmp_list.push_back(create_img_clock("VICTORY", "../assets/graphic_2D/Victory.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
    3.0, &r_type_win));
}

void check_change_state(Game_engine *g_e)
{
    Network *network = g_e->get_network();
    std::string msg;

    if (network->change_state() == 1)
    {
        msg = network->get_info();
//        std::cout << "MSG: " << msg << std::endl;
        if (msg.compare("JOIN_ROOM") == 0) {
            switch_state_in_room(g_e);
        } else if (msg.compare(0, 7, "IN_ROOM") == 0) {
            player_in_room(g_e, msg);
        } else if (msg.compare(0, 9, "GAME_INIT") == 0) {
            std::cout << "GAME_INIT !\n";
            switch_state_game_init(g_e, msg);
        } else if (msg.compare(0, 12, "GAME_RUNNING") == 0) {
            msg = msg.substr(msg.find(":") + 1, msg.size() - msg.find(":"));
            switch_state_game_running(g_e, msg);
        } else if (msg.compare("WIN") == 0) {
            network->_win_or_lose = "win";
            switch_state_game_win(g_e);
        }
    }
}
