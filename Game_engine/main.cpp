/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** Game_Engine
*/

#include <Game_engine.hpp>
#include "asio.hpp"

int print_usage()
{
    std::cout << "USAGE:\n    Need to give 2 arguments when you run the binary \"./game_engine_b\"." << std::endl;
    std::cout << "    ./game_engine_b [Adress server] [Port to connect in tcp]" << std::endl;
    std::cout << "GAME_ENGINE:\n    It's an game engine create by Clement DUBOIS." << std::endl;
    return 0;
}

bool condition_game_loop_example(Game_engine *g_e)
{
    return true;
}

int main(int ac, char **av)
{
    if (ac != 3)
        return print_usage();
    asio::io_context io_context;
    Network *network = new Network(io_context, (short) atoi(av[2]), std::string(av[1]));

    Game_engine *core;
    std::vector<Entity *> list_entity;
    /////////////////////////////////////// @ingroup createS Entity
    ///////////////////////////////////////

    core = new Game_engine(list_entity, &condition_game_loop_example);

    /////////////////////////////////////// @ingroup add function custom
    ///////////////////////////////////////

    window_conf_s conf_wdw;
    conf_wdw.width = WINDOW_WIDTH;
    conf_wdw.height = WINDOW_HEIGHT;
    conf_wdw.title = (char *)"R-type";
    core->enable_rendersystem<Rendersystem>(&conf_wdw);
    core->enable_eventsystem<Eventsystem>();
    core->enable_networksystem(network);
    core->run();
    delete core;
}

