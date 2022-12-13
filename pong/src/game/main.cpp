/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** PONG
*/

#include <Game_engine.hpp>
#include <cstdarg>

bool default_loop(Game_engine *g_e);

Entity *create_button(const char *name_component, const unsigned int nbr_arg, ...);
Entity *create_drawable(const char *name_component, ...);

drawable_conf_s *config_comp_drawable(va_list &vl);
movement_conf_s *config_comp_movement(va_list &vl);
event_conf_s *config_comp_input(const unsigned int nbr_arg, va_list &vl);
sound_conf_s *config_comp_sound(const unsigned int nbr_arg, va_list &vl);

void button_default(Game_engine *g_e);
void button_pressed(Game_engine *g_e);
void button_overlay(Game_engine *g_e);
void button_start_released(Game_engine *g_e);
void button_start_multi_released(Game_engine *g_e);

Entity *create_bar(const char *name_component, const unsigned int nbr_sound, ...)
{
    Entity *bar = new Entity(name_component);
    va_list vl;
    
    va_start(vl, nbr_sound);
    bar->add_component<Drawable_component>(config_comp_drawable(vl));
    bar->add_component<Sound_component>(config_comp_sound(nbr_sound, vl));
    va_end(vl);
    return bar;
}

Entity *create_ball(const char *name_component, const unsigned int nbr_sound, ...)
{
    Entity *ball = new Entity(name_component);
    va_list vl;

    va_start(vl, nbr_sound);
    ball->add_component<Drawable_component>(config_comp_drawable(vl));
    ball->add_component<Movement_component>(config_comp_movement(vl));
    ball->add_component<Sound_component>(config_comp_sound(nbr_sound, vl));
    va_end(vl);
    return ball;
}

int main(int ac, char **av)
{
    ///@note
    /*
    ///// INIT OF VECTOR ENTITY | une bonne idée serais que l'utilisateru créer ses entity avec un txt en indiquant tout depuis le txt et en le lisant on créer la liste
    /////// INIT VECTOR OF COMPONENT
    ///////// INIT COMPONENT
    */
    asio::io_context io_context;
    Network *network = nullptr;

    if (ac == 3) {
        network = new Network(io_context, (short) atoi(av[2]), std::string(av[1]));
    }

    Game_engine *core;
    std::vector<Entity *> list_entity;
    /////////////////////////////////////// @ingroup createS Entity
    list_entity.push_back(create_drawable("Background", "../assets/graphic_2D/Arena_Pong.jpg", 0.0, 0.0, 1.0, 1.0, 0, 0, 0, 1920, 1080));

    if (ac == 3) {
        list_entity.push_back(create_button("Play_button", 0, "../assets/graphic_2D/Button_play.png", 30.0, 30.0, 1.0, 1.0, 0, 0, 0, 800, 400,
        30.0, 32.0, 40.0, 30.0, &button_pressed, &button_start_multi_released, &button_overlay, &button_default));
    } else {
        list_entity.push_back(create_button("Play_button", 0, "../assets/graphic_2D/Button_play.png", 30.0, 30.0, 1.0, 1.0, 0, 0, 0, 800, 400,
        30.0, 32.0, 40.0, 30.0, &button_pressed, &button_start_released, &button_overlay, &button_default));
    }
    ///////////////////////////////////////

    /// @note
    //pointeur sur fonction qui sera la condition while de la game loop
    // bool (*condition_game_loop)(std::vector<Entity *>); 
    core = new Game_engine(list_entity, &default_loop);

    /////////////////////////////////////// @ingroup add function custom
    ///////////////////////////////////////
    window_conf_s conf_wdw;
    conf_wdw.width = WINDOW_WIDTH;
    conf_wdw.height = WINDOW_HEIGHT;
    conf_wdw.title = (char *)"R-type";
    core->enable_rendersystem<Rendersystem>(&conf_wdw);
    core->enable_eventsystem<Eventsystem>();
    core->enable_soundsystem<Soundsystem>();
    if (ac == 3) {
        core->enable_networksystem(network);
    }
    core->get_soundsystem()->add_sound_effect("../assets/audio/end_game_pong.wav");

    core->run();
    delete core;
    return 0;
}