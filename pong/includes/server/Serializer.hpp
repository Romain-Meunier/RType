/*
** EPITECH PROJECT, 2022
** epitechTek3 [WSL : Ubuntu-20.04]
** File description:
** Serializer
*/

#ifndef SERIALIZER_HPP_
#define SERIALIZER_HPP_
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <cstring>
#include <Data_Network.hpp>
#include "lz4.h"
#include "macro.hpp"
class Serializer {
    public:
        Serializer(std::string raw_msg);
        ~Serializer();
        void serialize();
        GameMessage *get_packet();

    protected:
    private:
        std::vector<std::string> parse_string(std::string s, char delim);
        void init_packet();
        void encode_id_player(std::string id);
        void encode_id_mob(std::string id);
        void encode_id_bullet(std::string id);
        void encode_coord_entity(std::string coords);
        void encode_coord_bullet_vector(std::string coords);
        void compress_msg();
        void run_screaming(const char* message, const int code);
        std::string _raw_msg;
        GameMessage * _packet;
        type_snapshot _type;
};

#endif /* !SERIALIZER_HPP_ */
