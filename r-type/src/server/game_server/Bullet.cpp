/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** Bullet
*/

#include "Bullet.hpp"

Bullet::Bullet(int x, int y, type_bullet type)
{
    if (type == BLASTER_ALLY) {
        _bullet_t.loadFromFile(PATH_ASSET_GRAPH.append("shoot.png"));
        _bullet_s.setScale(2, 2);
    } else if (type == ROCKET_MOB) {
        _bullet_t.loadFromFile(PATH_ASSET_GRAPH.append("shoot_mob.png"));
        _bullet_s.setScale(2, 2);
    } else if (type == OMNI) {
        _bullet_t.loadFromFile(PATH_ASSET_GRAPH.append("bullet_omni.png"));
        _bullet_s.setScale(0.2, 0.2);
    } else if (type == ELECTRIC_ALLY) {
        _bullet_t.loadFromFile(PATH_ASSET_GRAPH.append("bullet_electric.png"));
        _bullet_s.setScale(0.25, 1.0);
    } else if (type == BARRAGE_ALLY) {
        _bullet_t.loadFromFile(PATH_ASSET_GRAPH.append("barrage.png"));
        _bullet_s.setScale(0.75, 0.75);
    }
    _bullet_s.setTexture(_bullet_t);
    _bullet_s.setPosition(x, y);
    _pos = new coord_t;
    _pos->x = x;
    _pos->y = y;
    _type = type;

    if (_id_bullet_static > 255)
        _id_bullet_static = 1;
    _id_bullet = _id_bullet_static;
    _id_bullet_static++;
};

Bullet::~Bullet()
{
    delete _pos;
}

int Bullet::get_id()
{
    return _id_bullet;
}

coord_t *Bullet::get_pos(){return _pos;};

void Bullet::set_pos(int x, int y){_pos->x = x;_pos->y = y; _bullet_s.setPosition(x, y);};

sf::Sprite Bullet::get_sprite(){return _bullet_s;};

type_bullet Bullet::get_type(){return _type;};

void Bullet::move() {
    switch (_type)
    {
        case BLASTER_ALLY:
            set_pos(get_pos()->x + 30, get_pos()->y);
            break;
        case ROCKET_MOB:
            set_pos(get_pos()->x - 20, get_pos()->y);
            break;
        case OMNI:
            if (_angle == 0)
                set_pos(get_pos()->x + 10, get_pos()->y);
            if (_angle == 90)
                set_pos(get_pos()->x, get_pos()->y - 10);
            if (_angle == 180)
                set_pos(get_pos()->x - 10, get_pos()->y);
            if (_angle == 270)
                set_pos(get_pos()->x, get_pos()->y + 10);
            if (_angle == 45) {
                set_pos(get_pos()->x + 8, get_pos()->y - 2);
            }
            if (_angle == 135) {
                set_pos(get_pos()->x - 8, get_pos()->y - 2);
            }
            if (_angle == 225) {
                set_pos(get_pos()->x - 8, get_pos()->y + 2);
            }
            if (_angle == 315) {
                set_pos(get_pos()->x + 8, get_pos()->y + 2);
            }
            break;
        case ELECTRIC_ALLY:
            //rand()%(max-min + 1) + min;
            set_pos(get_pos()->x + 15, rand()%((get_pos()->y + 20)-(get_pos()->y - 20) + 1) + get_pos()->y - 20);
            break;
        case BARRAGE_ALLY:
            set_pos(get_pos()->x + 50, get_pos()->y);
            break;
        default:
            break;
    }
}