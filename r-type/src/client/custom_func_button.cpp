/*
** EPITECH PROJECT, 2022
** custom_func_button.cpp
** File description:
** Game
*/

#include "Game_engine.hpp"
#include <cstdarg>

Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);
Entity *create_drawable(const char *name_component, ...);
Entity *create_chat(const char *name_component, ...);

void button_join_default(Game_engine *g_e);
void button_join_pressed(Game_engine *g_e);
void button_join_overlay(Game_engine *g_e);
void button_join_released(Game_engine *g_e);

void button_create_default(Game_engine *g_e);
void button_create_pressed(Game_engine *g_e);
void button_create_overlay(Game_engine *g_e);
void button_create_released(Game_engine *g_e);

void button_disconnect_default(Game_engine *g_e);
void button_disconnect_pressed(Game_engine *g_e);
void button_disconnect_overlay(Game_engine *g_e);
void button_disconnect_released(Game_engine *g_e);

void button_play_default(Game_engine *g_e);
void button_play_pressed(Game_engine *g_e);
void button_play_overlay(Game_engine *g_e);
void button_play_released(Game_engine *g_e);

void button_settings_default(Game_engine *g_e);
void button_settings_pressed(Game_engine *g_e);
void button_settings_overlay(Game_engine *g_e);
void button_settings_released(Game_engine *g_e);

void nameroom_default(Game_engine *g_e);
void nameroom_pressed(Game_engine *g_e);
void nameroom_overlay(Game_engine *g_e);
void nameroom_released(Game_engine *g_e);

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

/// @brief START BUTTON
/// @param own_entity 
/// @param list_entity 
void button_start_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Start");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_start_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Start");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_start_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Start");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_start_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;

    if (g_e->get_network()->connect() == 0) {
        g_e->get_list_entity().push_back(create_chat("Name_Room", "../assets/graphic_2D/room_name.png", 40.0, 40.0, 1.0, 1.0, 0, 0, 0, 400, 50,
            40.0, 40.0, 20.8, 4.6, &nameroom_pressed, &nameroom_released, &nameroom_overlay, &nameroom_default,
            "../assets/font/Retro_Gaming.ttf", "", 40.5, 40.5, 1, 1, 0));
        g_e->get_list_entity().push_back(create_button("Join", 2, "../assets/graphic_2D/button_Join.png", 17.0, 60.0, 2.0, 2.0, 0, 0, 0, 200, 100,
            17.0, 60.0, 20.833, 18.518, &button_join_pressed, &button_join_released, &button_join_overlay, &button_join_default,
            "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
        g_e->get_list_entity().push_back(create_button("Create", 2, "../assets/graphic_2D/button_Create.png", 39.5, 60.0, 2.0, 2.0, 0, 0, 0, 200, 100,
            39.5, 60.0, 20.833, 18.518, &button_create_pressed, &button_create_released, &button_create_overlay, &button_create_default,
            "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
        g_e->get_list_entity().push_back(create_button("Disconnect", 2, "../assets/graphic_2D/button_Home.png", 62.0, 60.0, 2.0, 2.0, 0, 0, 0, 200, 100,
            62.0, 60.0, 20.833, 18.518, &button_disconnect_pressed, &button_disconnect_released, &button_disconnect_overlay, &button_disconnect_default,
            "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
        for (int i = 0; i < g_e->get_list_entity().size();)
        {
            if (g_e->get_list_entity()[i]->get_name_type().compare("Exit") == 0 ||
                g_e->get_list_entity()[i]->get_name_type().compare("Start") == 0) {
                delete g_e->get_list_entity().at(i);
                g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
            } else {
                i++;
            }
        }
    }
}
/// @endif

/// @brief EXIT BUTTON
/// @param own_entity 
/// @param list_entity

void button_exit_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Exit");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_exit_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Exit");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_exit_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Exit");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_exit_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;

    g_e->get_rendersystem()->close_wdw();
}
/// @endif

/// @brief JOIN BUTTON
/// @param own_entity 
/// @param list_entity

void button_join_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Join");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_join_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Join");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_join_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Join");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_join_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;
    g_e->get_network()->tcp_write("join", filter_by_name(g_e->get_list_entity(), "Name_Room")[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->get_string());
}
/// @endif

/// @brief CREATE BUTTON
/// @param own_entity 
/// @param list_entity

void button_create_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Create");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_create_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Create");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_create_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Create");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_create_released(Game_engine *g_e)
{
    std::cout << "Released" << std::endl;
    g_e->get_network()->tcp_write("create", filter_by_name(g_e->get_list_entity(), "Name_Room")[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->get_string());
}
/// @endif

/// @brief DISCONNECT BUTTON
/// @param own_entity 
/// @param list_entity

void button_disconnect_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Disconnect");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_disconnect_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Disconnect");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_disconnect_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Disconnect");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_disconnect_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;

    g_e->get_list_entity().push_back(create_button("Start", 2, "../assets/graphic_2D/button_Start.png", 39.75, 38.0, 2.0, 2.0, 0, 0, 0, 200, 100,
        39.75, 38.0, 20.832, 18.518, &button_start_pressed, &button_start_released, &button_start_overlay, &button_start_default,
        "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
    g_e->get_list_entity().push_back(create_button("Exit", 2, "../assets/graphic_2D/button_Exit.png", 44.791, 67.5, 1.0, 1.0, 0, 0, 0, 200, 100,
        44.791, 67.5, 10.416, 9.259, &button_exit_pressed, &button_exit_released, &button_exit_overlay, &button_exit_default,
        "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
    for (int i = 0; i < g_e->get_list_entity().size();)
    {
        if (g_e->get_list_entity()[i]->get_name_type().compare("Join") == 0 || 
            g_e->get_list_entity()[i]->get_name_type().compare("Create") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Disconnect") == 0 ||
            g_e->get_list_entity()[i]->get_name_type().compare("Name_Room") == 0) {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
        } else {
            i++;
        }
    }
}
/// @endif

/// @brief PLAY BUTTON
/// @param own_entity 
/// @param list_entity

void button_play_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Play");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_play_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Play");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_play_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Play");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_play_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;

    g_e->get_network()->udp_write(LAUNCH_GAME, "Start game");
}
/// @endif

/// @brief SETTINGS BUTTON
/// @param own_entity 
/// @param list_entity

void button_settings_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Settings");

    if (own_entity.size() == 1)
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(0, 0, 200, 100);
}

void button_settings_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Settings");

    if (own_entity.size() == 1) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_texture_rect(400, 0, 200, 100);
    }
}

void button_settings_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
    std::vector<Entity *> own_entity = filter_by_name(g_e->get_list_entity(), "Settings");
    Drawable_impl *tmp_drawable = own_entity[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (tmp_drawable->get_sprite().getTextureRect().left != 200) {
        own_entity[0]->get_component<Sound_component>(SOUND_C)->get_lib_sound()[1]->play();
        tmp_drawable->set_texture_rect(200, 0, 200, 100);
    }
}

void button_settings_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;
}
/// @endif