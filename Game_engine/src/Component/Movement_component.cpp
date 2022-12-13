/*
** EPITECH PROJECT, 2022
** Movement_component.cpp
** File description:
** Component
*/

#include <Entity.hpp>

std::vector<Entity *> filter_by_name(std::vector<Entity *> &list_entity, const char *name);

Movement_component::Movement_component(void *conf)
{
    std::cout << "Create Movement_component\n";
    movement_conf_s *conf_tmp = static_cast<movement_conf_s *>(conf);
    
    _type = MOVEMENT_C;
    set_vector_dir(conf_tmp->vector_dir.x, conf_tmp->vector_dir.y);
    set_position(conf_tmp->position.x, conf_tmp->position.y);
    set_speed(conf_tmp->speed);
    delete conf_tmp;
}

Movement_component::~Movement_component()
{
    std::cout << "Delete Movement_component\n";
}

double Movement_component::get_speed() const
{
    return _speed;
}

void Movement_component::set_speed(const double &new_speed)
{
    _speed = new_speed;
}

vector_2f_s Movement_component::get_vector_dir() const
{
    return _vector_dir;
}

void Movement_component::set_vector_dir(const double &x, const double &y)
{
    _vector_dir.x = x;
    _vector_dir.y = y;
}

vector_2f_s Movement_component::get_position() const
{
    return _position;
}

void Movement_component::set_position(const double &x, const double &y)
{
    _position.x = x;
    _position.y = y;
}
