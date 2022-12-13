/*
** EPITECH PROJECT, 2022
** __NETWORK__
** File description:
** __NETWORK__
*/

#pragma once

#include "Deserializer.hpp"
#include "Data_Network.hpp"

class Network {
    public:
        Network(asio::io_context& io_context, short port, std::string server_ip) /* :_io_context(io_context), _resolver(_io_context), _socket(_io_context) */;
        ~Network();
        void destroy();
        int connect();
        void tcp_read();
        void tcp_write(std::string choice);
        void tcp_write(std::string choice, std::string name_room);
        void udp_write(command cmd, std::string msg);
        void udp_read();
//        void set_core_state( state_core_e *menu);

        void serializer(std::string msg);
        std::string unserializer(GameMessage cry);
        std::string getLastestSnapshot() {if (_update.size() > 0) return _update[0];return "";};
        int change_state();
        std::string get_info();
        
        std::vector<std::string> _update;
        int get_id() {return _id_client;};
        int _id_client;
        int _clients_in_room;
        int end_thread;
        std::string _win_or_lose;
    protected:
    private:
        void buffer_reset();
        void disconnected_cmd(); //leave
        void lobby_create_room(); // create & join

        asio::io_context& _io_context;

        asio::ip::tcp::socket _socket;
        asio::ip::tcp::resolver _resolver;

        asio::ip::udp::resolver _udp_resolver;
        asio::ip::udp::socket _s_udp;

        requestMessage _buffer;

        GameMessage _game_buffer;
        GameMessage _game_buffer_res;
        t_server server_info;

        std::thread _reading_session;
        state_core_e _core_state;
        state_core_e _tmp_state;
        Deserializer *_deserializer;
        
};

typedef struct network_s {
    Network *network;
} network_t;
