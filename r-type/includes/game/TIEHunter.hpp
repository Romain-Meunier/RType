/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** TIEHunter
*/

#ifndef TIEHUNTER_HPP_
#define TIEHUNTER_HPP_
#include "Mob.hpp"

class TIEHunter : public Mob {
    public:
        TIEHunter(int x, int y);
        ~TIEHunter();
//        int get_fire();
//        void moove_bullet();
    protected:
    private:
        sf::Clock _fire_rate;
};

#endif /* !TIEHUNTER_HPP_ */
