/*
** EPITECH PROJECT, 2022
** condition_game_loop.cpp
** File description:
** Game
*/

#include <Game_engine.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

void check_hitbox_ball_bar(const double &x, const double &y, Movement_component *mvm_ball, Game_engine *g_e);
void check_hitbox_ball_wall(const double &x, const double &y, Movement_component *mvm_ball, Game_engine *g_e);

void movement_ball(Game_engine *g_e);
void input_movement_bar(Game_engine *g_e);

Entity *create_bar(const char *name_component, const unsigned int nbr_sound, ...);
Entity *create_ball(const char *name_component, const unsigned int nbr_sound, ...);
Entity *create_drawable(const char *name_component, ...);
Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);

void button_default(Game_engine *g_e);
void button_pressed(Game_engine *g_e);
void button_overlay(Game_engine *g_e);
void button_start_released(Game_engine *g_e);

bool default_loop(Game_engine *g_e)
{
    return true;
}

void chrono_start(Game_engine *g_e)
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
        for (int i = 0; i < list_tmp.size(); i++) {
            if (list_tmp[i]->get_name_type().compare("Chrono") == 0) {
                delete list_tmp[i];
                list_tmp.erase(list_tmp.begin() + i);
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
        g_e->add_custom_func(&input_movement_bar, "input_movement_bar");
        g_e->add_custom_func(&movement_ball, "movement_ball");
        return;
    default:
        break;
    }
    chrono->get_component<Clock_component>(CLOCK_C)->restart_time();
}

void victory(Game_engine *g_e)
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
    g_e->get_list_entity().push_back(create_button("Play_button", 0, "../assets/graphic_2D/Button_play.png", 30.0, 30.0, 1.0, 1.0, 0, 0, 0, 800, 400,
    30.0, 32.0, 40.0, 30.0, &button_pressed, &button_start_released, &button_overlay, &button_default));
}

void movement_ball(Game_engine *g_e)
{
    std::vector<Entity *> ball = filter_by_name(g_e->get_list_entity(), "Ball");
    Movement_component *mvm_ball;
    double next_x = 0.0;
    double next_y = 0.0;

    if (ball.empty())
        return;
    mvm_ball = ball[0]->get_component<Movement_component>(MOVEMENT_C);
    next_x = mvm_ball->get_position().x + mvm_ball->get_vector_dir().x * mvm_ball->get_speed();
    next_y = mvm_ball->get_position().y + mvm_ball->get_vector_dir().y * mvm_ball->get_speed();
    mvm_ball->set_position(next_x, next_y);
    ball[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position(next_x, next_y);
    check_hitbox_ball_bar(next_x * 1920 / 100, next_y * 1080 / 100, mvm_ball, g_e);
    check_hitbox_ball_wall(next_x * 1920 / 100, next_y * 1080 / 100, mvm_ball, g_e);
}