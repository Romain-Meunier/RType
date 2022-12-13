/*
** EPITECH PROJECT, 2022
** custom_func_input.cpp
** File description:
** Game
*/

#include <Game_engine.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);
std::vector<Entity *> filter_by_rfind_name(std::vector<Entity *> &list_entity, const std::string &name);
void check_change_state(Game_engine *g_e);

void button_play_default(Game_engine *g_e);
void button_play_pressed(Game_engine *g_e);
void button_play_overlay(Game_engine *g_e);
void button_play_released(Game_engine *g_e);

void button_settings_default(Game_engine *g_e);
void button_settings_pressed(Game_engine *g_e);
void button_settings_overlay(Game_engine *g_e);
void button_settings_released(Game_engine *g_e);

Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);
Entity *create_drawable(const char *name_component, ...);


void move_background_parallax(Game_engine *g_e)
{
    Drawable_impl *background_first = filter_by_name(g_e->get_list_entity(), "Background_lobby")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
    Drawable_impl *background_second = filter_by_name(g_e->get_list_entity(), "Background_parralax")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (background_second->get_sprite().getPosition().x <= 0) {
        background_first->set_position(0.0, 0.0);
        background_second->set_position(100.0, 0.0);
    } else {
        background_first->set_move(-1, 0);
        background_second->set_move(-1, 0);
    }
}

void r_type_win(Game_engine *g_e)
{
    for (int i = 0; i < g_e->get_list_entity().size(); i++)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("VICTORY") == 0) {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
            g_e->get_list_entity().push_back(create_drawable("Background_lobby", "../assets/graphic_2D/Menu.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080));
            g_e->get_list_entity().push_back(create_drawable("Player", "../assets/graphic_2D/r-type_spaceship.gif", 12.0, 7.0, 8.0, 8.0, 0, 66, 0, 33, 17));
            g_e->get_list_entity().push_back(create_button("Play", 2, "../assets/graphic_2D/button_Play.png", 42.5, 67.0, 2.0, 2.0, 0, 0, 0, 200, 100,
                42.5, 67.0, 20.832, 18.518, &button_play_pressed, &button_play_released, &button_play_overlay, &button_play_default,
                "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
            g_e->get_list_entity().push_back(create_button("Settings", 2, "../assets/graphic_2D/button_Settings.png", 81.0, 80.0, 1.0, 1.0, 0, 0, 0, 200, 100,
                81.0, 80.0, 10.416, 9.259, &button_settings_pressed, &button_settings_released, &button_settings_overlay, &button_settings_default,
                "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
            g_e->add_custom_func(&check_change_state, "check_change_state");
            g_e->get_soundsystem()->add_music("../assets/audio/Menu_music.wav", "Menu_music");
            g_e->get_soundsystem()->start_playlist();
            g_e->get_network()->_win_or_lose = "none";
            // g_e->get_network()->_win = true;
            // g_e->get_network()->_update.clear();
            return;
        }
    }
}

void r_type_lose(Game_engine *g_e)
{
    for (int i = 0; i < g_e->get_list_entity().size(); i++)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("GameOver") == 0) {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
            g_e->get_list_entity().push_back(create_drawable("Background_lobby", "../assets/graphic_2D/Menu.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080));
            g_e->get_list_entity().push_back(create_drawable("Player", "../assets/graphic_2D/r-type_spaceship.gif", 12.0, 7.0, 8.0, 8.0, 0, 66, 0, 33, 17));
            g_e->get_list_entity().push_back(create_button("Play", 2, "../assets/graphic_2D/button_Play.png", 42.5, 67.0, 2.0, 2.0, 0, 0, 0, 200, 100,
                42.5, 67.0, 20.832, 18.518, &button_play_pressed, &button_play_released, &button_play_overlay, &button_play_default,
                "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
            g_e->get_list_entity().push_back(create_button("Settings", 2, "../assets/graphic_2D/button_Settings.png", 81.0, 80.0, 1.0, 1.0, 0, 0, 0, 200, 100,
                81.0, 80.0, 10.416, 9.259, &button_settings_pressed, &button_settings_released, &button_settings_overlay, &button_settings_default,
                "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
            g_e->add_custom_func(&check_change_state, "check_change_state");
            g_e->get_soundsystem()->add_music("../assets/audio/Menu_music.wav", "Menu_music");
            g_e->get_soundsystem()->start_playlist();
            g_e->get_network()->_win_or_lose = "none";
            // g_e->get_network()->_update.clear();
            return;
        }
    }
}

void electric_bullet_anim(Game_engine *g_e)
{
    Clock_component *tmp;
    std::vector<Entity *> electric_bullet_vect = filter_by_rfind_name(g_e->get_list_entity(), "B_ELECTRIC_ALLY");

    for (auto bullet : electric_bullet_vect)
    {
        tmp = bullet->get_component<Clock_component>(CLOCK_C);
        if (tmp->get_time().count() >= 1)
        {
            switch (bullet->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getTextureRect().left)
            {
                case 0:
                    bullet->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(63,0,63,61);
                    break;
                case 63:
                    bullet->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(126,0,63,61);
                    break;
                case 126:
                    bullet->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(189,0,63,61);
                    break;
                case 189:
                    bullet->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0,0,63,61);
                    break;
            }
            tmp->restart_time();
        }
    }
}

void explosion_anim(Game_engine *g_e)
{
    Clock_component *tmp;
    std::vector<Entity *> explosion_vect = filter_by_rfind_name(g_e->get_list_entity(), "Explosion");

    for (auto explosion : explosion_vect)
    {
        tmp = explosion->get_component<Clock_component>(CLOCK_C);
        if (tmp->get_time().count() >= 0.05)
        {
            switch (explosion->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getTextureRect().left)
            {
                case 0:
                    explosion->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(66,0,66,61);
                    break;
                case 66:
                    explosion->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(132,0,66,61);
                    break;
                case 132:
                    explosion->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(198,0,66,61);
                    break;
                case 198:
                    for (int i = 0 ; i < g_e->get_list_entity().size() ;)
                    {
                        if (g_e->get_list_entity()[i]->get_name_type().compare(explosion->get_name_type()) == 0)
                        {
                            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
                        } else {
                            i++;
                        }
                        break;
                    }
                tmp->restart_time();
            }
        }
    }
}

void lvl1_transition(Game_engine *g_e)
{
    g_e->get_soundsystem()->del_music("Lvl1_music");
    g_e->get_soundsystem()->add_music("../assets/audio/Miniboss_music.wav", "Miniboss_music");
    g_e->get_soundsystem()->start_playlist();
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("Lvl1_transition") == 0)
        {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else {
            i++;
        }
    }
}

void lvl2_transition(Game_engine *g_e)
{
    g_e->get_soundsystem()->del_music("Lvl2_music");
    g_e->get_soundsystem()->add_music("../assets/audio/Boss_music.wav", "Boss_music");
    g_e->get_soundsystem()->start_playlist();
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("Lvl2_transition") == 0)
        {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else {
            i++;
        }
    }

}