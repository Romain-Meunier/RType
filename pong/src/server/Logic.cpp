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

}

Logic::~Logic() {

}

void Logic::init_player(std::vector<Client *> client)
{
    int x = 100;
    int y = 50;
    while (_player_vect.size() != 0) {
        delete _player_vect[0];
        _player_vect.erase(_player_vect.begin());
    }

    for (int i = 0; i < 2; i++) {
        if (i == 0)
            _player_vect.push_back(new Player(96, 624, i,"bar_blue.png"));
        else
            _player_vect.push_back(new Player(1803, 624, i, "bar_red.png"));
    }
}

void Logic::check_state_game()
{
}

void Logic::update_menu(std::vector<Client *> clients) {
    std::string snapshot;

    snapshot.append("Players: ");
    snapshot.append(std::to_string(clients.size()));
    _snapshot.insert(_snapshot.begin(), snapshot);
    _type_snap.insert(_type_snap.begin(), ROOM_PLAYER);
}

int Logic::check_victory() {
    for (int i = 0; i < _player_vect.size(); i++) {
        if (_player_vect[i]->get_score() == 5) {
            return _player_vect[i]->_id;
        }
    }
    return -1;
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
            break;
        case START_GAME:
            init_player(clients);
            update_game(clients);
            _type_snap.insert(_type_snap.begin(), GAME_INIT);
            _state = IN_GAME;
            _clock_lvl_transi->restartTime();
            break;
        case IN_GAME:
            if (_clock_lvl_transi->getTime().count() < 5) {
                while (_snapshot.size() != 0)
                    _snapshot.erase(_snapshot.begin());
                while (_type_snap.size() != 0)
                    _type_snap.erase(_type_snap.begin());
                break;
            }
            if (check_victory() != -1) {
                _type_snap.insert(_type_snap.begin(), WIN);
                _snapshot.insert(_snapshot.begin(), std::string("WIN:").append(std::to_string(check_victory())));
                _state = MENU;
                std::cout << std::string("WIN:").append(std::to_string(check_victory())) << std::endl;
                break;
            }
            update_game(clients);
            _type_snap.insert(_type_snap.begin(), GAME_UPDATE);
            break;
        case NOTHING:
            break;
        default:
        break;
    }
}

void Logic::update_game(std::vector<Client *> clients) {
    handle_ball();
    mooving_player(clients);
    create_snapshot();
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

void Logic::handle_ball() {
    if (_state == IN_GAME) {
        if (_balls.size() == 0)
            _balls.push_back(new Ball(902, 475, 1.5, 1.0, 0.3, "ball_pong.png"));
        for (int i = 0; i < _player_vect.size(); i++)
            if (_player_vect[i]->get_sprite().getGlobalBounds().intersects(_balls[0]->get_sprite().getGlobalBounds())) {
                _balls[0]->set_direction(_balls[0]->get_vector_dir().x * -1, _balls[0]->get_vector_dir().y);
                _balls[0]->set_speed(_balls[0]->get_speed() + 0.1);
                std::cout << "here" << std::endl;
            }
        if (_balls[0]->get_pos().y + 40 <= 0 || _balls[0]->get_pos().y + 160 >= 1080) {
            _balls[0]->set_direction(_balls[0]->get_vector_dir().x, _balls[0]->get_vector_dir().y * -1);
        }
        if (_balls[0]->get_pos().x <= 0) {
            _player_vect[1]->add_point(1);
            _balls[0]->init(800, 500, 1.5, 1.0, 0.3);
        }
        if (_balls[0]->get_pos().x >= 1920) {
            _player_vect[0]->add_point(1);
            _balls[0]->init(800, 500, 1.5, 1.0, 0.3);
        }
        /*
        if (_balls[0]->get_pos().y >= 1080 || _balls[0]->get_pos().y <= 0) {
            _balls[0]->set_direction(_balls[0]->get_vector_dir().x * -1, _balls[0]->get_vector_dir().x);
        }
        */
        _balls[0]->move();
    }
}

void Logic::mooving_player(std::vector<Client *> clients)
{
    std::string msg;

    for (int i = 0; i < clients.size(); i++) {
        while (!clients[i]->get_message_queue().empty()) {
            msg = clients[i]->pop_message();
            _player_vect[i]->move(msg);
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
            }
        }
        if (linked == 0) {
            _player_vect.erase(_player_vect.begin() + i);
        }
    }
}

void Logic::create_snapshot()
{
    std::string snapshot;
    int player_nbr = 1;
    int bullet_nbr = 1;

    for (auto player : _player_vect)
    {
        snapshot.append("PLAYER/" + std::to_string(player_nbr) + ":");
        snapshot.append(std::to_string(player->get_pos()->x));
        snapshot.append(".");
        snapshot.append(std::to_string(player->get_pos()->y));
        snapshot.append("|!");
        snapshot.append(std::to_string(player->get_score()));
        snapshot.append("|\n");
        player_nbr++;
    }
    for (auto ball : _balls)
    {
        snapshot.append("BALL/" + std::to_string(1) + ":");
        snapshot.append(std::to_string(static_cast<int>(ball->get_pos().x)));
        snapshot.append(".");
        snapshot.append(std::to_string(static_cast<int>(ball->get_pos().y)));
        snapshot.append("|!");
        snapshot.append(std::to_string(ball->get_state()));
        snapshot.append("|\n");
    }
    std::cout << snapshot << std::endl;
    _snapshot.insert(_snapshot.begin(), snapshot);
}

