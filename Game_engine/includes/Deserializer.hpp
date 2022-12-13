#ifndef DESERIALIZER_HPP_
#define DESERIALIZER_HPP_
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <cstring>
#include "Data_Network.hpp"
#include "lz4.h"

class Deserializer {
    public:
        Deserializer(GameMessage *packet, int msg_len);
        ~Deserializer();
        void deserialize();
        std::string get_deserialized_msg();
    protected:
    private:
        void show_binary(size_t len, unsigned char *array);
        std::string get_type_from_byte(unsigned char byte);
        void deserialize_bullet_vector(std::string type);
        void deserialize_entity(std::string type);
        std::vector<std::string> get_n_next_byte_as_str(int n);
        std::vector<std::string> parse_string(std::string s, char delim);
        unsigned char set_char_with_str(std::string str);
        unsigned short set_short_with_str(std::string byte_a_str, std::string byte_b_str);
        char reverse(char b);
        void decompress_msg();

        GameMessage *_packet;
        std::string _deserialized_msg;
        int _cursor_msg;
        int _msg_len;
};

#endif /* !DESERIALIZER_HPP_ */