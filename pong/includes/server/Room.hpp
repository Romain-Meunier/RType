/*
** EPITECH PROJECT, 2022
** Room.hpp
** File description:
** r-type server
*/

#pragma once

#include <iostream>
#include "asio.hpp"
#include "Client.hpp"
#include <Data_Network.hpp>
#include <chrono>
#include "Player.hpp"
#include "Ball.hpp"
/*
#include "Kamikaze.hpp"
#include "TIEHunter.hpp"
#include "Boss.hpp"
#include "MiniBoss.hpp"
*/
#include "Clock.hpp"
#include "Serializer.hpp"

enum State_Room {
    MENU = 0,
    START_GAME = 1,
    IN_GAME = 2,
    NOTHING = 6,
    LEAVE = 7
};

class Logic {
    public:
        Logic();
        ~Logic();
        void setState(State_Room state) {_state = state;};
        std::string getLastestSnapshot(void);
        command getLastestSnapshotType(void);
        void handle_ball();
        void update_game(std::vector<Client *> clients);
        void mooving_player(std::vector<Client *> clients);
        void mooving_mob();
        void mooving_bullet();
        int check_victory();
//        void add_bullet(Bullet *bullet);
        void state_handling(std::vector<Client *> clients);
        void update_menu(std::vector<Client *> clients);
        void init_player(std::vector<Client *> clients);
        void check_state_game();
        void update_state_of_monster();
        void update_state_of_player(std::vector<Client *> clients);
        void update_state(std::vector<Client *> clients);
        void create_snapshot();

    private:
        std::vector<std::string> _snapshot;
        std::vector<command> _type_snap;
        State_Room _state;
        State_Room _next_state;

        Clock *_clock_game_loop;
        Clock *_clock_lvl_transi;
        Clock *_clock_mob_spawn;
//        std::vector<Mob *> _mobs;
        std::vector<Player *> _player_vect;
        std::vector<Ball *> _balls;
//        std::vector<Bullet *> _bullets;
        int _bool_test;
};

class Room
{
    public:
        Room(asio::io_context& io_context, std::string name);
        ~Room();
        void destroy();
        void add_client(unsigned short port, std::string addr, asio::ip::tcp::socket socket);
        int getPort();
        void getMessage();
        std::string get_name();
        void send_update(command cmd, std::string msg);
        void send_update_room(command cmd, std::string msg);
        void send_update(command cmd, std::string msg, int id);
        void backend_operation_handling();
        std::string update_game();
        void init_player();
        void check_state_game();
        int clients_nbr_in_room() {
            return _clients.size();
        }
        int state_Room(void) {
            if (_state == MENU)
                return 0;
            else 
                return 1;
        }
        std::string state_str_Room(void) {
            if (_state == MENU)
                return "MENU";
            else 
                return "GAME";

        }
        int getlast_cli(void) {
            return last_nbr_cli;
        }        

    private:
        asio::ip::udp::endpoint sender_endpoint;
        asio::io_context& _io_context;
        asio::ip::udp::socket _udp_socket;
        GameMessage _game_buffer;
        GameMessage _game_buffer_res;
        requestMessage buffer;

        std::thread _thread_backend;

        Logic *_logics;

        std::vector<Client *> _clients;
        std::string _name;
//        Serializer *_serializer;
        Clock *_clock_game_loop;
        State_Room _state;
        int last_nbr_cli;
};