/*
** EPITECH PROJECT, 2022
** text_component
** File description:
** Component
*/

#include "Component.hpp"

Text_component::Text_component(void *conf)
{
    std::cout << "Create Text_component\n";
    text_conf_s *conf_tmp = static_cast<text_conf_s *>(conf);

    _type = TEXT_C;
    _lib_text = new Text_impl(conf_tmp->path_font, conf_tmp->string_txt);
    _lib_text->set_position(conf_tmp->pos.x, conf_tmp->pos.y);
    _lib_text->set_scale(conf_tmp->scale.x, conf_tmp->scale.y);
    _lib_text->set_rotation(conf_tmp->degree);
}

Text_component::~Text_component()
{
    std::cout << "Delete Text_component\n";
    delete _lib_text;
}
