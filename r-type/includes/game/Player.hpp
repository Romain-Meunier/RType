/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival
** File description:
** Player
*/

#pragma once
#include <vector>
#include "Clock.hpp"
#include "Bullet.hpp"
enum input_direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    IDLE
};

class Network;

class Player
{
    public:
        Player(int x, int y, int skin);
        ~Player();
        coord_t *get_pos();

        void shoot_bullet(Network *network);
        void modif_pos(input_direction input);
        void set_pos(int x, int y);
        void move(int x, int y);
        void set_state(int state);
        int get_state();
        void add_clock();
        Clock *get_clock();
        sf::Sprite get_sprite();
        int get_index_bullet();
        void set_next_index_bullet(int next);
        int _id;

    private:
        // boost::uuids::uuid _uuid;
        coord_t *_pos;
        sf::Sprite _player_s;
        sf::Texture _player_t;
        sf::IntRect _frame;
        sf::Clock _fire_rate;
        int _state;
        Clock *_clock;
        int _index_current_bullet;
};