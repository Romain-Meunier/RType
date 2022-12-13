/*
** EPITECH PROJECT, 2022
** soundsystem.cpp
** File description:
** System
*/

#include "Game_engine.hpp"

std::vector<Entity *> filter_by_component(std::vector<Entity *> &list_entity, type_component type);

Soundsystem::Soundsystem(void *conf)
{
    std::cout << "Soundsystem enable\n";
    _index_music = 0;
}

Soundsystem::~Soundsystem()
{
    std::cout << "Soundsystem disable\n";
    while (_lib_music.size() > 0)
    {
        delete _lib_music[0].first;
        _lib_music.erase(_lib_music.begin());
    }
    while (_lib_sound_effect.size() > 0)
    {
        delete _lib_sound_effect[0];
        _lib_sound_effect.erase(_lib_sound_effect.begin());
    }
}

std::vector<std::pair<Sound_impl *, std::string>> &Soundsystem::get_sound()
{
    return _lib_music;
}

void Soundsystem::running_music()
{
    if (_lib_music.empty())
        return;
    if (_lib_music[_index_music].first->get_status() == 0) {
        _index_music++;
        if (_index_music >= _lib_music.size())
            _index_music = 0;
        _lib_music[_index_music].first->play();
    }
}

void Soundsystem::play_sound_effect()
{
    if (_lib_sound_effect.empty())
        return;
    if (_lib_sound_effect[0]->get_status() == 0) {
        delete _lib_sound_effect[0];
        _lib_sound_effect.erase(_lib_sound_effect.begin());
        if (!_lib_sound_effect.empty())
            _lib_sound_effect[0]->play();
    }

}

void Soundsystem::start_playlist()
{
    _lib_music[0].first->play();
}

void Soundsystem::add_music(const std::string &path_music, const std::string &name_music)
{
    Sound_impl *new_music = new Sound_impl(path_music.c_str());

    _lib_music.push_back(std::pair<Sound_impl *, std::string>(new_music, name_music));
}

void Soundsystem::add_sound_effect(const std::string &path_music)
{
    Sound_impl *new_music = new Sound_impl(path_music.c_str());

    new_music->volume(100);
    _lib_sound_effect.push_back(new_music);
    std::cout << "SOUND SIZE: " << _lib_sound_effect.size() << std::endl;
    if (_lib_sound_effect.size() == 1) {
        _lib_sound_effect[0]->play();
    }
}

void Soundsystem::del_music(const std::string &name_music)
{
    for (int i = 0; i < _lib_music.size(); i++)
    {
        if (_lib_music[i].second.compare(name_music) == 0)
            delete _lib_music[i].first;
            _lib_music.erase(_lib_music.begin() + i);
    }
}

void Soundsystem::clear_sound_effect()
{
    while(_lib_sound_effect.size() > 0) {
        delete _lib_sound_effect[0];
        _lib_sound_effect.erase(_lib_sound_effect.begin());
    }
}