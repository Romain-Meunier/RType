/*
** EPITECH PROJECT, 2022
** Drawable_component.cpp
** File description:
** Component
*/

#include "Entity.hpp"

Drawable_component::Drawable_component(void *conf)
{
    std::cout << "Create Drawable_component\n";
    drawable_conf_s *conf_tmp = static_cast<drawable_conf_s *>(conf);

    _type = DRAWABLE_C; 
    _lib_graph = new Drawable_impl(conf_tmp->path_sprite);
    _lib_graph->set_position(conf_tmp->pos.x, conf_tmp->pos.y);
    _lib_graph->set_scale(SCALE_WIDTH_SPRITE * conf_tmp->scale.x, SCALE_HEIGHT_SPRITE * conf_tmp->scale.y);
    _lib_graph->set_rotation(conf_tmp->degree);
    _lib_graph->set_texture_rect(conf_tmp->rect.left, conf_tmp->rect.top, conf_tmp->rect.width, conf_tmp->rect.height);
    delete conf_tmp;
}

Drawable_component::~Drawable_component()
{
    std::cout << "Delete Drawable_component\n";
    delete _lib_graph;
}

Drawable_impl *Drawable_component::get_lib_graph() const
{
    return _lib_graph;
}
