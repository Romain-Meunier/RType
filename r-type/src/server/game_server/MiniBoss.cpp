/*
** EPITECH PROJECT, 2022
** Boss
** File description:
** Boss
*/

#include "MiniBoss.hpp"

MiniBoss::MiniBoss(int x, int y) : Mob(x, y, "boss_1.png", "Mini_boss1.txt")
{
    set_type(std::string("MINIBOSS"));
    _life = 4;
}

MiniBoss::~MiniBoss()
{
}

void MiniBoss::remove_life(int value) {
    std::cout << "here: " << _life << std::endl;
    if (_life == 3) {
        std::cout << "here 3" <<  std::endl;
        _actions.clear();
        open_script(PATH_ASSET_PATTERN.append("Mini_boss2.txt"));
    }
    _life -= value;
}

int MiniBoss::get_life() {
    return _life;
}