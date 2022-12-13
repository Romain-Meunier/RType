/*
** EPITECH PROJECT, 2022
** Sound_impl.cpp
** File description:
** Component
*/

#include "Component.hpp"

Sound_impl::Sound_impl(const char *path_sound)
{
    _sound_b.loadFromFile(path_sound);
    _sound.setBuffer(_sound_b);
}

Sound_impl::~Sound_impl()
{

}

sf::SoundSource::Status Sound_impl::get_status()
{
    return _sound.getStatus();
}

void Sound_impl::play()
{
    
    if (get_status() != 2)
        _sound.play();
}

void Sound_impl::pause()
{
    _sound.pause();
}

void Sound_impl::stop()
{
    _sound.stop();
}

void Sound_impl::volume(const double &volume)
{
    _sound.setVolume(volume);
}