/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** Kamikaze
*/

#include "Kamikaze.hpp"
#include <iostream>
Kamikaze::Kamikaze(int x, int y) : Mob(x, y, "ship_KAMIKAZE.png", "Mini_zig.txt")
{
    set_type(std::string("Kamikaze"));
}

Kamikaze::~Kamikaze()
{
}

/*
void Kamikaze::moove()
{
    if (_actions.size() == 0)
        return;
    std::string action = _actions[_latent_action];
    if (action.find('U') >= 0 && action.find('U') < action.size()) {
        int value_u = stoi(action.substr(action.find('U') + 2, action.find(' ', action.find('U')) - action.find('U') + 2));
        set_pos(get_pos()->x, get_pos()->y - value_u);
    }
    if (action.find('D') >= 0 && action.find('D') < action.size()) {
        int value_d = stoi(action.substr(action.find('D') + 2, action.find(' ', action.find('D')) - action.find('D') + 2));
        set_pos(get_pos()->x, get_pos()->y + value_d);
    }
    if (action.find('L') >= 0 && action.find('L') < action.size()) {
        int value_l = stoi(action.substr(action.find('L') + 2, action.find(' ', action.find('L')) - action.find('L') + 2));
        set_pos(get_pos()->x - value_l, get_pos()->y);
    }
    if (action.find('R') >= 0 && action.find('R') < action.size()) {
        int value_r = stoi(action.substr(action.find('R') + 2, action.find(' ', action.find('R')) - action.find('R') + 2));
        set_pos(get_pos()->x + value_r, get_pos()->y);
    }
    if (action.find('S') >= 0 && action.find('S') < action.size()) {
        add_bullet(this->get_pos()->x - 75, this->get_pos()->y + 24);        
    }
    if (_latent_action + 1 == _actions.size())
        _latent_action = 0;
    else
        _latent_action += 1;
}
*/

/*
void Kamikaze::moove_bullet()
{
//    std::vector<Bullet *> &bullet_vect = get_bullet_vect();

    for (int i = 0 ; i < bullet_vect.size() ; i++)
    {
        bullet_vect[i]->set_pos(bullet_vect[i]->get_pos()->x - 15, bullet_vect[i]->get_pos()->y);
        if (bullet_vect[i]->get_pos()->x < -10)
        {
            bullet_vect.erase(bullet_vect.begin() + i);
        }
    }
}
*/