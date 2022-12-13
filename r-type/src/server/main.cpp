/*
** EPITECH PROJECT, 2022
** server_tcp_udp
** File description:
** server
*/

#include "Server.hpp"

int main(int ac, char **av) 
{
    try {
        asio::io_context io_context;
        if (ac != 2)
        {
            std::cout << "wrong arg" << std::endl;
            return 84;
        }

        Server server(io_context, atoi(av[1]));
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}