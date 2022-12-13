/*
** EPITECH PROJECT, 2022
** __PLAYER__
** File description:
** __PLAYER__
*/

#pragma once

#include <iostream>
#include <string.h>
#include "macro.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef struct coord_s
{
    int x;
    int y;
}coord_t;

class Player {
    public:
        Player(int x, int y, int id, std::string name_sprite) {
            _pos = new coord_t;
            set_pos(x, y);
            set_id(id);
            _player_t.loadFromFile(PATH_ASSET_GRAPH.append(name_sprite));
            _player_s.setTexture(_player_t);
            _player_s.scale(3, 3);
            _player_s.setPosition(_pos->x, _pos->y);
            _state = 1;
            _score = 0;
//            _frame = sf::IntRect(66, 0 + (17 * skin), 33, 17);
//            _player_s.setTextureRect(_frame);
        }
        ~Player() {}
        void move(std::string msg) {
            if (msg.compare("UP") == 0)
                set_pos(_pos->x, _pos->y - 5);
            if (msg.compare("DOWN") == 0)
                set_pos(_pos->x, _pos->y + 5);
        }
        void set_id(int id) {
            _id = id;
        }
        void set_pos(int x, int y) {
            _pos->x = x;
            _pos->y = y;
            _player_s.setPosition(_pos->x, _pos->y);
        }
        coord_t *get_pos() {
            return _pos;
        }
        sf::Sprite get_sprite() {
            return _player_s;
        }
        void add_point(int value) {
            _score += value;
        }
        int get_score() {
            return _score;
        }
        int get_state() {
            return _state;
        }
        int _id;
    protected:
    private:
        int _score;
        coord_t *_pos;
        sf::Sprite _player_s;
        sf::Texture _player_t;
        sf::IntRect _frame;
        int _state;
};