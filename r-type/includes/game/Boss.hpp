/*
** EPITECH PROJECT, 2022
** Boss
** File description:
** Boos
*/

#ifndef __BOSS__
#define __BOSS__

#include "Mob.hpp"
#include <string>

class Boss : public Mob {
    public:
        Boss(int x, int y);
        ~Boss();
        void remove_life(int value);
        int get_life();
    protected:
    private:
        int _life;
};

#endif /* !Boss */
