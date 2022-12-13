/*
** EPITECH PROJECT, 2022
** Lobby_session.hpp
** File description:
** r-type server
*/

#pragma once

#include <iostream>
#include "asio.hpp"
#include "Server.hpp"
#include <Data_Network.hpp>

class Server;
class Room;

class Lobby_session: std::enable_shared_from_this<Lobby_session> 
{
    public:
        Lobby_session(asio::ip::tcp::socket socket, Server* server);
        ~Lobby_session();
        void handle();
        void create_room_cmd();
        void cmd_create_room();
        void cmd_join_room();
        void join_room_cmd();
        void disconnect_cmd();

    private:
        requestMessage _buffer;
        requestMessage buffer;
        Server* _server;
        asio::ip::tcp::socket _socket;
        enum { max_length = 1024 };
        char data_[max_length];
        int _id;
        int state;
};