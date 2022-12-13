/*
** EPITECH PROJECT, 2022
** Entity.cpp
** File description:
** Game_engine
*/

#include "Entity.hpp"

Entity::Entity(const std::string name_entity)
{
    _name_entity.assign(name_entity.c_str());
    std::cout << "Create Entity " << _name_entity << std::endl;
}

Entity::~Entity()
{
    while (_list_component.size() > 0) {
        delete _list_component.front();
        _list_component.erase(_list_component.begin());
    }
    std::cout << "Delete Entity " << _name_entity << std::endl;
}

const std::string Entity::get_name_type()
{
    return _name_entity;
}

const bool Entity::get_ifcomp(const type_component &comp_e)
{
    for (int i = 0; i < _list_component.size(); i++)
    {
        if (comp_e == _list_component[i]->get_type())
            return true;
    }
    return false;
}
