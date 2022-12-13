/*
** EPITECH PROJECT, 2022
** Input_component.cpp
** File description:
** Component
*/

#include "Entity.hpp"

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

Input_component::Input_component(void *conf)
{
    std::cout << "Create Input_component\n";
    event_conf_s *conf_tmp = static_cast<event_conf_s *>(conf);
    
    _type = INPUT_C;
    _input_keyboard.reserve(conf_tmp->list_input_func.size());
    for (int i = 0; i < conf_tmp->list_input_func.size(); i++) 
    {
        _input_keyboard.push_back(conf_tmp->list_input_func[i]);
    }
    delete conf_tmp;
}

Input_component::~Input_component()
{
    std::cout << "Delete Input_component\n";
}

std::vector<std::pair<int, ptr_func_custom>> Input_component::get_input() const
{
    return _input_keyboard;
}
