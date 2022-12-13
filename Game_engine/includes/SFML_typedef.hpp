/*
** EPITECH PROJECT, 2022
** SFML_typedef.hpp
** File description:
** Game_engine
*/

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/// @note
/// @example
//ici on changera à la main la taille de la window, cela fait partie de l'initialisation
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
//
#define REFERENCE_RESOLUTION_WIDTH 1920.0
#define REFERENCE_RESOLUTION_HEIGHT 1080.0
#define SCALE_WIDTH_SPRITE (float)((float) WINDOW_WIDTH / (float)REFERENCE_RESOLUTION_WIDTH)
#define SCALE_HEIGHT_SPRITE (float)((float) WINDOW_HEIGHT / (float)REFERENCE_RESOLUTION_HEIGHT)

typedef sf::RenderWindow window_t;
typedef sf::Event event_t;
typedef sf::Sprite sprite_t;
typedef sf::Texture texture_t;
typedef sf::Keyboard::Key keyboard_t;
typedef sf::SoundBuffer sound_buffer_t;
typedef sf::Sound sound_t;
typedef sf::Text text_t;
typedef sf::Font font_t;
typedef sf::Color color_t;
