/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival
** File description:
** Bullet
*/

#pragma once
#include "macro.hpp"
#include "Data_Network.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

static int _id_bullet_static = 1;
typedef struct coord_s
{
    int x;
    int y;
}coord_t;

class Bullet {
    public:
        Bullet(int x, int y, type_bullet type);
        ~Bullet();
        coord_t *get_pos();
        void set_pos(int x, int y);
        sf::Sprite get_sprite();
        type_bullet get_type();
        void move();
        void set_angle(int angle) {
            _angle = angle;
        };
        int get_id();
    protected:
    private:
        int _angle;
        coord_t *_pos;
        sf::Texture _bullet_t;
        sf::Sprite _bullet_s;
        type_bullet _type;
        int _id_bullet;
};
