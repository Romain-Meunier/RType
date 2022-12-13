/*
** EPITECH PROJECT, 2022
** custom_func_input.cpp
** File description:
** Game
*/

#include "Game_engine.hpp"

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);
std::vector<Entity *> filter_by_component(std::vector<Entity *> &list_entity, type_component type);

void send_input_to_network(Game_engine *g_e)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        g_e->get_network()->udp_write(PLAYER_INPUT, "RIGHT");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        g_e->get_network()->udp_write(PLAYER_INPUT, "LEFT");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        g_e->get_network()->udp_write(PLAYER_INPUT, "UP");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        g_e->get_network()->udp_write(PLAYER_INPUT, "DOWN");
    }
}

void up_movement(Game_engine *g_e)
{
    std::cout << "Up" << std::endl;
    Drawable_impl *player = filter_by_component(g_e->get_list_entity(), INPUT_C)[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    switch (player->get_sprite().getTextureRect().left)
    {
    case 0:
        player->set_texture_rect(33, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    case 33:
        player->set_texture_rect(66, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    case 66:
        player->set_texture_rect(99, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    case 99:
        player->set_texture_rect(132, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    default:
        break;
    }
}

void down_movement(Game_engine *g_e)
{
    std::cout << "Down" << std::endl;
    Drawable_impl *player = filter_by_component(g_e->get_list_entity(), INPUT_C)[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    switch (player->get_sprite().getTextureRect().left)
    {
    case 33:
        player->set_texture_rect(0, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    case 66:
        player->set_texture_rect(33, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    case 99:
        player->set_texture_rect(66, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    case 132:
        player->set_texture_rect(99, player->get_sprite().getTextureRect().top, 33, 16);
        break;
    default:
        break;
    }
}

void shoot_bullet(Game_engine *g_e)
{
    Clock_component *clock_comp;
    std::vector<Entity *> clock_entity;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        std::cout << "Space" << std::endl;
        
        g_e->get_network()->udp_write(PLAYER_INPUT, "SHOOT");
        clock_entity = filter_by_component(g_e->get_list_entity(), CLOCK_C);
        for (int i = 0; i < clock_entity.size(); i++) {
            if (clock_entity[i]->get_name_type().compare(0, 6, "PLAYER") == 0)
                clock_comp = clock_entity[i]->get_component<Clock_component>(CLOCK_C);
        }
        clock_comp->restart_time();
    }
}

void swap_weapon_action(Game_engine *g_e)
{
    g_e->get_network()->udp_write(PLAYER_INPUT, "SWAP_WEAPON");
    std::vector<Entity *> HUD_weapon_entity = filter_by_name(g_e->get_list_entity(), "HUD_weapon");
    if (HUD_weapon_entity.size() != 0)
    {
        if (HUD_weapon_entity[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->get_string().compare("Current weapon: Blaster\nPress X to swap") == 0)
        {
            HUD_weapon_entity[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->set_text("Current weapon: Electric-Surcharge\nPress X to swap");
        }
        else if (HUD_weapon_entity[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->get_string().compare("Current weapon: Electric-Surcharge\nPress X to swap") == 0)
        {
            HUD_weapon_entity[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->set_text("Current weapon: Barrage\nPress X to swap");
        }
        else if (HUD_weapon_entity[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->get_string().compare("Current weapon: Barrage\nPress X to swap") == 0)
        {
            HUD_weapon_entity[0]->get_component<Text_component>(TEXT_C)->get_lib_text()->set_text("Current weapon: Blaster\nPress X to swap");
        }
        
    }
}