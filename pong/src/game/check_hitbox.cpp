/*
** EPITECH PROJECT, 2022
** check_hitbox.cpp
** File description:
** Pong
*/

#include <Game_engine.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);
Entity *create_img_clock(const char *name_component, ...);
void victory(Game_engine *g_e);

void delete_game(Game_engine *g_e)
{
    g_e->del_custom_func("input_movement_bar");
    g_e->del_custom_func("movement_ball");
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

void increment_score_red(Game_engine *g_e)
{
    Drawable_impl *score = filter_by_name(g_e->get_list_entity(), "Score_RED")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    switch (score->get_sprite().getTextureRect().left)
    {
    case 0:
        delete_game(g_e);
        g_e->get_list_entity().push_back(create_img_clock("VICTORY", "../assets/graphic_2D/Victory_RED.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
        3.0, &victory));
        break;
    case 1920:
        score->set_texture_rect(0, 0, 1920, 1080);
        break;
    case 3840:
        score->set_texture_rect(1920, 0, 1920, 1080);
        break;
    case 7680:
        score->set_texture_rect(3840, 0, 1920, 1080);
        break;
    default:
        break;
    }
}

void increment_score_blue(Game_engine *g_e)
{
    Drawable_impl *score = filter_by_name(g_e->get_list_entity(), "Score_BLUE")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    switch (score->get_sprite().getTextureRect().left)
    {
    case 0:
        delete_game(g_e);
        g_e->get_list_entity().push_back(create_img_clock("VICTORY", "../assets/graphic_2D/Victory_BLUE.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080,
        3.0, &victory));
        break;
    case 1920:
        score->set_texture_rect(0, 0, 1920, 1080);
        break;
    case 3840:
        score->set_texture_rect(1920, 0, 1920, 1080);
        break;
    case 7680:
        score->set_texture_rect(3840, 0, 1920, 1080);
        break;
    default:
        break;
    }
}

void check_hitbox_ball_bar(const double &x, const double &y, Movement_component *mvm_ball, Game_engine *g_e)
{
    Entity *bar_left = filter_by_name(g_e->get_list_entity(), "Bar_LEFT")[0];
    Entity *bar_right = filter_by_name(g_e->get_list_entity(), "Bar_RIGHT")[0];
    sf::Vector2f position_bar_blue = bar_left->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition();
    sf::Vector2f position_bar_red = bar_right->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition();
    Sound_impl *sound_bar_left = bar_left->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0];
    Sound_impl *sound_bar_right = bar_right->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0];

    if (x + 60 < position_bar_blue.x + 60 && x + 60 > position_bar_blue.x) {
        if (y + 60 < position_bar_blue.y + 410 && y + 60 > position_bar_blue.y) {
            mvm_ball->set_vector_dir(mvm_ball->get_vector_dir().x * -1.0, mvm_ball->get_vector_dir().y);
            mvm_ball->set_speed(mvm_ball->get_speed() + 0.05);
            sound_bar_left->stop();
            sound_bar_left->play();
            return;
        }
    }
    if (x + 60 < position_bar_red.x + 60 && x + 60 > position_bar_red.x) {
        if (y + 60 < position_bar_red.y + 410 && y + 60 > position_bar_red.y) {
            mvm_ball->set_vector_dir(mvm_ball->get_vector_dir().x * -1.0, mvm_ball->get_vector_dir().y);
            mvm_ball->set_speed(mvm_ball->get_speed() + 0.05); 
            sound_bar_right->stop();
            sound_bar_right->play();
            return;
        }
    }
}

void check_hitbox_ball_wall(const double &x, const double &y, Movement_component *mvm_ball, Game_engine *g_e)
{
    Entity *ball = filter_by_name(g_e->get_list_entity(), "Ball")[0];
    Drawable_impl *ball_sprite = ball->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
    Sound_impl *ball_sound = ball->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0];

    if (x < 0) {
        g_e->get_soundsystem()->clear_sound_effect();
        g_e->get_soundsystem()->add_sound_effect("../assets/audio/goal_pong.wav");
        mvm_ball->set_position(47.0, 44.0);
        ball_sprite->set_position(47.0, 44.0);
        mvm_ball->set_vector_dir(-1.5, mvm_ball->get_vector_dir().y * -1.0);
        mvm_ball->set_speed(0.3);
        increment_score_red(g_e);
    } if (x > 1920) {
        g_e->get_soundsystem()->clear_sound_effect();
        g_e->get_soundsystem()->add_sound_effect("../assets/audio/goal_pong.wav");
        mvm_ball->set_position(47.0, 44.0);
        ball_sprite->set_position(47.0, 44.0);
        mvm_ball->set_vector_dir(1.5, mvm_ball->get_vector_dir().y * -1.0);
        mvm_ball->set_speed(0.3);
        increment_score_blue(g_e);
    }
    if (y + 160 > 1080 || y + 40 < 0) {
        mvm_ball->set_vector_dir(mvm_ball->get_vector_dir().x, mvm_ball->get_vector_dir().y * -1.0);
        ball_sound->stop();
        ball_sound->play();
    }

}
