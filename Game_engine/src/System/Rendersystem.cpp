/*
** EPITECH PROJECT, 2022
** Rendersystem.cpp
** File description:
** System
*/

#include <iostream>
#include "Rendersystem.hpp"
#include "config_comp.hpp"

Rendersystem::Rendersystem(void *conf)
{
    window_conf_s *wdw_config = static_cast<window_conf_s *>(conf);
    _window = new window_t;
    _window->create(sf::VideoMode(wdw_config->width, wdw_config->height), wdw_config->title, sf::Style::Default);
    std::cout << "Rendersystem enable\n";
}

Rendersystem::~Rendersystem()
{
    _window->close();
    delete _window;
    std::cout << "Rendersystem disable\n";
}

void Rendersystem::close_wdw()
{
    _window->close();
}

void Rendersystem::draw_sprite(sprite_t sprite)
{
    _window->draw(sprite);
}

void Rendersystem::draw_text(text_t text)
{
    _window->draw(text);
}

void Rendersystem::display_wdw()
{
    _window->display();
}

const bool Rendersystem::wdw_isopen()
{
    return _window->isOpen();
}

window_t *Rendersystem::get_window()
{
    return _window;
}

const bool Rendersystem::get_event_wdw(event_t &event)
{
    return _window->pollEvent(event);
}