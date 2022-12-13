/*
** EPITECH PROJECT, 2022
** server.h
** File description:
** server
*/

#pragma once

#include <iostream>
#include "asio.hpp"

// ipconfig | findstr /c:"Adresse IP"

#ifdef _WIN32
#define NAME_FIND "IP"
#define CMD_IP "ipconfig | findstr /c:" NAME_FIND

#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#endif //_WIN32

#ifdef linux
#define NAME_FIND " inet "
#define CMD_IP " ifconfig | grep -i " NAME_FIND
#endif //linux

#ifdef __APPLE__
#define NAME_FIND " inet "
#define CMD_IP " ifconfig | grep -i " NAME_FIND
#endif //__APPLE__


class Room;
class Lobby_session;

class Server: std::enable_shared_from_this<Server>
{
    public:
        Server(asio::io_context& io_context, short port);
        std::vector<Room *> getRooms();
        void add_room(std::string name);
        Room *get_room(std::string name);
        void delete_lobbie(Lobby_session *lobby_to_del);

        void console_log(void);
    private:
        void remove_room(std::string name);
        void show_info(std::string cmd);
        void show_list_room(void);
        void handle_cmd(std::string cmd);
        void do_accept();
        void update_room(void);

    std::vector<Room *> _rooms;
    asio::io_context& _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<Lobby_session *> _lobbies;
//        asio::ip::tcp::socket _socket;
    std::thread _thread_backend;
    int exit;
};


