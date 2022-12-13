/*
** EPITECH PROJECT, 2022
** Room.cpp
** File description:
** r-type
*/

#include "Room.hpp"

class Client;

Room::Room(asio::io_context& io_context, std::string name) : _io_context(io_context), _udp_socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)), _thread_backend(&Room::backend_operation_handling, this)
{
    _logics = new Logic();
    _state = MENU;  
    _name = name;
    last_nbr_cli = 0;
    std::cout << "My name room: " << _name << std::endl;
    sleep(1);
    getMessage();
}

Room::~Room() {   
}

void Room::destroy()
{
    for (int i = 0; i < _clients.size(); i++) {
        send_update(DISCONNECT, "DISCONNECTED", _clients[i]->id);
        _clients.erase(_clients.begin() + i);
    }
//    delete _logics;
    std::cout << "Destroy Room" << std::endl;
}

std::string Room::get_name(){return _name;}

void Room::add_client(unsigned short port, std::string addr, asio::ip::tcp::socket socket) 
{
    _clients.push_back(new Client(_io_context, std::move(socket), port, addr));
    last_nbr_cli += 1;
}

int Room::getPort()
{
    return _udp_socket.local_endpoint().port();
}

void show_bin(int nb) {
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

void Room::send_update(command cmd, std::string msg, int id) {
    _game_buffer.packet.cmd = cmd;
    std::cout << "CMD:" << cmd << "| MSG: " << msg << std::endl;
        for (int i = 0; i < 256; i++) {
        if (_game_buffer.packet.msg[i] == 0)
            break;
    }

    for (int i = 0; i < msg.size(); i++)
        _game_buffer.packet.msg[i] = msg[i];
    _game_buffer.packet.msg[msg.size()] = '\0';
  
    std::cout << "Clients: " << _clients.size() << std::endl;
    for (int i = 0; i < _clients.size(); i++) {
        if (_clients[i]->id == id) {
            asio::ip::udp::resolver resolver_(_io_context);
            asio::ip::udp::resolver::results_type endpoints = resolver_.resolve(asio::ip::udp::v4(), _clients[i]->get_ip_addr().c_str(), std::to_string(_clients[i]->get_udp_port()).c_str());
            _udp_socket.send_to(asio::buffer(&_game_buffer, sizeof(_game_buffer)), *endpoints.begin());
        }
    }
}

void Room::send_update_room(command cmd, std::string msg) {
    _game_buffer.packet.cmd = cmd;
    for (int i = 0; i < 256; i++) {
        if (_game_buffer.packet.msg[i] == 0)
            break;
    }

    for (int i = 0; i < msg.size(); i++)
        _game_buffer.packet.msg[i] = msg[i];
    _game_buffer.packet.msg[msg.size()] = '\0';
  
    for (int i= 0; i < _clients.size(); i++) {
        if (_clients[i]->id != -1) {
            asio::ip::udp::resolver resolver_(_io_context);
            asio::ip::udp::resolver::results_type endpoints = resolver_.resolve(asio::ip::udp::v4(), _clients[i]->get_ip_addr().c_str(), std::to_string(_clients[i]->get_udp_port()).c_str());
            _udp_socket.send_to(asio::buffer(&_game_buffer, sizeof(_game_buffer)), *endpoints.begin());
        }
    }
}

void Room::send_update(command cmd, std::string msg) {
    _game_buffer.packet.cmd = cmd;
//    std::cout << "start write" << msg <<  std::endl;
    Serializer *serializer_ = new Serializer(msg);


//   if (cmd == GAME_INIT || cmd == GAME_UPDATE) {
//        std::cout << "get here" << std::endl;
//        std::cout << "MYMSG:" << msg << "%\n";
//        serializer_->serialize();
//        _game_buffer = *(serializer_->get_packet());
//        _game_buffer.packet.cmd = cmd;
//        std::cout << "MYMSG serialized:" << serializer_->get_packet()->packet.msg << std::endl; 
//        std::cout << "get out" << std::endl;
//   } else {
        for (int i = 0; i < 5000; i++) {
            _game_buffer.packet.msg[i] = 0;
        }
        for (int i = 0; i < msg.size(); i++) {
            _game_buffer.packet.msg[i] = msg[i];
        }
//   }
//    std::cout << (int)_game_buffer.packet.cmd << " " << _game_buffer.packet.msg << std::endl;

    for (int i= 0; i < _clients.size(); i++) {
        asio::ip::udp::resolver resolver_(_io_context);
        asio::ip::udp::resolver::results_type endpoints = resolver_.resolve(asio::ip::udp::v4(), _clients[i]->get_ip_addr().c_str(), std::to_string(_clients[i]->get_udp_port()).c_str());
         _udp_socket.send_to(asio::buffer(&_game_buffer.packet, sizeof(_game_buffer.packet)), *endpoints.begin());
    }
//    std::cout << "end write" << std::endl;
//    delete serializer_;
}

void Room::getMessage() {
    _udp_socket.async_receive_from(
        asio::buffer(&_game_buffer, sizeof(_game_buffer)), sender_endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            if (!ec && bytes_recvd > 0)
            {
                std::cout << "cmd: " << (int)_game_buffer.packet.cmd << std::endl;
                if (_game_buffer.packet.cmd == LAUNCH_GAME)
                {
                    if (_clients.size() == 2) {
                        _logics->setState(START_GAME);
                        _state = START_GAME;
                    } else {
                        std::cout << "NO" << std::endl;
                    }
                } 
                else if (_game_buffer.packet.cmd == CLIENT_GIVE_IP) {
                    for (int i = 0; i < _clients.size(); i++) {
                        std::cout << "our:" << _clients[i]->get_udp_port() << " him:" << sender_endpoint.port() << std::endl;
                        if (_clients[i]->get_udp_port() == sender_endpoint.port()) {
                            _clients[i]->set_addr(sender_endpoint.address().to_string());
                            std::cout << "get one" << std::endl;
                            _game_buffer.packet.cmd = GIVE_NBR_TO_CLI;
                            _clients[i]->id = i;
                            std::string raw_msg(std::to_string(i));
                            for (int i = 0; i < raw_msg.size(); i++)
                                _game_buffer.packet.msg[i] = raw_msg[i];
                            asio::ip::udp::resolver resolver_(_io_context);
                            asio::ip::udp::resolver::results_type endpoints = resolver_.resolve(asio::ip::udp::v4(), _clients[i]->get_ip_addr().c_str(), std::to_string(_clients[i]->get_udp_port()).c_str());
                            _udp_socket.send_to(asio::buffer(&_game_buffer, sizeof(_game_buffer)), *endpoints.begin());
                        }
                    }
                } else if (_game_buffer.packet.cmd == PLAYER_INPUT) {
                    std::cout << "INPUT" << reinterpret_cast<const char*>(_game_buffer.packet.msg) << std::endl;
                    ////!\/// 
                    for (int i = 0; i < _clients.size(); i++)
                        if (_clients[i]->get_udp_port() == sender_endpoint.port()) {
                            _clients[i]->add_msg_to_queue(std::string(reinterpret_cast<const char*>(_game_buffer.packet.msg)));
                        }
                } else if (_game_buffer.packet.cmd == DISCONNECT) {
                    for (int i = 0; i < _clients.size(); i++)
                        if (_clients[i]->get_udp_port() == sender_endpoint.port()) {
                            std::cout << _game_buffer.packet.msg << "disconnected" << std::endl;
                            send_update(DISCONNECT, "DISCONNECTED", _clients[i]->id);
                            _clients.erase(_clients.begin() + i);
                            if (last_nbr_cli - 1 > 0)
                                last_nbr_cli -= 1;
                            else
                                last_nbr_cli = -1;
                        }
                }
            }
            else {
                std::cout << "error reading UDP\n";
            }
            getMessage();
        });
}

void Room::backend_operation_handling() {
    sleep(2);
    std::cout << "Start backend handling" << std::endl; 
    Clock *clock_game_loop = new Clock();

    while (_logics != NULL) {
        if (clock_game_loop->getTime().count() > 0.05)
        {
            _logics->state_handling(_clients);
            std::string msg(_logics->getLastestSnapshot());
            command cmd = _logics->getLastestSnapshotType();
            if (cmd != EOP && (cmd == GAME_UPDATE || cmd == GAME_INIT)) {
                send_update(cmd, msg);
            } else if (cmd == ROOM_PLAYER || cmd == WIN) {
                send_update_room(cmd, msg);
            }
            clock_game_loop->restartTime();
        }
    //    if (last_nbr_cli == -1)

    }
}