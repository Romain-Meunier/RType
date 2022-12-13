/*
** EPITECH PROJECT, 2022
** data_network.hpp
** File description:
** Network
*/

#pragma once

#include "asio.hpp"
#include <iostream>
#include <thread>
#include <string.h>

#define NB_OF_TYPE 10
static std::pair<std::string, unsigned char> map_of_type[] =
{
    {"PLAYER", 1},
    {"Kamikaze", 2},
    {"TIEHunter", 3},
    {"B_BLASTER_ALLY", 4},
    {"B_ROCKET_MOB", 5},
    {"B_OMNI", 6},
    {"BOSS", 7},
    {"MINIBOSS", 8},
    {"B_ELECTRIC_ALLY", 9},
    {"B_BARRAGE_ALLY", 10}
    // {"", Nul}/*
};

enum state_core_e {
    NONE,
    START_STATUS,
    CONNECT_STATUS,
    JOIN_STATUS,
    CREATE_STATUS,
    INIT_ROOM_STATUS,
    ROOM_STATUS,
    GAME_INIT_STATUS,
    GAME_RUNNING_STATUS,
    WIN_STATUS
};

enum command
{
    EOP = 0,
    DISCONNECT = 1,
    JOIN_ROOM = 2,
    CREATE_ROOM = 3,
    

    READ_MSG = 4,

    LAUNCH_GAME = 5,

    GAME_INIT = 6,
    GAME_UPDATE = 7,

    ENTER_ROOM = 8,
    PLAYER_INPUT = 9,

    GIVE_NBR_TO_CLI = 10,
    ROOM_PLAYER = 11,

    ROOM_ACCEPT = 12,
    ROOM_ACCESS_DENIED = 13,

    WIN = 14,

    CLIENT_GIVE_IP = 125,
    SERVER_GIVE_ROOM_PORT = 126
};

enum type
{
    COMPONENT_LIFE_INDEX = 0,
    COMPONENT_POSITION_INDEX = 1
};

#define NB_TYPE_BULLET 5
enum type_bullet
{
    BLASTER_ALLY,
    ROCKET_MOB,
    OMNI,
    ELECTRIC_ALLY,
    BARRAGE_ALLY
};

typedef struct server_info {
    unsigned short port_tcp;
    unsigned short port_udp;
    std::string ip;
} t_server;

//for TCP
struct requestMessage
{
    char cmd;
    struct {
        char strlen;
        char msg[256];
        unsigned short port;
        char addr[16];
    };
};

//for UDP
typedef struct packet_s
{
    char cmd;
    unsigned char msg[5000];
    int compressed_data_size;
    int src_size;
}packet_t;

struct GameMessage {
    packet_t packet;
    size_t cursor_msg;
    char *compressed_data;
};

enum type_snapshot
{
    INFO,
    GAME
};
