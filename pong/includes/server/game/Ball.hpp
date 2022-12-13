/*
** EPITECH PROJECT, 2022
** __BALL__
** File description:
** __BALL__
*/

#pragma once

#include "Player.hpp"

typedef struct vector_2f {
    double x;
    double y;
} vector_2f;



class Ball {
    public:
        Ball(double x, double y, double dir_x, double dir_y, double speed, std::string name_sprite) {
            init(x, y, dir_x, dir_y, speed);
            _ball_t.loadFromFile(PATH_ASSET_GRAPH.append(name_sprite));
            _ball_s.setTexture(_ball_t);
            _ball_s.scale(3, 3);
            _ball_s.setPosition(_pos.x, _pos.y);
            _state = 1;
        }
        void init(double x, double y, double dir_x, double dir_y, double speed) {
            set_pos(x, y);
            set_direction(dir_x, dir_y);
            set_speed(speed);
        }
        ~Ball();
        void set_pos(double x, double y) {
            _pos.x = x;
            _pos.y = y;
            _ball_s.setPosition(_pos.x, _pos.y);
        }
        void set_direction(double x, double y) {
            _direction.x = x;
            _direction.y = y;
        }
        void set_speed(double speed) {
            _speed = speed;
        }
        void move() {
            double next_x = static_cast<double>(get_pos().x * 100 / 1920) + get_vector_dir().x * get_speed();
            double next_y = static_cast<double>(get_pos().y * 100 / 1080) + get_vector_dir().y * get_speed();
            set_pos(next_x / 100 * 1920, next_y / 100 * 1080);
        }
        vector_2f get_vector_dir() {
            return _direction;
        }
        vector_2f get_pos() {
            return _pos;
        }
        double get_speed() {
            return _speed;
        }
        sf::Sprite get_sprite() {
            return _ball_s;
        }
        int get_state() {
            return _state;
        }
    protected:
    private:
        sf::Sprite _ball_s;
        sf::Texture _ball_t;

        vector_2f _direction;
        vector_2f _pos;
        double _speed;
        int _state;
};

//#endif /* !__BALL__ */
