/*
** EPITECH PROJECT, 2022
** custom_func_input.cpp
** File description:
** PONG
*/

#include <Game_engine.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

void input_movement_bar_multi(Game_engine *g_e)
{
    Drawable_impl *tmp_graph;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        tmp_graph = filter_by_name(g_e->get_list_entity(), "Bar_RIGHT")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
        if (tmp_graph->get_sprite().getPosition().y > -10)
            g_e->get_network()->udp_write(PLAYER_INPUT, "UP");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        tmp_graph = filter_by_name(g_e->get_list_entity(), "Bar_RIGHT")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
        if (tmp_graph->get_sprite().getPosition().y + 410 < 1080)
            g_e->get_network()->udp_write(PLAYER_INPUT, "DOWN");
    }
}


void input_movement_bar(Game_engine *g_e)
{
    Drawable_impl *tmp_graph;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        tmp_graph = filter_by_name(g_e->get_list_entity(), "Bar_LEFT")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
        if (tmp_graph->get_sprite().getPosition().y > -10)
            tmp_graph->set_move(0, -8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        tmp_graph = filter_by_name(g_e->get_list_entity(), "Bar_LEFT")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
        if (tmp_graph->get_sprite().getPosition().y + 410 < 1080)
            tmp_graph->set_move(0, 8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        tmp_graph = filter_by_name(g_e->get_list_entity(), "Bar_RIGHT")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
        if (tmp_graph->get_sprite().getPosition().y > -10)
            tmp_graph->set_move(0, -8);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        tmp_graph = filter_by_name(g_e->get_list_entity(), "Bar_RIGHT")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();
        if (tmp_graph->get_sprite().getPosition().y + 410 < 1080)
            tmp_graph->set_move(0, 8);
    }
}
