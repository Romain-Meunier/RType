/*
** EPITECH PROJECT, 2022
** game_running network
** File description:
** game_running_network
*/

#include <Game_engine.hpp>

std::vector<std::string> parse_string(std::string s, char delim);
std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

void update_player1(Game_engine *g_e, const std::string &line)
{
    std::vector<std::string> info_block = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    std::string x = parse_string(info_block[0], '.')[0];
    std::string y = parse_string(info_block[0], '.')[1];
    std::vector<Entity *> entity_found_from_snapshot = filter_by_name(g_e->get_list_entity(), "Bar_LEFT");
    Drawable_impl *score = filter_by_name(g_e->get_list_entity(), "Score_BLUE")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    switch (info_block[1][1])
    {
    case '1':
        score->set_texture_rect(3840, 0, 1920, 1080);
        break;
    case '2':
        score->set_texture_rect(1920, 0, 1920, 1080);
        break;
    case '3':
        score->set_texture_rect(0, 0, 1920, 1080);
        break;
    default:
        break;
    }
    entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position(std::stod(x) * 100.0 / 1920.0, std::stod(y) * 100.0 / 1080.0);
}

void update_player2(Game_engine *g_e, const std::string &line)
{
    std::vector<std::string> info_block = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    std::string x = parse_string(info_block[0], '.')[0];
    std::string y = parse_string(info_block[0], '.')[1];
    std::vector<Entity *> entity_found_from_snapshot = filter_by_name(g_e->get_list_entity(), "Bar_RIGHT");
    Drawable_impl *score = filter_by_name(g_e->get_list_entity(), "Score_RED")[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph();

    switch (info_block[1][1])
    {
    case '1':
        score->set_texture_rect(3840, 0, 1920, 1080);
        break;
    case '2':
        score->set_texture_rect(1920, 0, 1920, 1080);
        break;
    case '3':
        score->set_texture_rect(0, 0, 1920, 1080);
        break;
    default:
        break;
    }
    entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position(std::stod(x) * 100.0 / 1920.0, std::stod(y) * 100.0 / 1080.0);
}

void update_ball(Game_engine *g_e, const std::string &line)
{
    std::vector<std::string> info_block = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    std::string x = parse_string(info_block[0], '.')[0];
    std::string y = parse_string(info_block[0], '.')[1];
    std::vector<Entity *> entity_found_from_snapshot = filter_by_name(g_e->get_list_entity(), "Ball");

    entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position(std::stod(x) * 100.0 / 1920.0, std::stod(y) * 100.0 / 1080.0);
}
