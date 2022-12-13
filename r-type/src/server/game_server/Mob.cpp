/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-claire.cival [WSL : Ubuntu-20.04]
** File description:
** Mob
*/

#include "Mob.hpp"

Mob::Mob(int x, int y, std::string texture, std::string script /*, std::vector<Bullet *> &bullet_vect_ptr*/)
{
    _pos = new coord_t;
    _pos->x = x;
    _pos->y = y;
    open_script(PATH_ASSET_PATTERN.append(script));
    _type_of_mob = std::string("None");
    _state = 1;
    _mob_t.loadFromFile(PATH_ASSET_GRAPH.append(texture));
    _mob_s.setTexture(_mob_t);
    _mob_s.setPosition(x, y);

    _clock = NULL;

//    _bullet_vect = bullet_vect_ptr;
    _latent_action = 0;
    _tmp_fire = 0;

    if (_id_static > 255)
        _id_static = 1;
    _id = _id_static;
    _id_static++;
};

Mob::~Mob()
{
    delete _pos;
/*
    for (auto bullet : _bullet_vect) {
        delete bullet;
    }
*/
}

int Mob::get_id()
{
    return _id;
}

void Mob::add_bullet(int x, int y){new Bullet(x, y, ROCKET_MOB);};

coord_t *Mob::get_pos(){return _pos;};

void Mob::set_pos(int x, int y){_pos->x = x;_pos->y = y;
//std::cout << _pos->x << " " << _pos->y << std::endl;
_mob_s.setPosition(x, y);};

sf::Sprite Mob::getMobSprite(){return _mob_s;};


/*
std::vector<Bullet *> &Mob::get_bullet_vect(){
    //return _bullet_vect;
};
*/

void Mob::moove()
{
//    std::cout << _actions.size() << std::endl;
    if (_actions.size() == 0)
        return;
    std::string action = _actions[_latent_action];
    if (action.find('U') >= 0 && action.find('U') < action.size()) {
        int value_u = stoi(action.substr(action.find('U') + 2, action.find('|', action.find('U')) - action.find('U') + 2));
//        std::cout << 'U' << " " << value_u << std::endl;
        set_pos(get_pos()->x, get_pos()->y - value_u);
    }
    if (action.find('D') >= 0 && action.find('D') < action.size()) {
        int value_d = stoi(action.substr(action.find('D') + 2, action.find('|', action.find('D')) - action.find('D') + 2));
//        std::cout << 'D' << " " << value_d << std::endl;
        set_pos(get_pos()->x, get_pos()->y + value_d);
    }
    if (action.find('L') >= 0 && action.find('L') < action.size()) {
        int value_l = stoi(action.substr(action.find('L') + 2, action.find('|', action.find('L')) - action.find('L') + 2));
//        std::cout << 'L' << " " << value_l << std::endl;
        set_pos(get_pos()->x - value_l, get_pos()->y);
    }
    if (action.find('R') >= 0 && action.find('R') < action.size()) {
        int value_r = stoi(action.substr(action.find('R') + 2, action.find('|', action.find('R')) - action.find('R') + 2));
//        std::cout << 'R' << " " << value_r << std::endl;
        set_pos(get_pos()->x + value_r, get_pos()->y);
    }
    if (action.find("S|") >= 0 && action.find("S|") < action.size()) {
        _tmp_fire = 1;
       //add_bullet(this->get_pos()->x - 75, this->get_pos()->y + 24);        
    }
    if (action.find("SO") >= 0 && action.find("SO") < action.size()) {
        _tmp_fire = 2;
        std::cout << "tmp: " << _tmp_fire << " a:" << action.substr(action.find(":", action.find("SO")) + 1, action.size() - 2) << std::endl;
        _angle_fire = stoi(action.substr(action.find(":", action.find("SO")) + 1, action.size() - 2));
        //_angle_fire = 180;
       //add_bullet(this->get_pos()->x - 75, this->get_pos()->y + 24);        
    }

    if (_latent_action + 1 == _actions.size())
        _latent_action = 0;
    else
        _latent_action += 1;
}

void Mob::open_script(std::string script_file) {
    std::string line;
    std::string content;
    std::fstream fs;
    _actions.clear();
    fs.open(script_file, std::fstream::in);
//    std::cout << "fs is open" << fs.is_open() << " " << script_file << std::endl;
    if (fs.is_open()) {
        while ( getline (fs,line) ) {
            //std::cout << line << std::endl;
            content.append(line).append("\n");
        }
    }
    parse_file(content);
}

void Mob::parse_file(std::string content) {
    if (content.size() == 0)
        return;
    std::string texture = content.substr(content.find("\n") + 1, content.find("\n", content.find("\n") + 1) - content.find("\n"));
    content = content.substr(content.find("\n", content.find("\n") + 1));
    if (content.find("Init:") >= 0 && content.find("Init:") < content.size()) {
        std::cout << "___ x: i" << content.substr(content.find("Init:") + 6, content.find(".", content.find("Init:")) - content.find("Init:") - 6) << " \\\\y:" << content.substr(content.find(".", content.find("Init:")) + 1, content.find("|", content.find("Init:")) - 1 - content.find(".", content.find("Init:"))) << "||" << std::endl;
        int x = 0;
        int y = 0;
        if (content.substr(content.find("Init:") + 6, content.find(".", content.find("Init:")) - content.find("Init:") - 6).find('R') == 0)
            x = rand() % 1920;
        else
            x = stoi(content.substr(content.find("Init:") + 6, content.find(".", content.find("Init:")) - content.find("Init:") - 6));
        if (content.substr(content.find(".", content.find("Init:")) + 1, content.find("|", content.find("Init:")) - 1 - content.find(".", content.find("Init:"))).find('R') == 0)
            y = rand() % 1080;
        else
            y = stoi(content.substr(content.find(".", content.find("Init:")) + 1, content.find("|", content.find("Init:")) - 1 - content.find(".", content.find("Init:"))));
        std::cout << x << " " << y << std::endl;
        set_pos(x, y);
    }
    if (content.find("Comportement:") >= 0 && content.find("Comportement:") < content.size()) {
    content = content.substr(content.find("\n", content.find("Comportement:")));
//    std::cout << "comportement:" << content.substr(content.find('\n') + 1);
    //std::cout << "here1" << std::endl;
        while (content.empty() != true) {
            _actions.insert(_actions.end(), content.substr(0, content.find('\n')));
            content = content.substr(content.find('\n') + 1);
 //           std::cout << _actions[_actions.size() - 1] << std::endl; 
        }
    }
    _latent_action = 0;
//    std::cout << "here2" << std::endl;
}

void Mob::move(int x, int y)
{
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
    _mob_s.move(move_x, move_y);
    _pos->x += move_x;
    _pos->y += move_y;
}


std::string Mob::get_type()
{
    return _type_of_mob;
}

void Mob::set_type(std::string type)
{
    _type_of_mob = type;
}

void Mob::add_clock()
{
    _clock = new Clock();
}

Clock *Mob::get_clock()
{
    return _clock;
}

void Mob::set_state(int state)
{
    _state = state;
}

int Mob::get_state()
{
    return _state;
}