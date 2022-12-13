/*
** EPITECH PROJECT, 2022
** CLIENT
** File description:
** A
*/

#pragma once

#include <iostream>
#include "asio.hpp"

class Client
{
    public:
        Client(asio::io_context& io_context, asio::ip::tcp::socket socket, unsigned short port, std::string addr);
        unsigned short get_tcp_port();
        unsigned short get_udp_port();
        std::string get_ip_addr();
        void set_addr(std::string addr);
        void add_msg_to_queue(std::string msg);
        std::string pop_message();
        std::vector<std::string> get_message_queue();
        void empty_queue();
        int id;
    private:
//        asio::ip::udp::socket _udp_socket;
//        asio::ip::udp::endpoint _sender_endpoint_;
        unsigned short _udp_port;
        unsigned short _tcp_port;
        asio::ip::tcp::socket _tcp_socket;
        std::string _ip_addr;
        std::vector<std::string> _msg_queue;
};
