/*
** EPITECH PROJECT, 2022
** Player.cpp
** File description:
** R-Type
*/

#include "Player.hpp"
#include "macro.hpp"
#include "Network.hpp"

Player::Player(int x, int y, int skin)
{
    _state = 1;
    _pos = new coord_t;
    _pos->x = x;
    _pos->y = y;
    _player_t.loadFromFile(PATH_ASSET_GRAPH.append("r-type_spaceship.gif"));
    _player_s.setTexture(_player_t);
    _player_s.scale(3, 3);
    _player_s.setPosition(_pos->x, _pos->y);
    _frame = sf::IntRect(66, 0 + (17 * skin), 33, 17);
    _player_s.setTextureRect(_frame);
    _clock = NULL;
}

Player::~Player()
{
    delete _pos;
}

coord_t *Player::get_pos(){return _pos;};

void Player::shoot_bullet(Network *network) 
{
    if (_fire_rate.getElapsedTime().asMilliseconds() > 500) {
        // Bullet *bullet_temp = new Bullet(getPosition().x + 75, getPosition().y + 24);

        // _bullets.insert(_bullets.begin(), bullet_temp);
        network->udp_write(PLAYER_INPUT, "SHOOT");
        // sf::SoundBuffer sound_shoot;
        // sf::Sound shoot_pew;
        // sound_shoot.loadFromFile(PATH_ASSET_AUDIO.append("pew.wav"));
        // shoot_pew.setBuffer(sound_shoot);
        // shoot_pew.play();
        _fire_rate.restart();
    }
}

void Player::modif_pos(input_direction input) 
{
    //changing local pos of player
    switch (input)
    {
        case LEFT:
//            _player_s.move(-10, 0);
            break;
        case RIGHT:
//            _player_s.move(10, 0);
            break;
        case UP:
//            _player_s.move(0, -10);
            if (_frame.left < 122)
                _frame.left += 33;
            break;
        case DOWN:
//            _player_s.move(0, 10);
            if(_frame.left > 0)
                _frame.left -= 33;
            break;
        case IDLE:
            _frame.left = 66;
            break;
    }
    _player_s.setTextureRect(_frame);
}

void Player::move(int x, int y) {
    int move_x = 0;
    int move_y = 0;
    if (_pos->x - x > 0)
        move_x = -5;
    if (_pos->x - x < 0)
        move_x = 5;
    if (_pos->y - y > 0)
        move_y = -5;
    if (_pos->y - y < 0)
        move_y = 5;
/*
    std::cout << "Init: " << _pos->x << "." << _pos->y << std::endl;
    std::cout << "Mod: " << _pos->x << "." << _pos->y << std::endl;
    std::cout << "Move: x" << move_x << " y" << move_y << std::endl;
    std::cout << "GET: " << _player_s.getPosition().x << "." << _player_s.getPosition().y << std::endl;
*/
//    _player_s.setPosition(x, y);
    _player_s.move(move_x, move_y);
    _pos->x += move_x;
    _pos->y += move_y;
}

void Player::set_pos(int x, int y) {
    _pos->x = x;
    _pos->y = y;
    _player_s.setPosition(x, y);
}

sf::Sprite Player::get_sprite(){return _player_s;};

void Player::set_state(int state)
{
    _state = state;
}

int Player::get_state()
{
    return _state;
}

void Player::add_clock()
{
    _clock = new Clock();
}

Clock *Player::get_clock()
{
    return _clock;
}

void Player::set_next_index_bullet(int next) {
    _index_current_bullet += 1;
    if (_index_current_bullet >= 3)
        _index_current_bullet = 0;
}

int Player::get_index_bullet() {
    return _index_current_bullet;
}