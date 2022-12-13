/*
** EPITECH PROJECT, 2022
** Logic
** File description:
** a
*/

#include "Room.hpp"

Logic::Logic () {
    _clock_mob_spawn = new Clock();
    _clock_lvl_transi = new Clock();
    _clock_game_loop = new Clock();
    std::cout << "Start Logic " << std::endl;
    _state = MENU;
    _bool_test = 1;
    _next_state = NOTHING;

    _index_current_bullet = 0;
    _type_bullet_available.push_back(BLASTER_ALLY);
    _type_bullet_available.push_back(ELECTRIC_ALLY);
    _type_bullet_available.push_back(BARRAGE_ALLY);
}

Logic::~Logic() {

}

void Logic::init_player(std::vector<Client *> client)
{
    int x = 100;
    int y = 100;
    _index_current_bullet = 0;
    for (int i = 0; i < _player_vect.size(); i++) {
        _player_vect[i]->set_pos(x, y);
        _player_vect[i]->_id = client[i]->id;
    }
    for (int i = _player_vect.size(); i < client.size(); i++)
    {
        _player_vect.push_back(new Player(x, y, i));
        _player_vect[i]->_id = client[i]->id;
        y += 50;
    }
    _mobs.clear();
    _clock_lvl_transi->restartTime();
    _clock_mob_spawn->restartTime();
}

void Logic::check_state_game()
{
    if (_player_vect.size() == 0) {
        std::cout << "Restart on Menu" << std::endl;
        _state = MENU;
    }
    /*
    else if (_clock_lvl_transi->getTime().count() > 60)
        _state = MENU;
    */
}

void Logic::update_menu(std::vector<Client *> clients) {
    std::string snapshot;

    while(!_mobs.empty()) {
        delete _mobs[0];
        _mobs.erase(_mobs.begin()); 
    }
    while(!_bullets.empty()) {
        delete _bullets[0];
        _bullets.erase(_bullets.begin()); 
    }
    snapshot.append("Players: ");
    snapshot.append(std::to_string(clients.size()));
    _snapshot.insert(_snapshot.begin(), snapshot);
    _type_snap.insert(_type_snap.begin(), ROOM_PLAYER);
}

void Logic::state_handling(std::vector<Client *> clients) {
    if (_next_state != NOTHING) {
        _state = _next_state;
        _next_state = NOTHING;
        _type_snap.insert(_type_snap.begin(), WIN);
        _snapshot.insert(_snapshot.begin(), "WIN");
        return;
    }
    switch (_state)
    {
        case MENU:
            update_menu(clients);
            nb_turn = 0;
            break;
        case START_GAME:
            if (nb_turn == 0) {
                init_player(clients);
                update_game(clients);
            } else if (nb_turn == 14) {
               _state = GAME_LVL1;
                create_snapshot();
            } else {
                create_snapshot();
            }
            std::cout << nb_turn << std::endl;
            _type_snap.insert(_type_snap.begin(), GAME_INIT);
//            send_update(GAME_INIT, update_game());_
    //         std::cout << "snap1: "<< _snapshot[0] << std::endl;
            nb_turn += 1;
            break;
        case GAME_LVL1:
            if (_clock_lvl_transi->getTime().count() >= 60 && _mobs.size() == 0) {
                _state = GAME_LVL2;
                _clock_lvl_transi->restartTime();
            }
                if (_player_vect.size() == 0)
                    _state = MENU;

                update_game(clients);
                _type_snap.insert(_type_snap.begin(), GAME_UPDATE);
//                _clock_game_loop->restartTime();
            //}
//                update_game(clients);
                // std::cout << "SNAPSHOT SENT:" << msg;
//                _type_snap.insert(_type_snap.begin(), GAME_UPDATE);
//                send_update(GAME_UPDATE, msg);
//                check_state_game();
            break;
        case GAME_LVL2:
            if (_player_vect.size() == 0)
                _state = MENU;
            if (_mobs.size() == 0) {
                _state = GAME_LVL3;
                _clock_lvl_transi->restartTime();
            }
            update_game(clients);
            break;
        case GAME_LVL3:
            if (_clock_lvl_transi->getTime().count() >= 60 && _mobs.size() == 0) {
                _state = GAME_LVL4;
            }
            if (_player_vect.size() == 0)
                _state = MENU;
            update_game(clients);
            _type_snap.insert(_type_snap.begin(), GAME_UPDATE);
            break;
        case GAME_LVL4:
            if (_player_vect.size() == 0)
            {
                _state = MENU;
            }
            update_game(clients);
            if (_mobs.size() == 0) {
                _next_state = MENU;
                // _type_snap.insert(_type_snap.begin(), WIN);
                // _snapshot.insert(_snapshot.begin(), "WIN");
                return;
            }
            _type_snap.insert(_type_snap.begin(), GAME_UPDATE);
            break;
        case NOTHING:
            break;
        default:
        break;
    }
}

void Logic::update_game(std::vector<Client *> clients) {
    spawn_mob();
    update_state(clients);
    mooving_player(clients);
    mooving_mob();
    mooving_bullet();
    create_snapshot();

    for (int i = 0 ; i < _mobs.size() ; i++)
    {
        if (_mobs[i]->get_state() == 2 && _mobs[i]->get_clock() != NULL && _mobs[i]->get_clock()->getTime().count() > 3) {
            _mobs.erase(_mobs.begin() + i);
            // if (_mobs[i]->get_type().compare("BOSS") == 0) {
            //     _next_state = MENU;
            // }
        }
    }
    for (int i = 0 ; i < _player_vect.size() ; i++)
    {
        if (_player_vect[i]->get_state() == 2 && _player_vect[i]->get_clock() != NULL && _player_vect[i]->get_clock()->getTime().count() > 3)
            _player_vect.erase(_player_vect.begin() + i);
    }

}

std::string Logic::getLastestSnapshot(void) {
//    std::cout << _snapshot.size() << std::endl; 
    while (_snapshot.size() > 2)
        _snapshot.pop_back();
    if (_snapshot.size() > 0)
        return _snapshot[0];
    return "";
};

command Logic::getLastestSnapshotType(void) {
    if (_type_snap.size() > 0)
        return _type_snap[0];
    return EOP;
};

void Logic::spawn_mob() {
    if (_state == GAME_LVL1) {
        if (_clock_mob_spawn->getTime().count() >= 1 && _clock_lvl_transi->getTime().count() < 47)
        {
            _clock_mob_spawn->restartTime();
            _mobs.push_back(new Kamikaze(1800, rand() % 900 + 1));
        }
    } else if (_state == GAME_LVL2) {
        if (_mobs.size() >= 1)
            return ;
        else
            _mobs.push_back(new MiniBoss(1790, 0));
    } else if (_state == GAME_LVL3) {
        if (_clock_mob_spawn->getTime().count() >= 1 && _clock_lvl_transi->getTime().count() < 47) {
            _clock_mob_spawn->restartTime();
            if (rand() % 2 == 1)
                _mobs.push_back(new TIEHunter(1800, rand() % 900 + 1));
            else
                _mobs.push_back(new Kamikaze(1800, rand() % 900 + 1));
        }
    } else if (_state == GAME_LVL4) {
        if (_mobs.size() >= 1)
            return ;
        else
            _mobs.push_back(new Boss(1790, 0));
    }

    // if (_clock_mob_spawn->getTime().count() >= 1)
    // {
    //     if (_clock_lvl_transi->getTime().count() >= 30) {
    //         if (rand() % 3 > 0) {
    //             _mobs.push_back(new TIEHunter(1920, rand() % 900 + 1));
    //             _mobs.push_back(new Kamikaze(1920, rand() % 900 + 1));
    //         } else {}
    //     } else {
    //         if (rand() % 3 > 1)
    //             _mobs.push_back(new Kamikaze(1920, rand() % 900 + 1));
    //     }
    //     _clock_mob_spawn->restartTime();
    // }
}

void Logic::mooving_player(std::vector<Client *> clients)
{
    std::string msg;

    for (int i = 0; i < clients.size(); i++) {
        while (!clients[i]->get_message_queue().empty()) {
            msg = clients[i]->pop_message();
    //            std::cout << "1: " << msg << std::endl;
            if (msg.compare("UP") == 0 && _player_vect[i]->get_pos()->y - 5 > 5)
                _player_vect[i]->set_pos(_player_vect[i]->get_pos()->x, _player_vect[i]->get_pos()->y - 5);
            if (msg.compare("DOWN") == 0 && _player_vect[i]->get_pos()->y + 5 + 120 < 1080)
                _player_vect[i]->set_pos(_player_vect[i]->get_pos()->x, _player_vect[i]->get_pos()->y + 5);
            if (msg.compare("LEFT") == 0 && _player_vect[i]->get_pos()->x - 5 > 5)
                _player_vect[i]->set_pos(_player_vect[i]->get_pos()->x - 5, _player_vect[i]->get_pos()->y);
            if (msg.compare("RIGHT") == 0 && _player_vect[i]->get_pos()->x + 5 < 1920 - 120)
                _player_vect[i]->set_pos(_player_vect[i]->get_pos()->x + 5, _player_vect[i]->get_pos()->y);
            if (msg.compare("SWAP_WEAPON") == 0)
            {
                _player_vect[i]->set_next_index_bullet(1);
            }
            if (msg.compare("SHOOT") == 0) {
                
                if (_type_bullet_available[_player_vect[i]->get_index_bullet()] == BARRAGE_ALLY)
                    _bullets.push_back(new Bullet(_player_vect[i]->get_pos()->x + 50, _player_vect[i]->get_pos()->y, _type_bullet_available[_player_vect[i]->get_index_bullet()]));
                else
                    _bullets.push_back(new Bullet(_player_vect[i]->get_pos()->x + 50, _player_vect[i]->get_pos()->y + 10, _type_bullet_available[_player_vect[i]->get_index_bullet()]));

                // if (_state == GAME_LVL4)
                //     _bullets.push_back(new Bullet(_player_vect[i]->get_pos()->x + 50, _player_vect[i]->get_pos()->y + 10,  ELECTRIC_ALLY));
                // else
                //     _bullets.push_back(new Bullet(_player_vect[i]->get_pos()->x + 50, _player_vect[i]->get_pos()->y + 10,  BLASTER_ALLY));
            }
        }
    }
}

void Logic::add_bullet(Bullet *bullet)
{
    _bullets.push_back(bullet);
}

void Logic::mooving_mob()
{
    for (int i = 0 ; i < _mobs.size() ; i++)
    {
        if (_mobs[i]->get_state() == 1) {
            if (_mobs[i]->get_type().compare("Kamikaze") == 0)
            {
                static_cast<Kamikaze*>(_mobs[i])->moove();
            }
            else if (_mobs[i]->get_type().compare("TIEHunter") == 0)
            {
                static_cast<TIEHunter*>(_mobs[i])->moove();
                if (static_cast<TIEHunter*>(_mobs[i])->get_fire() == 1)
                    _bullets.push_back(new Bullet(_mobs[i]->get_pos()->x - 75, _mobs[i]->get_pos()->y + 24, ROCKET_MOB));
            }
            else if (_mobs[i]->get_type().compare("BOSS") == 0) {
                static_cast<Boss*>(_mobs[i])->moove();
                switch (static_cast<Boss*>(_mobs[i])->get_fire())
                {
                    case 1:
                    _bullets.push_back(new Bullet(_mobs[i]->get_pos()->x - 75, _mobs[i]->get_pos()->y + 24, ROCKET_MOB));
                        break;
                    case 2:
//                        std::cout << "omni" << std::endl;
                        _bullets.push_back(new Bullet(_mobs[i]->get_pos()->x - 75, _mobs[i]->get_pos()->y + 24, OMNI));
                        _bullets[_bullets.size() - 1]->set_angle(_mobs[i]->angle_fire());
                        break;
                    default:
                        break;
                }
            } else if (_mobs[i]->get_type().compare("MINIBOSS") == 0) {
                static_cast<MiniBoss*>(_mobs[i])->moove();
                switch (static_cast<MiniBoss*>(_mobs[i])->get_fire())
                {
                    case 1:
                    _bullets.push_back(new Bullet(_mobs[i]->get_pos()->x - 75, _mobs[i]->get_pos()->y + 24, ROCKET_MOB));
                        break;
                    case 2:
                        _bullets.push_back(new Bullet(_mobs[i]->get_pos()->x - 75, _mobs[i]->get_pos()->y + 24, OMNI));
                        _bullets[_bullets.size() - 1]->set_angle(_mobs[i]->angle_fire());
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Logic::mooving_bullet()
{
    for (int i = 0 ; i < _bullets.size() ; i++)
    {
        _bullets[i]->move();
        if (_bullets[i]->get_pos()->x > 1920 || _bullets[i]->get_pos()->x < -100 || _bullets[i]->get_pos()->y > 1920 || _bullets[i]->get_pos()->y < -100/*5000*/) {
            delete _bullets[i];
            _bullets.erase(_bullets.begin() + i);
        }

        if (_bullets[i]->get_type() == BARRAGE_ALLY)
        {
            for (int u = 0 ; u < _bullets.size() ; u++)
            {
                if ((_bullets[u]->get_type() == ROCKET_MOB || _bullets[u]->get_type() == OMNI) && _bullets[u]->get_sprite().getGlobalBounds().intersects(_bullets[i]->get_sprite().getGlobalBounds()))
                {
                    delete _bullets[u];
                    // delete _bullets[i];
                    _bullets.erase(_bullets.begin() + u);
                    // _bullets.erase(_bullets.begin() + i);
                }
            }
        } //  && _mobs[i]->getMobSprite().getGlobalBounds().intersects(_bullets[j]->get_sprite().getGlobalBounds()) && _mobs[i]->get_state() == 1

    }
}

void Logic::update_state_of_monster()
{
    // std::cout << "_up_state" << std::endl;
    for (int i = 0 ; i < _mobs.size() ; i++)
    {

        std::string name_and_id = _mobs[i]->get_type() + std::to_string(_mobs[i]->get_id());

        if (_mobs[i]->get_pos()->x < -20 && _mobs[i]->get_state() != 2)
        {
            _mobs[i]->add_clock();
            _mobs[i]->set_state(2);
        }

        for (int j = 0 ; j < _bullets.size() ; j++)
        {

//            std::cout << "j" << j << "size" << _mobs[i]->get_state() << " " << _mobs[i]->getMobSprite().getGlobalBounds().intersects(_bullets[j]->get_sprite().getGlobalBounds()) << std::endl;
            if ((_bullets[j]->get_type() == BLASTER_ALLY || _bullets[j]->get_type() == ELECTRIC_ALLY) && _mobs[i]->getMobSprite().getGlobalBounds().intersects(_bullets[j]->get_sprite().getGlobalBounds()) && _mobs[i]->get_state() == 1)
            {
                if (_mobs[i]->get_type().compare("BOSS") == 0) {
                    if (static_cast<Boss *>(_mobs[i])->get_life() > 1) {
                        static_cast<Boss *>(_mobs[i])->remove_life(1);
                        delete _bullets[j];
                        _bullets.erase(_bullets.begin() + j);
                        break;
                    } else {
                        // std::cout << static_cast<Boss*>(_mobs[i])->get_life() << std::endl;
                        _mobs.erase(_mobs.begin() + i);
                        delete _bullets[j];
                        _bullets.erase(_bullets.begin() + j);
                        break;
                    }
                } else if (_mobs[i]->get_type().compare("MINIBOSS") == 0) {
                    std::cout << "here" << std::endl;
                    if (static_cast<MiniBoss*>(_mobs[i])->get_life() > 1) {
                        static_cast<MiniBoss *>(_mobs[i])->remove_life(1);
                        std::cout << "here dead" << std::endl;
                        delete _bullets[j];
                        _bullets.erase(_bullets.begin() + j);
                        std::cout << "end here dead" << std::endl;
                        break;
                    } else {
                        std::cout << static_cast<MiniBoss*>(_mobs[i])->get_life() << std::endl;
                        if (_mobs[i]->get_state() != 2)
                        {
                            _mobs[i]->add_clock();
                            _mobs[i]->set_state(2);
                            delete _bullets[j];
            //                _mobs.erase(_mobs.begin() + i);
                            _bullets.erase(_bullets.begin() + j);
                        }
                        break;
                    }
                } else {
                        if (_mobs[i]->get_state() != 2)
                        {
                            _mobs[i]->add_clock();
                            _mobs[i]->set_state(2);
                            delete _bullets[j];
            //                _mobs.erase(_mobs.begin() + i);
                            _bullets.erase(_bullets.begin() + j);
                        }
                    break;
                }
            }
        }
    }
}

void Logic::update_state_of_player( std::vector<Client *> clients)
{
    for (int i = 0; i < _player_vect.size(); i++) {
        int linked = 0;
        for (int j = 0; j < clients.size(); j++) {
            if (_player_vect[i]->_id == clients[j]->id) {
                linked = 1;
//                std::cout << "Linked" << clients[j]->id << std::endl;
            }
        }
        if (linked == 0) {
            _player_vect.erase(_player_vect.begin() + i);
//            std::cout << linked << std::endl;
        }
    }


    for (int i = 0 ; i < _player_vect.size() ; i++)
    {
        for (int j = 0 ; j < _bullets.size() ; j++)
        {
            if ((_bullets[j]->get_type() == ROCKET_MOB || _bullets[j]->get_type() == OMNI) && _player_vect[i]->get_sprite().getGlobalBounds().intersects(_bullets[j]->get_sprite().getGlobalBounds()))
            {
                if (_player_vect[i]->get_state() != 2)
                {
                    _player_vect[i]->set_state(2);
                    _player_vect[i]->add_clock();
                    // _player_vect.erase(_player_vect.begin() + i);
                    _bullets.erase(_bullets.begin() + j);
                }
                break;
            }
        }
    }
    for (int i = 0 ; i < _player_vect.size() ; i++)
    {
        for (int j = 0 ; j < _mobs.size() ; j++)
        {
            if (_player_vect[i]->get_sprite().getGlobalBounds().intersects(_mobs[j]->getMobSprite().getGlobalBounds()) && _mobs[j]->get_state() != 2)
            {
                if (_player_vect[i]->get_state() != 2)
                {
                    _player_vect[i]->set_state(2);
                    _player_vect[i]->add_clock();
                    // _player_vect.erase(_player_vect.begin() + i);
                    // _bullets.erase(_bullets.begin() + j);
                }

                if (_mobs[i]->get_state() != 2)
                {
                    _mobs[j]->set_state(2);
                    _mobs[j]->add_clock();
                }

//                _player_vect.erase(_player_vect.begin() + i);
//                _mobs.erase(_mobs.begin() + j);
                break;
            }
        }
    }
}
void Logic::update_state(std::vector<Client *> clients)
{
    update_state_of_monster();
    update_state_of_player(clients);
}

void Logic::create_snapshot()
{
    std::string snapshot;
    int player_nbr = 1;
    int bullet_nbr = 1;

    snapshot.assign("GAME$");
    for (auto player : _player_vect)
    {
        snapshot.append("PLAYER/" + std::to_string(player_nbr) + ":");
        snapshot.append(std::to_string(player->get_pos()->x));
        snapshot.append(".");
        snapshot.append(std::to_string(player->get_pos()->y));
        snapshot.append("|!");
        snapshot.append(std::to_string(player->get_state()));
        snapshot.append("|\n");
        player_nbr++;
    }

    for (auto mob : _mobs)
    {
        snapshot.append(mob->get_type() + "/" + std::to_string(mob->get_id()) + ":");
        snapshot.append(std::to_string(mob->get_pos()->x));
        snapshot.append(".");
        snapshot.append(std::to_string(mob->get_pos()->y));
        snapshot.append("|!");
        snapshot.append(std::to_string(mob->get_state()));
        snapshot.append("|\n");
    }

    for (int i = 0; i < NB_TYPE_BULLET; i++) {
        std::string bullet_list_str;
        if (i == BLASTER_ALLY)
            bullet_list_str.append("B_BLASTER_ALLY/");
        else if (i == ROCKET_MOB)
            bullet_list_str.append("B_ROCKET_MOB/");
        else if (i == OMNI)
            bullet_list_str.append("B_OMNI/");
        else if (i == ELECTRIC_ALLY)
            bullet_list_str.append("B_ELECTRIC_ALLY/");
        else if (i == BARRAGE_ALLY)
            bullet_list_str.append("B_BARRAGE_ALLY/");
        int nb = 0;
        for (auto bullet : _bullets) {
            if (i == BLASTER_ALLY && bullet->get_type() == BLASTER_ALLY) {
                nb += 1;
            } else if (i == ROCKET_MOB && bullet->get_type() == ROCKET_MOB) {
                nb += 1;
            } else if (i == OMNI && bullet->get_type() == OMNI) {
                nb += 1;
            } else if (i == ELECTRIC_ALLY && bullet->get_type() == ELECTRIC_ALLY) {
                nb += 1;
            } else if (i == BARRAGE_ALLY && bullet->get_type() == BARRAGE_ALLY) {
                nb += 1;
            }
        }
        bullet_list_str.append(std::to_string(nb) + ":");
        for (auto bullet : _bullets)
        {
            bullet_nbr = bullet->get_id();
            //&B and &R
            //&B:85.23|65.23|78.23|\n
            //&R:85.23|65.23|78.23|\n
            if (i == BLASTER_ALLY && bullet->get_type() == BLASTER_ALLY) {//
                bullet_list_str.append(std::to_string(bullet_nbr) + "*");
                bullet_nbr++;
                bullet_list_str.append(std::to_string(bullet->get_pos()->x) + "." + std::to_string(bullet->get_pos()->y) + "|");
            } else if (i == ROCKET_MOB && bullet->get_type() == ROCKET_MOB) {
                bullet_list_str.append(std::to_string(bullet_nbr) + "*");
                bullet_nbr++;
                bullet_list_str.append(std::to_string(bullet->get_pos()->x) + "." + std::to_string(bullet->get_pos()->y) + "|");
            } else if (i == OMNI && bullet->get_type() == OMNI) {
                bullet_list_str.append(std::to_string(bullet_nbr) + "*");
                bullet_nbr++;
                bullet_list_str.append(std::to_string(bullet->get_pos()->x) + "." + std::to_string(bullet->get_pos()->y) + "|");
            } else if (i == ELECTRIC_ALLY && bullet->get_type() == ELECTRIC_ALLY) {
                bullet_list_str.append(std::to_string(bullet_nbr) + "*");
                bullet_nbr++;
                bullet_list_str.append(std::to_string(bullet->get_pos()->x) + "." + std::to_string(bullet->get_pos()->y) + "|");
            } else if (i == BARRAGE_ALLY && bullet->get_type() == BARRAGE_ALLY) {
                bullet_list_str.append(std::to_string(bullet_nbr) + "*");
                bullet_nbr++;
                bullet_list_str.append(std::to_string(bullet->get_pos()->x) + "." + std::to_string(bullet->get_pos()->y) + "|");
            }
            else
            {

            }
        }
        if (bullet_list_str.back() == ':')
            bullet_list_str.append("|");
        bullet_list_str.append("\n");
        // if (nb != 0)
            snapshot.append(bullet_list_str);
//        std::cout << bullet_list_str << std::endl;
    }

//    std::cout << "str" << snapshot << std::endl;
//    std::cout << snapshot << std::endl;
    _snapshot.insert(_snapshot.begin(), snapshot);
}

