/*
** EPITECH PROJECT, 2022
** Boss
** File description:
** Boos
*/

#ifndef __MINIBOSS__
#define __MINIBOSS__

#include "Mob.hpp"
#include <string>

class MiniBoss : public Mob {
    public:
        MiniBoss(int x, int y);
        ~MiniBoss();
        void remove_life(int value);
        int get_life();
    protected:
    private:
        int _life;
};

#endif /* !MINIBOSS */
