/*
** EPITECH PROJECT, 2022
** Text_impl
** File description:
** Component
*/

#include "Component.hpp"

sf::Vector2f modif_graphics_from_screen(float x, float y);

Text_impl::Text_impl(const char *path_font, const char *str_text)
{
    set_font(path_font);
    set_text(str_text);
}

Text_impl::~Text_impl()
{
}

text_t Text_impl::get_text() const
{
    return _text;
}

std::string Text_impl::get_string() const
{
    return _text.getString();
}


void Text_impl::set_text(const char *str_text)
{
    _text.setString(str_text);
}

void Text_impl::set_font(const char *path_font)
{
    _font.loadFromFile(path_font);
    _text.setFont(_font);
}

void Text_impl::set_position(const double x, const double y)
{
    _text.setPosition(modif_graphics_from_screen(x, y));
}

void Text_impl::set_scale(const float x, const float y)
{
    _text.setScale(SCALE_WIDTH_SPRITE * x, SCALE_HEIGHT_SPRITE * y);
}

void Text_impl::set_rotation(const unsigned int degree)
{
    _text.setRotation(degree);
}