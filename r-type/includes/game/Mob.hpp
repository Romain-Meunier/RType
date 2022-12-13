/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** Mob_server
*/
#include "Bullet.hpp"
#include "Clock.hpp"
#include <iostream>
#include <fstream>
#include "macro.hpp"
#pragma once

static int _id_static = 1;

class Mob {
    public:

        Mob(int x, int y, std::string texture, std::string script /*, std::vector<Bullet *> &bullet_vect_ptr*/);
        ~Mob();
        void add_bullet(int x, int y);
        coord_t *get_pos();
        void set_pos(int x, int y);
        sf::Sprite getMobSprite();

        void move(int x, int y);
        void moove();
        int get_fire() {
            if (_tmp_fire == 1) {
                _tmp_fire = 0;
                return 1;
            } else if (_tmp_fire == 2) {
                _tmp_fire = 0;
//                std::cout << "> 2" << std::endl;
                return 2;
            }
            return 0;
        };
        int angle_fire() {
            return _angle_fire;
        }
        std::string get_type();
        void set_type(std::string type);
        void set_state(int state);
        int get_state();
        Clock *get_clock();
        void add_clock();
        int get_id();
    protected:
        void open_script(std::string script_file);
        void parse_file(std::string content);
        coord_t *_pos;
        
        std::vector<Bullet *> _bullet_vect;
        std::vector<std::string> _actions;
        int _latent_action;
    private:
        sf::Sprite _mob_s;
        sf::Texture _mob_t;
        int _state;
        int _tmp_fire;
        int _angle_fire;
        Clock *_clock;
        std::string _type_of_mob;
        int _id;
};

