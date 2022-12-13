/*
** EPITECH PROJECT, 2022
** __SERVER__
** File description:
** A
*/

#include "Lobby_session.hpp"
#include "Room.hpp"
#include "Server.hpp"
class Lobby_session;

Server::Server(asio::io_context& io_context, short port) : _io_context(io_context), _acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), _thread_backend(&Server::console_log, this)
{
    system(CMD_IP);
    do_accept();
}

Room *Server::get_room(std::string name)
{
    for (auto room : _rooms)
    {
        if (room->get_name().compare(name) == 0)
        {
            return room;
        }
    }
    return NULL;
}

void Server::delete_lobbie(Lobby_session *lobby_to_del)
{
    for (int i = 0 ; i < _lobbies.size() ; i++)
    {
        if (_lobbies[i] == lobby_to_del)
        {
            delete _lobbies.at(i);
            _lobbies.erase(_lobbies.begin() + i);
        }
    }
}

void Server::add_room(std::string name) {
    _rooms.insert(_rooms.begin(), new Room(_io_context, name));
}

void Server::remove_room(std::string name) {
    for (int i = 0; i < _rooms.size(); i++)
        if (_rooms[i]->get_name() == name) {
//            delete _rooms[i];
            _rooms[i]->destroy();
            _rooms.erase(_rooms.begin() + i);
        }
}

void Server::do_accept() 
{
    _acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket)
    {
        if (!ec) {
            std::cout << "I ACCEPT A CLIENT IN TCP\n\n";
            _lobbies.emplace_back(new Lobby_session(std::move(socket), this));
        }
        do_accept();
    });
//    get_cmd();
}

std::vector<Room *> Server::getRooms() {
    return _rooms;
}

void Server::show_list_room(void) {
    std::cout << "\t[";
    for (int i = 0; i < _rooms.size(); i++) {
        std::cout << "\""<< _rooms[i]->get_name() << "\"";
        if (i < _rooms.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}

void Server::show_info(std::string cmd) {
    if (cmd.find("Room") == 0 && cmd.size() == std::string("Room").size())
        show_list_room();
    else if (cmd.find("Room ") == 0) {
        std::string name = cmd.substr(std::string("Room ").size(), cmd.find(' ', cmd.find(' ') + 1) - (cmd.find(' ') + 1));
        Room *selected_room = get_room(name);
        if (selected_room == NULL)
            std::cout << "Error: Room \"" << name << "\" not find" << std::endl;
        else {
            std::cout << "State: " << selected_room->state_str_Room() << "|" << selected_room->getlast_cli() << "." << std::endl;
            std::cout <<  selected_room->clients_nbr_in_room() << " Player(s) connected" << std::endl;
        }
    } else if (cmd.find("Player Connected") == 0)
        std::cout << _lobbies.size() << "Players Connected" << std::endl;
}

void show_help() {
    std::cout << "Commands Availables: \n";
    std::cout << "Show Room\t\n";
    std::cout << "Show Room [name]\n";
    std::cout << "Show Player Connected\n";
    std::cout << "Add Room [name]\n";
    std::cout << "Remove Room [name]\n";
}

void Server::handle_cmd(std::string cmd) {
    if (cmd.find("Show") == 0)
        show_info(cmd.substr(std::string("Show ").size()));
    else if (cmd.find("Add Room ") == 0) {
        while (cmd.find("\"") < cmd.size())
            cmd.replace(cmd.find("\""), 1, "");
        add_room(cmd.substr(std::string("Add Room ").size(), cmd.find(" ", std::string("Add Room ").size()) - std::string("Add Room ").size()));
    } else if (cmd.find("Remove Room ") == 0) {
        remove_room(cmd.substr(std::string("Remove Room ").size(), cmd.find(" ", std::string("Remove Room ").size()) - std::string("Remove Room ").size()));
    } else if (cmd.find("Help") == 0 || cmd.find("help") == 0) {
        show_help();
    } else {
        if (cmd.find(' ') > 0 && cmd.find(' ') < cmd.size())
            std::cout << "Error: Command not found \"" << cmd.substr(0, cmd.find(' ')) << "\"." << std::endl;
        else
            std::cout << "Error: Command not found \"" << cmd << "\"." << std::endl;
    }
}

void Server::update_room(void)
{
        for (int i = 0; i < _rooms.size(); i++)
            if (_rooms[i]->getlast_cli() == -1) {
                //std::cout << "Hello" << std::endl;
                _rooms.erase(_rooms.begin() + i);
            }
    
}

void Server::console_log(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    exit = 0;
    char msg_1[100];
    std::string all_cmd;
    std::cout << "$> ";
    while (exit == 0) {
        std::cin.getline(msg_1, 100, '\n');
        update_room();
        if (std::string(msg_1).find("exit") == 0) {
            exit = 1;
        } else {
            handle_cmd(std::string(msg_1));
            std::cout << "$> ";
        }
    }
}