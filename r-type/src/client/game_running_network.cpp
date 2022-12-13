/*
** EPITECH PROJECT, 2022
** game_running_network.cpp
** File description:
** client
*/

#include <Game_engine.hpp>

Entity *create_drawable(const char *name_component, ...);
Entity *create_img_clock(const char *name_component, ...);
Entity *create_img_clock_sound(const char *name_component, const unsigned int nbr_sound, ...);
Entity *create_drawable_sound(const char *name_component, const unsigned int nbr_sound, ...);
Entity *create_clock(const char *name_component, ...);

std::vector<Entity *> filter_by_rfind_name(std::vector<Entity *> &list_entity, const std::string &name);
std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);
std::vector<std::string> parse_string(std::string s, char delim);

void button_play_default(Game_engine *g_e);
void button_play_pressed(Game_engine *g_e);
void button_play_overlay(Game_engine *g_e);
void button_play_released(Game_engine *g_e);

void button_settings_default(Game_engine *g_e);
void button_settings_pressed(Game_engine *g_e);
void button_settings_overlay(Game_engine *g_e);
void button_settings_released(Game_engine *g_e);

void explosion_anim(Game_engine *g_e);
void electric_bullet_anim(Game_engine *g_e);
void lvl2_transition(Game_engine *g_e);

void delete_all_bullet_vect(std::vector<Entity *> bullet_list, int size_vector_bullet, Game_engine *g_e)
{
    for (int i = 0; i < g_e->get_list_entity().size() && bullet_list.size() > 0; i++)
    {
        if (bullet_list[0]->get_name_type().compare(g_e->get_list_entity()[i]->get_name_type()) == 0) {
            delete g_e->get_list_entity()[i];
            g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
            bullet_list.erase(bullet_list.begin());
        }
    }
    return;
}

void delete_bullet_vect_from_snapshot(std::string type, std::string line, Game_engine *g_e)
{
    int size_vector_bullet = atoi(parse_string(parse_string(line, '/')[1], ':')[0].c_str());
    std::vector<std::string> coord_parsed;
    std::vector<std::string> id_bullet;
    std::vector<Entity *> bullet_list = filter_by_rfind_name(g_e->get_list_entity(), type);
    bool exist = false;

    // std::cout << "FADOLI:" << parse_string(parse_string(line, '/')[1], ':')[0].c_str() << "µ\n";
    if (size_vector_bullet == 0) {
        delete_all_bullet_vect(bullet_list, size_vector_bullet, g_e);
        return;
    }
    coord_parsed = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    for (auto it : bullet_list)
    {
        for (int i = 0 ; i < size_vector_bullet && exist == false; i++)
        {
            id_bullet = parse_string(coord_parsed[i], '*');
            if (it->get_name_type().compare(type + id_bullet[0]) == 0)
                exist = true;
        }
        if (exist == false) {
            for (int i = 0; i < g_e->get_list_entity().size(); i++)
            {
                if (it->get_name_type().compare(g_e->get_list_entity()[i]->get_name_type()) == 0) {
                    delete g_e->get_list_entity()[i];
                    g_e->get_list_entity().erase(g_e->get_list_entity().begin() + i);
                }
            }
        }
        exist = false;
    }
}

void update_bullet_vect_from_snapshot(std::string type, std::string line, Game_engine *g_e)
{
    std::vector<Entity *> bullets;
    std::vector<std::string> coord;
    std::vector<std::string> id_bullet;
    int size_vector_bullet = atoi(parse_string(parse_string(line, '/')[1], ':')[0].c_str());
    std::vector<std::string> coord_parsed;
    
    if (size_vector_bullet > 0)
        coord_parsed = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    for (int i = 0 ; i < size_vector_bullet ; i++)
    {
        id_bullet = parse_string(coord_parsed[i], '*');
        if (id_bullet[0].c_str()[0] == '0')
            continue;
        coord = parse_string(id_bullet[1], '.');
        bullets = filter_by_name(g_e->get_list_entity(), std::string(type + id_bullet[0]).c_str());

        if (bullets.size() == 0)
        {
            if (type.compare("B_BLASTER_ALLY") == 0) {
                g_e->get_list_entity().push_back(create_drawable_sound(std::string(type + id_bullet[0]).c_str(), 1, "../assets/graphic_2D/shoot.png", std::stod(coord[0]) * 100.0/1920.0,  std::stod(coord[1]) * 100.0/1080.0, 2.0, 2.0, 0, 0, 0, 60, 30,
                "../assets/audio/Blastershot.wav", 30.0));
            } if (type.compare("B_ROCKET_MOB") == 0) {
                g_e->get_list_entity().push_back(create_drawable_sound(std::string(type + id_bullet[0]).c_str(), 1, "../assets/graphic_2D/shoot_mob.png", std::stod(coord[0]) * 100.0/1920.0,  std::stod(coord[1]) * 100.0/1080.0, 2.0, 2.0, 0, 0, 0, 60, 30,
                "../assets/audio/TIEshot.wav", 75.0));
            } if (type.compare("B_OMNI") == 0) {
                g_e->get_list_entity().push_back(create_drawable_sound(std::string(type + id_bullet[0]).c_str(), 1, "../assets/graphic_2D/bullet_omni.png", std::stod(coord[0]) * 100.0/1920.0,  std::stod(coord[1]) * 100.0/1080.0, 0.2, 0.2, 0, 0, 0, 140, 140,
                "../assets/audio/Omnishot.wav", 50.0));
            } if (type.compare("B_BARRAGE_ALLY") == 0) {
                g_e->get_list_entity().push_back(create_drawable_sound(std::string(type + id_bullet[0]).c_str(), 1, "../assets/graphic_2D/barrage.png", std::stod(coord[0]) * 100.0/1920.0,  std::stod(coord[1]) * 100.0/1080.0, 0.75, 0.75, 0, 0, 0, 77, 163,
                "../assets/audio/Barrageshot.wav", 30.0));
            } if (type.compare("B_ELECTRIC_ALLY") == 0) {
                g_e->get_list_entity().push_back(create_img_clock_sound(std::string(type + id_bullet[0]).c_str(), 1, "../assets/graphic_2D/bullet_electric.png", std::stod(coord[0]) * 100.0/1920.0,  std::stod(coord[1]) * 100.0/1080.0, 1.0, 1.0, 0, 0, 0, 63, 61,
                0.10, &electric_bullet_anim,
                "../assets/audio/Electricityshot.wav", 30.0));
            }
            g_e->get_list_entity().back()->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
        }
        else
        {
            bullets[0]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position(std::stod(coord[0]) * 100.0/1920.0, std::stod(coord[1]) * 100.0/1080.0);
        }
    }
}

void update_entity_state_from_snapshot(std::string info_block, std::string type, std::string id, Game_engine *g_e)
{
    info_block.erase(0, 1);
    int state = stoi(info_block);
    std::vector<Entity *> &tmp_list = g_e->get_list_entity();
    std::string id_of_entity;

    if (state == 2)
    {
        for (int i = 0; i < tmp_list.size();) {
            if (tmp_list[i]->get_name_type().compare(type + id) == 0) {

                //getting mob type without ID
                if (tmp_list[i]->get_name_type().rfind("MINIBOSS", 0, 8) == 0)
                {
                    g_e->get_soundsystem()->del_music("Miniboss_music");
                    g_e->get_soundsystem()->add_music("../assets/audio/Lvl2_music.wav", "Lvl2_music");
                    g_e->get_soundsystem()->start_playlist();
                    g_e->get_list_entity().push_back(create_clock("Lvl2_transition", 60.0, &lvl2_transition));

                }
                if (tmp_list[i]->get_name_type().rfind("BOSS", 0, 4) == 0)
                {
                    
                    return;
                }

                for (int u = 0 ; u < tmp_list[i]->get_name_type().size() ; u++)
                {
                    if (tmp_list[i]->get_name_type()[u] <= '9' && tmp_list[i]->get_name_type()[u] >= '0')
                    {
                        id_of_entity += tmp_list[i]->get_name_type()[u];
                    }
                }
                g_e->get_list_entity().push_back(create_img_clock_sound(std::string("Explosion" + id_of_entity).c_str(), 1, "../assets/graphic_2D/explose.png", tmp_list[i]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().x * 100.0/1920.0, tmp_list[i]->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->get_sprite().getPosition().y * 100.0/1080.0, 1.5, 1.5, 0, 0, 0, 66, 61,
                0.05, &explosion_anim,
                "../assets/audio/Explosion.wav", 30.0));
                g_e->get_list_entity().back()->get_component<Sound_component>(SOUND_C)->get_lib_sound()[0]->play();
                delete tmp_list[i];
                tmp_list.erase(tmp_list.begin() + i);
            } else {
                i++;
            }
        }
    }
}

void update_entity_pos_from_snapshot(std::string info_block, std::string type, Entity *entity)
{
    std::string x = parse_string(info_block, '.')[0];
    std::string y = parse_string(info_block, '.')[1];

    entity->get_component<Drawable_component>(DRAWABLE_C)->get_lib_graph()->set_position(std::stod(x) * 100.0 / 1920.0, std::stod(y) * 100.0 / 1080.0);
}

void create_entity_from_snapshot(Game_engine *g_e, std::string type, std::string id, std::string info_block)
{
    std::string x = parse_string(info_block, '.')[0];
    std::string y = parse_string(info_block, '.')[1];

    if (type.compare("Kamikaze") == 0) {
        g_e->get_list_entity().push_back(create_drawable(std::string(std::string("Kamikaze") + id).c_str(), "../assets/graphic_2D/ship_KAMIKAZE.png", std::stod(x) * 100.0/1920.0, std::stod(y) * 100.0/1080.0, 1.0, 1.0, 0, 0, 0, 200, 100));
    }
    if (type.compare("TIEHunter") == 0)
        g_e->get_list_entity().push_back(create_drawable(std::string(std::string("TIEHunter") + id).c_str(), "../assets/graphic_2D/ship_TIE.png", std::stod(x) * 100.0/1920.0, std::stod(y) * 100.0/1080.0, 1.0, 1.0, 0, 0, 0, 200, 100));
    if (type.compare("MINIBOSS") == 0)
        g_e->get_list_entity().push_back(create_drawable(std::string(std::string("MINIBOSS") + id).c_str(), "../assets/graphic_2D/miniBoss.png", std::stod(x) * 100.0/1920.0, std::stod(y) * 100.0/1080.0, 1.0, 1.0, 0, 0, 0, 100, 120));
    if (type.compare("BOSS") == 0)
        g_e->get_list_entity().push_back(create_drawable(std::string(std::string("BOSS") + id).c_str(), "../assets/graphic_2D/bigBoss.png", std::stod(x) * 100.0/1920.0, std::stod(y) * 100.0/1080.0, 1.0, 1.0, 0, 0, 0, 190, 160));

}

void update_entity_from_snapshot(std::string type, std::string line, Game_engine *g_e)
{
    std::vector<std::string> info_block_list = parse_string(parse_string(parse_string(line, '/')[1], ':')[1], '|');
    std::string id = parse_string(parse_string(line, '/')[1], ':')[0];
    std::vector<Entity *> entity_found_from_snapshot;

    if (id.c_str()[0] == '0')
        return;
    if (info_block_list[1][1] == '2')
    {
        update_entity_state_from_snapshot(info_block_list[1], type, id, g_e);
    }
    else
    {
        entity_found_from_snapshot = filter_by_name(g_e->get_list_entity(), std::string(type + id).c_str());
        if (entity_found_from_snapshot.size() == 0)
            create_entity_from_snapshot(g_e, type, id, info_block_list[0]);
        else
            update_entity_pos_from_snapshot(info_block_list[0], type, entity_found_from_snapshot[0]);
    }
}

void update_game_from_snapshot(std::string type, std::string line, Game_engine *g_e)
{
    // std::cout << "LINE: " << line << std::endl;
    if (type.rfind("B_", 0) == 0)
    {
        delete_bullet_vect_from_snapshot(type, line, g_e);
        update_bullet_vect_from_snapshot(type, line, g_e);
    }
    else
    {
        update_entity_from_snapshot(type, line, g_e);
    }
}