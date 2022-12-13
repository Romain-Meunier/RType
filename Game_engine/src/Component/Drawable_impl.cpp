/*
** EPITECH PROJECT, 2022
** Drawable_impl.cpp
** File description:
** Component
*/

#include "Component.hpp"

sf::Vector2f modif_graphics_from_screen(float x, float y)
{
    return sf::Vector2f((float)((float)WINDOW_WIDTH * (float)(x / (float)100.0)), 
        (float)((float)WINDOW_HEIGHT * (float)(y / (float)100.0)));
}

Drawable_impl::Drawable_impl(const char *path_sprite)
{
    set_texture(path_sprite);
}

Drawable_impl::~Drawable_impl()
{

}

void Drawable_impl::set_texture(const char *path_sprite)
{
    _texture.loadFromFile(path_sprite);
    _sprite.setTexture(_texture);
}

sprite_t Drawable_impl::get_sprite() const
{
    return _sprite;
}

void Drawable_impl::set_position(const double x, const double y)
{
    _sprite.setPosition(modif_graphics_from_screen(x, y));
}

void Drawable_impl::set_scale(const double x, const double y)
{
    _sprite.setScale(x, y);
}
void Drawable_impl::set_color(const color_t &color)
{
    _sprite.setColor(color);
}

void Drawable_impl::set_rotation(const unsigned int degree)
{
    _sprite.setRotation(degree);
}

void Drawable_impl::set_texture_rect(const unsigned int &left, const unsigned int &top, const unsigned int &width, const unsigned int &height)
{
    _sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Drawable_impl::set_move(const int &x, const int &y)
{
    _sprite.move(x, y);
}