/*
** EPITECH PROJECT, 2022
** __NETWORK__
** File description:
** __NETWORK__
*/

#include "Network.hpp"

Network::Network(asio::io_context& io_context, short port, std::string server_ip): _io_context(io_context), _resolver(_io_context), _socket(_io_context), _udp_resolver(_io_context), _s_udp(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)), _reading_session(&Network::udp_read, this)
{
    server_info.ip = server_ip;
    server_info.port_tcp = port;
    server_info.port_udp = 0;
    _clients_in_room = 0;
    _id_client = 0;
    end_thread = 0;
    _tmp_state = NONE;
    _core_state = NONE;
    _win_or_lose = "none";
}

void Network::destroy() {
    std::cout << "Network disable" << std::endl;
    try {
        udp_write(DISCONNECT, std::string("leave: ") + std::to_string(_id_client));
        while (end_thread == 0);
    } catch (std::system_error &e) {
        e.what();
    }
}

Network::~Network()
{
    destroy();
//    tcp_write("leave");
}

void Network::lobby_create_room() {
//    std::cout << "send create" << std::endl;
    asio::write(_socket, asio::buffer(&_buffer, sizeof(_buffer)));
    std::cout << "cmd:" << (int) _buffer.cmd << std::endl;
    std::cout << "msg_length:" << (int) _buffer.strlen << std::endl;
    std::cout << "msg:" << _buffer.msg << std::endl;
    std::cout << "tcp port client:" << (int) _buffer.port << std::endl;
    std::cout << "addr ip :" << _buffer.addr << std::endl;

/*   
    asio::write(_socket, asio::buffer(&_buffer.cmd, sizeof(_buffer.cmd)));
    asio::write(_socket, asio::buffer(&_buffer.strlen, sizeof(_buffer.strlen)));
    asio::write(_socket, asio::buffer(&_buffer.msg, (size_t) _buffer.strlen));
    asio::write(_socket, asio::buffer(&_buffer.port, sizeof(_buffer.port)));
    asio::write(_socket, asio::buffer(&_buffer.addr, sizeof(char) * 16));
*/
    tcp_read();
}

// void Network::set_core_state( state_core_e *menu){_core_state = menu;};

void Network::disconnected_cmd() {
    asio::write(_socket, asio::buffer(&_buffer.cmd, sizeof(_buffer.cmd)));
}

int Network::connect()
{
    try {
        asio::connect(_socket, _resolver.resolve(server_info.ip.c_str(), std::to_string(server_info.port_tcp).c_str()));
    } catch (std::system_error) {
        return -1;
    }
//    _tmp_state = START_STATUS;
    _core_state = START_STATUS;
    return 0;
}

int Network::change_state() {
    if (_tmp_state == NONE)
        return -1;
    // std::cout << "new state" << std::endl; 
    return 1;
}

std::string Network::get_info() {
    switch (_tmp_state) 
    {
    case CONNECT_STATUS:
        _tmp_state = NONE;
        return "ON_CONNECT";
    case ROOM_STATUS:
        _tmp_state = NONE;
        return std::string("IN_ROOM:").append(std::to_string(_clients_in_room)).append("|").append(std::to_string(_id_client));
    case INIT_ROOM_STATUS:
        _tmp_state = NONE;
        return std::string("JOIN_ROOM");
    case GAME_INIT_STATUS:
        _tmp_state = NONE;
        return std::string("GAME_INIT:").append(_update[0]);
    case GAME_RUNNING_STATUS:
        _tmp_state = NONE;
//        std::cout << _update[1] << std::endl;
        return std::string("GAME_RUNNING:").append(_update[1]);
    case WIN_STATUS:
        _tmp_state = NONE;
        return _update[0];
    default:
        break;
    }
    return "";
}

void Network::buffer_reset() {
    _buffer.cmd = 0;
    _buffer.strlen = 0;
    for (int i = 0; i < 256; i++) {
        _buffer.msg[i] = 0;
        _game_buffer_res.packet.msg[i] = 0;
    }
    _game_buffer.packet.cmd = 0;
    _buffer.port = 0;
}

void Network::tcp_read() {
    buffer_reset();
    std::cout << "go in" << std::endl;
    asio::read(_socket, asio::buffer(&_buffer, sizeof(_buffer)));
//    asio::read(_socket, asio::buffer(&_buffer.cmd, sizeof(_buffer.cmd)));
    if (_buffer.cmd == SERVER_GIVE_ROOM_PORT) {
//        asio::read(_socket, asio::buffer(&_buffer.port, sizeof(_buffer.port)));
        server_info.port_udp = _buffer.port;
        //udp packet sent by client to server after he joined/created a room in order for the server to get IP
        udp_write(CLIENT_GIVE_IP, "JOINING ROOM");
        _core_state = ROOM_STATUS;
        _tmp_state = INIT_ROOM_STATUS;
    } else if (_buffer.cmd == ROOM_ACCESS_DENIED)
        std::cout << "Access Denied" << std::endl;
}

void Network::tcp_write(std::string choice, std::string name_room) 
{
    buffer_reset();
    /*temporal*/
    std::cout << choice << std::endl;
    for (int i = 0; i < server_info.ip.size(); i++)
        _buffer.addr[i] = server_info.ip[i];
    _buffer.addr[server_info.ip.size()] = '\0';

    _buffer.strlen = (char)name_room.size() + 1;
    for (int i = 0; i < name_room.size(); i++)
        _buffer.msg[i] = name_room[i];
    _buffer.msg[name_room.size()] = 0;
//    std::cout << (int)_buffer.strlen << " " << _buffer.msg << std::endl;
    _buffer.port = _s_udp.local_endpoint().port();
    std::cout << "port" << _buffer.port << std::endl;
    /*end local*/
    if (choice.compare("create") == 0) {
      _buffer.cmd = CREATE_ROOM;
      lobby_create_room();
    } else if (choice.compare("join") == 0) {
      _buffer.cmd = JOIN_ROOM;
        lobby_create_room();
    } else if (choice.compare("leave") == 0) {
      _buffer.cmd = DISCONNECT;
      disconnected_cmd();
    }
}

void Network::tcp_write(std::string choice) 
{
    buffer_reset();
    /*temporal*/
     for (int i = 0; i < 256; i++) {
        _buffer.msg[i] = 0;
    }
    for (int i = 0; i < server_info.ip.size(); i++)
        _buffer.addr[i] = server_info.ip[i];
    _buffer.addr[server_info.ip.size()] = '\0';
    _buffer.strlen = (char)choice.size() + 1;
//    for (int i = 0; i < choice.size(); i++)
//        _buffer.msg[i] = choice[i];
//    _buffer.msg[0] = 'A';
//    _buffer.msg[1] = 'B';
//    _buffer.msg[2] = 0;
//    _buffer.strlen = 2 + 1;

    _buffer.msg[choice.size()] = 0;
    std::cout << (int)_buffer.strlen << " " << _buffer.msg << std::endl;
    _buffer.port = _s_udp.local_endpoint().port();
    /*end local*/
    if (choice.compare("create") == 0) {
      _buffer.cmd = CREATE_ROOM;
      lobby_create_room();
    } else if (choice.compare("join") == 0) {
      _buffer.cmd = JOIN_ROOM;
        lobby_create_room();
    } else if (choice.compare("leave") == 0) {
      _buffer.cmd = DISCONNECT;
      disconnected_cmd();
    }
}

void Network::udp_write(command cmd, std::string msg) 
{
    buffer_reset();
    _game_buffer.packet.cmd = cmd;
        for (int i = 0; i < 256; i++) {
        _game_buffer.packet.msg[i] = 0;
    }
    _buffer.strlen = msg.size();
    for (int i = 0; i < msg.size(); i++) {
        _game_buffer.packet.msg[i] = msg[i];
    }
    _buffer.msg[msg.size()] = '\0';

//    asio::ip::udp::resolver::query query(asio::ip::udp::v4(), server_info.ip.c_str(), std::to_string(server_info.port).c_str());
    //asio::ip::udp::resolver::results_type endpoints = _udp_resolver.resolve(query);
    // std::cout << "CLIENT SENDING UDP_MSG TO IP:" << server_info.ip.c_str() << " PORT:" << std::to_string(server_info.port_udp).c_str() << "\n";
    asio::ip::udp::resolver::results_type endpoints = _udp_resolver.resolve(asio::ip::udp::v4(), server_info.ip.c_str(), std::to_string(server_info.port_udp).c_str());
    _s_udp.send_to(asio::buffer(&_game_buffer, sizeof(_game_buffer)), *endpoints.begin());
}

void show_bin2(int nb) {
    int bin[256];
    int i = 0;

    while(nb > 0) {
        bin[i] = nb % 2;
        nb = nb / 2;
        i++;
    }

    int space = 0;
    int diff = i % 8;
    while (diff != 0 && diff < 8) {
        std::cout << "0";
        diff += 1;
        space += 1;
    }
    for(i=i-1 ;i>=0 ;i--) {    
        if (space == 8) {
            std::cout << " ";
            space = 0;
        }
        std::cout << bin[i];
        space += 1;
    }
    std::cout << "\n";
}

void Network::udp_read() 
{
    asio::ip::udp::endpoint sender_endpoint;
    buffer_reset();

    _s_udp.receive_from(asio::buffer(&_game_buffer_res.packet, sizeof(_game_buffer_res.packet)), sender_endpoint);
    //std::cout << (int) _game_buffer_res.packet.cmd << "| cmd: " << _game_buffer_res.packet.msg << std::endl;
//    std::cout << "new cmd" << (int)_game_buffer_res.packet.cmd << std::endl;
    if (_game_buffer_res.packet.cmd == GAME_INIT) {
       Deserializer *deserializer = new Deserializer(&_game_buffer_res, 256);
       deserializer->deserialize();
       std::string new_msg(deserializer->get_deserialized_msg());
            if (new_msg.rfind("GAME$", 0) == 0 && new_msg.size() <= 8)
            {

            }
            else
            {
                std::cout << "CORE STATE:" << _core_state << "\n";
                if (_core_state == ROOM_STATUS) {
                    _tmp_state  = GAME_INIT_STATUS;
                    _core_state = GAME_RUNNING_STATUS;
                    _update.insert(_update.begin(), new_msg);
                }
                while (_update.size() > 2)
                    _update.erase(_update.end());
            }

    } else if (_game_buffer_res.packet.cmd == GAME_UPDATE) {
        // std::cout << "received" << std::endl;
       Deserializer *deserializer = new Deserializer(&_game_buffer_res, 256);
       deserializer->deserialize();
       std::string new_msg(deserializer->get_deserialized_msg());
       if (new_msg.rfind("GAME$", 0) == 0 && new_msg.size() <= 8)
        {
            std::cout << "ERROR" << std::endl;
        }
        else
        {
                //        std::cout << "crypted: " << unserializer(_game_buffer_res) << std::endl;
    //        std::cout << "msg uncrypted:" << _game_buffer_res.msg << std::endl;
    //        _update.insert(_update.begin(), new_msg);
            _core_state = GAME_RUNNING_STATUS;
            if (new_msg.size() > 0) {
                _tmp_state = GAME_RUNNING_STATUS;
                _update.insert(_update.begin(), new_msg);

                // _update.insert(_update.begin(), std::string(reinterpret_cast<const char *>(_game_buffer_res.packet.msg)));
            }
            // std::cout << "load" << _update[0] << std::endl;
            while (_update.size() > 2)
                _update.erase(_update.end());
            // std::cout << "end read" << std::endl;
        }

    } else if (_game_buffer_res.packet.cmd == GIVE_NBR_TO_CLI) {
        _id_client = atoi(reinterpret_cast<const char *>(_game_buffer_res.packet.msg));
    } else if (_game_buffer_res.packet.cmd == ROOM_PLAYER) {
        _clients_in_room = stoi(std::string(reinterpret_cast<const char *>(_game_buffer_res.packet.msg)).substr(std::string(reinterpret_cast<const char *>(_game_buffer_res.packet.msg)).find(": ") + 2));
        _tmp_state = ROOM_STATUS;
        _core_state = ROOM_STATUS;
//
    } else if (_game_buffer_res.packet.cmd == WIN) {
        std::cout << "WE GOT WIN\n";

            _update.insert(_update.begin(), std::string(reinterpret_cast<const char *>(_game_buffer_res.packet.msg)));
            _tmp_state = WIN_STATUS;
            _core_state = ROOM_STATUS;
        
    } else if (_game_buffer_res.packet.cmd == DISCONNECT) {
        end_thread = 1;
        _core_state = CONNECT_STATUS;
        return;
    }
    udp_read();
}