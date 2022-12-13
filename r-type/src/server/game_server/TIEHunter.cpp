/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** TIEHunter
*/

#include "TIEHunter.hpp"
#include <iostream>

TIEHunter::TIEHunter(int x, int y) : Mob(x, y, "ship_TIE.png", "Big_zag.txt")
{
    set_type(std::string("TIEHunter"));
}

TIEHunter::~TIEHunter()
{
}

/*
void TIEHunter::moove_bullet()
{
    std::vector<Bullet *> &bullet_vect = get_bullet_vect();

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