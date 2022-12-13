/*
** EPITECH PROJECT, 2022
** Sound_component.cpp
** File description:
** Component
*/

#include "Entity.hpp"

Sound_component::Sound_component(void *conf)
{
    std::cout << "Create Sound_component\n";
    sound_conf_s *conf_tmp = static_cast<sound_conf_s *>(conf);

    _type = SOUND_C;
    for (char i = 0; i < conf_tmp->volume.size(); i++)
    {
        _lib_sound.push_back(new Sound_impl(conf_tmp->path_sound[i]));
        _lib_sound[i]->volume(conf_tmp->volume[i]);
    }
    delete conf_tmp;
}

Sound_component::~Sound_component()
{
    std::cout << "Delete Sound_component\n";
    for (int i = 0; i < _lib_sound.size(); i++) {
        delete _lib_sound[i];
    }
}

std::vector<Sound_impl *> Sound_component::get_lib_sound() const
{
    return _lib_sound;
}
