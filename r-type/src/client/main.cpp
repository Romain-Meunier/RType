/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** Game_Engine
*/

#include <Game_engine.hpp>

Entity *create_drawable(const char *name_component, ...);
Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);
Entity *create_input(const char *name_component, const unsigned int nbr_arg, ...);

bool condition_game_loop(Game_engine *g_e);

void check_change_state(Game_engine *g_e);

void button_start_default(Game_engine *g_e);
void button_start_pressed(Game_engine *g_e);
void button_start_overlay(Game_engine *g_e);
void button_start_released(Game_engine *g_e);
void button_exit_default(Game_engine *g_e);
void button_exit_pressed(Game_engine *g_e);
void button_exit_overlay(Game_engine *g_e);
void button_exit_released(Game_engine *g_e);

int print_usage()
{
    std::cout << "USAGE:\n    Need to give 2 arguments when you run the binary \"./r-type_client\"." << std::endl;
    std::cout << "    ./game_engine_b [Adress server] [Port to connect in tcp]" << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    ///@note
    /*
    ///// INIT OF VECTOR ENTITY | une bonne idée serais que l'utilisateru créer ses entity avec un txt en indiquant tout depuis le txt et en le lisant on créer la liste
    /////// INIT VECTOR OF COMPONENT
    ///////// INIT COMPONENT
    */
    if (ac != 3)
        return print_usage();
    asio::io_context io_context;
    Network *network = new Network(io_context, (short) atoi(av[2]), std::string(av[1]));

    Game_engine *core;
    std::vector<Entity *> list_entity;
    /////////////////////////////////////// @ingroup createS Entity
    list_entity.push_back(create_drawable("Background", "../assets/graphic_2D/background.png", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080));
    list_entity.push_back(create_button("Start", 2, "../assets/graphic_2D/button_Start.png", 39.75, 38.0, 2.0, 2.0, 0, 0, 0, 200, 100,
        39.75, 38.0, 20.832, 18.518, &button_start_pressed, &button_start_released, &button_start_overlay, &button_start_default,
        "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
    list_entity.push_back(create_button("Exit", 2, "../assets/graphic_2D/button_Exit.png", 44.791, 67.5, 1.0, 1.0, 0, 0, 0, 200, 100,
        44.791, 67.5, 10.416, 9.259, &button_exit_pressed, &button_exit_released, &button_exit_overlay, &button_exit_default,
        "../assets/audio/Sound-click.wav", 75.0, "../assets/audio/Sound-overlay.wav", 75.0));
    ///////////////////////////////////////

    /// @note
    //pointeur sur fonction qui sera la condition while de la game loop
    // bool (*condition_game_loop)(std::vector<Entity *>); 
    core = new Game_engine(list_entity, &condition_game_loop);

    /////////////////////////////////////// @ingroup add function custom
    core->add_custom_func(&check_change_state, "check_change_state");
    ///////////////////////////////////////
    window_conf_s conf_wdw;
    conf_wdw.width = WINDOW_WIDTH;
    conf_wdw.height = WINDOW_HEIGHT;
    conf_wdw.title = (char *)"R-type";
    core->enable_rendersystem<Rendersystem>(&conf_wdw);
    core->enable_eventsystem<Eventsystem>();
    core->enable_networksystem(network);
    core->enable_soundsystem<Soundsystem>();
    core->get_soundsystem()->add_music("../assets/audio/Menu_music.wav", "Menu_music");
    core->get_soundsystem()->start_playlist();

    core->run();
    delete core;
    return 0;
}
