/*
** EPITECH PROJECT, 2022
** Clock_component
** File description:
** Component
*/

#include "Component.hpp"

Clock_component::Clock_component(void *conf)
{
    std::cout << "Create Clock_component\n";
    clock_conf_t *conf_tmp = static_cast<clock_conf_s *>(conf);

    _type = CLOCK_C;
    _timer = conf_tmp->timer;
    _clock_func = conf_tmp->clock_func;
    _start = std::chrono::system_clock::now();
}

Clock_component::~Clock_component()
{
    std::cout << "Delete Clock_component\n";
}

void Clock_component::restart_time()
{
    _start = std::chrono::system_clock::now();
}

std::chrono::duration<double> Clock_component::get_time() 
{
    return(std::chrono::system_clock::now() - _start);
}

void Clock_component::exe_clock_func(Game_engine *g_e)
{
    if (get_time().count() >= _timer) {
        _clock_func(g_e);    
    }
}