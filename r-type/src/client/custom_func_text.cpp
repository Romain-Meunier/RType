/*
** EPITECH PROJECT, 2022
** custom_func_text.cpp
** File description:
** Game
*/

#include "Game_engine.hpp"
#include <cstdarg>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);
Entity *create_img_clock(const char *name_component, ...);

void delete_enter_text_nameroom(Game_engine *g_e)
{
    std::vector<Entity *> &list_entity = g_e->get_list_entity();

    g_e->get_eventsystem()->del_custom_event("enter_text_nameroom");
    for (int i = 0; i < list_entity.size(); i++) {
        if (list_entity[i]->get_name_type().compare("Space_bar_name_room") == 0) {
            delete list_entity[i];
            list_entity.erase(list_entity.begin() + i);
            return;
        }
    }
}

void set_position_space_bar_room(Game_engine *g_e, sf::Vector2f pos)
{
    std::vector<Entity *> entity_space_bar_room = filter_by_name(g_e->get_list_entity(), "Space_bar_name_room");

    entity_space_bar_room[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position((pos.x + 5) * 100 / 1920, (pos.y - 2) * 100 / 1080);
}

void enter_text_nameroom(Game_engine *g_e)
{
    event_t &event = g_e->get_eventsystem()->get_event();
    std::vector<Entity *> entity_nameroom = filter_by_name(g_e->get_list_entity(), "Name_Room");
    Text_impl *text;
    std::string str_text;

    if (entity_nameroom.size() != 1) {
        delete_enter_text_nameroom(g_e);
        return;
    }
    text = entity_nameroom[0]->get_component<Text_component>(TEXT_C)->get_lib_text();
    str_text = text->get_string();
    switch (event.type) {
        case sf::Event::TextEntered:
            if (event.text.unicode < 128 && event.text.unicode != 8) {
                str_text.push_back(static_cast<char>(event.text.unicode));
            } else if (event.text.unicode == 8 && !str_text.empty()) {
                str_text.erase(str_text.end() - 1);
            } else {}
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Enter) {
                delete_enter_text_nameroom(g_e);
                return;
            } else if (event.key.code == sf::Keyboard::Escape) {
                delete_enter_text_nameroom(g_e);
                return;
            } else {}
        default:
            break;
    }
    text->set_text(str_text.c_str());
    if (text->get_text().findCharacterPos(str_text.size()).x >= 1165) {
        str_text.erase(str_text.end() - 1);
        text->set_text(str_text.c_str());
    }
    set_position_space_bar_room(g_e, text->get_text().findCharacterPos(str_text.size()));
}

void clock_space_bar_room(Game_engine *g_e)
{
    Entity *space_bar = filter_by_name(g_e->get_list_entity(), "Space_bar_name_room")[0];
    Drawable_impl *space_bar_s = space_bar->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    if (space_bar_s->get_sprite().getColor() == sf::Color::White) {
        space_bar_s->set_color(sf::Color::Transparent);
    } else {
        space_bar_s->set_color(sf::Color::White);
    }
    space_bar->get_component<Clock_component>(CLOCK_C)->restart_time();
}

void nameroom_default(Game_engine *g_e)
{
    // std::cout << "Default" << std::endl;
}

void nameroom_pressed(Game_engine *g_e)
{
    // std::cout << "Pressed" << std::endl;
}

void nameroom_overlay(Game_engine *g_e)
{
    // std::cout << "Overlay" << std::endl;
}

void nameroom_released(Game_engine *g_e)
{
    // std::cout << "Released" << std::endl;
    if (filter_by_name(g_e->get_list_entity(), "Space_bar_name_room").size() == 0) {
        g_e->get_eventsystem()->add_custom_event(&enter_text_nameroom, "enter_text_nameroom");
        g_e->get_list_entity().push_back(create_img_clock("Space_bar_name_room", "../assets/graphic_2D/Space_bar.png", 41.0, 40.0, 1.0, 1.0, 0, 0, 0, 4, 44,
        0.5, &clock_space_bar_room));
    }
}