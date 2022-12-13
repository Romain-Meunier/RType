/*
** EPITECH PROJECT, 2022
** interpolation.cpp
** File description:
** r-type
*/

#include <Game_engine.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);
std::vector<std::string> parse_string(std::string s, char delim);

void interpolation_bullet(std::string type, std::string line, Game_engine *g_e)
{
    std::vector<Entity *> bullets;
    std::vector<std::string> coord;
    std::vector<std::string> id_bullet;
    int size_vector_bullet = atoi(parse_string(parse_string(line, '/')[1], ':')[0].c_str());
    std::vector<std::string> coord_parsed;
    int move_x = 0;
    int move_y = 0;
    int speed = 0;
    
    if (size_vector_bullet > 0)
        coord_parsed = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    for (int i = 0 ; i < size_vector_bullet ; i++)
    {
        id_bullet = parse_string(coord_parsed[i], '*');
        coord = parse_string(id_bullet[1], '.');
        bullets = filter_by_name(g_e->get_list_entity(), std::string(type + id_bullet[0]).c_str());
        speed = 0;
        if (bullets.size() > 0)
        {
            if (bullets[0]->get_name_type().compare(0, 15, "B_ELECTRIC_ALLY") == 0) {
                speed = 2;
            } else if (bullets[0]->get_name_type().compare(0, 14, "B_BLASTER_ALLY") == 0)
                speed = 10;
            else if (bullets[0]->get_name_type().compare(0, 14, "B_BARRAGE_ALLY") == 0)
                speed = 30;
            else
                speed = 5;
            if (std::stod(coord[0]) - bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x > speed)
                move_x = speed;
            else if (std::stod(coord[0]) - bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x < speed * -1)
                move_x = speed * -1;
            else
               move_x = std::stod(coord[0]) - bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x;
            if (std::stod(coord[1]) - bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y > speed)
               move_y = speed;
            else if (std::stod(coord[1]) - bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y < speed * -1)
               move_y = speed * -1;
           else
               move_y = std::stod(coord[1]) - bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y;
           bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_move(move_x, move_y);
        }
    }
}

void interpolation_entity(std::string type, std::string line, Game_engine *g_e)
{
    std::vector<std::string> info_block_list = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    std::string id = parse_string(parse_string(line, '/')[1], ':')[0];
    std::vector<Entity *> entity_found_from_snapshot;
    std::string x = parse_string(info_block_list[0], '.')[0];
    std::string y = parse_string(info_block_list[0], '.')[1];
    int move_x = 0;
    int move_y = 0;

    entity_found_from_snapshot = filter_by_name(g_e->get_list_entity(), std::string(type + id).c_str());
    if (entity_found_from_snapshot.size() > 0) {
        if (std::stod(x) - entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x > 2)
            move_x = 2;
        else if (std::stod(x) - entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x < -2)
            move_x = -2;
        else
            move_x = std::stod(x) - entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x;
        if (std::stod(y) - entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y > 2)
            move_y = 2;
        else if (std::stod(y) - entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y < -2)
            move_y = -2;
        else
            move_y = stod(y) - entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y;
            
        entity_found_from_snapshot[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_move(move_x, move_y);
    }
}

void interpolation(std::string type, std::string line, Game_engine *g_e)
{
    if (type.rfind("B_", 0) == 0)
    {
        interpolation_bullet(type, line, g_e);
    }
    else
    {
        interpolation_entity(type, line, g_e);
    }
}

void interpolation_game_loop(Game_engine *g_e)
{
    std::vector<std::string> raw_msg_parsed = parse_string(parse_string(g_e->get_network()->getLastestSnapshot(), '$')[1], '\n');

    for (auto line : raw_msg_parsed)
    {
        for (auto type : map_of_type)
        {
            if (type.first.compare(parse_string(line, '/')[0]) == 0) 
            {
                if (!g_e->get_list_entity().empty())
                    interpolation(type.first, line, g_e);
            }
        }
    }
}
