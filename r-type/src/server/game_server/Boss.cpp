/*
** EPITECH PROJECT, 2022
** Boss
** File description:
** Boss
*/

#include "Boss.hpp"

Boss::Boss(int x, int y) : Mob(x, y, "bigBoss.png", "Boss_state1.txt")
{
    set_type(std::string("BOSS"));
    _life = 5;
}

Boss::~Boss()
{
}

void Boss::remove_life(int value) {
    std::cout << "here: " << _life << std::endl;
    if (_life == 4) {
        std::cout << "here 3" <<  std::endl;
        _actions.clear();
        open_script(PATH_ASSET_PATTERN.append("Boss_state2.txt"));    
    } else if (_life == 3) {
        std::cout << "here 1" <<  std::endl;
        _actions.clear();
        open_script(PATH_ASSET_PATTERN.append("Boss_state3.txt"));
    }
    _life -= value;
}

int Boss::get_life() {return _life;}