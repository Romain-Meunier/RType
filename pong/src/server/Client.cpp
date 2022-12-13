/*
** EPITECH PROJECT, 2022
** __CLIENT__
** File description:
** __CLIENT__
*/

#include "Client.hpp"

Client::Client(asio::io_context& io_context, asio::ip::tcp::socket socket, unsigned short port, std::string addr): _tcp_socket(std::move(socket))
{
    std::cout << "get port:" << port << std::endl;
    _ip_addr = addr;
//    _ip_addr = socket.remote_endpoint().address().to_string();
//    _tcp_port = port;
    _udp_port = port;
    id = -1;
}

unsigned short Client::get_tcp_port(){return _tcp_port;};

unsigned short Client::get_udp_port(){return _udp_port;};

std::string Client::get_ip_addr(){return _ip_addr;};

void Client::set_addr(std::string addr) {_ip_addr = addr;};

void Client::add_msg_to_queue(std::string msg) {_msg_queue.push_back(msg);};

std::string Client::pop_message() {
    if (!_msg_queue.empty()) {
        std::string msg_cpy = _msg_queue[0];
        _msg_queue.erase(_msg_queue.begin());
        return msg_cpy;
    }
    return nullptr;
};

std::vector<std::string> Client::get_message_queue() {return _msg_queue;};

void Client::empty_queue() {
    while (!_msg_queue.empty()) {
        _msg_queue.pop_back();
    }
};