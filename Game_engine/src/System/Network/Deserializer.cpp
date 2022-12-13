/*
** EPITECH PROJECT, 2022
** epitechTek3 [WSL : Ubuntu-20.04]
** File description:
** Deserializer
*/

#include "Deserializer.hpp"

Deserializer::Deserializer(GameMessage *packet, int msg_len)
{
    _cursor_msg = 0;
    _msg_len = msg_len;
    _packet = packet;
    
}

Deserializer::~Deserializer()
{
}

std::string Deserializer::get_deserialized_msg()
{
    if (_deserialized_msg.size() == std::string("GAME$").size())
        return "";
    return _deserialized_msg;
}

std::vector<std::string> Deserializer::parse_string(std::string s, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);
    while (getline(ss, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

void Deserializer::show_binary(size_t len, unsigned char *array)
{
    for (int u = 0 ; u <= len ; u++)
    {
        for (int i = 7; i >= 0; --i)
        {
            std::cout << ((array[u] >> i) & 0x1);
        }
        std::cout << '\n';
    }
}

std::string Deserializer::get_type_from_byte(unsigned char byte)
{
    for (auto it : map_of_type)
    {
        if (it.second == byte)
            return it.first;
    }
    return std::string("Nul");
}

std::vector<std::string> Deserializer::get_n_next_byte_as_str(int n)
{
    std::string tmp_str;
    std::vector<std::string> tmp_vect;

    for (int i = _cursor_msg ; i < _cursor_msg + n ; i++)
    {
        for (int u = 0 ; u < 8 ; u++)
        {
            if ((_packet->packet.msg[i] >> u) & 1)
                tmp_str += "1";
            else
                tmp_str += "0";
        }
        ///////
        tmp_vect.push_back(tmp_str);
        tmp_str.clear();
    }
    _cursor_msg += n;
    return tmp_vect;
}

unsigned char Deserializer::set_char_with_str(std::string str)
{
    unsigned char byte = 0;

    for (int i = 7 ; i >= 0 ; i--)
    {
        if (str[i] == '1')
        {
            byte |= 1 << i;
        }
        else if (str[i] == '0')
        {
            byte &= ~(1 << i);
        }
    }
    return byte;
}

unsigned short Deserializer::set_short_with_str(std::string byte_a_str, std::string byte_b_str)
{
    unsigned char byte_a = 0;
    unsigned char byte_b = 0;
    unsigned short val;

    for (int i = 7 ; i >= 0 ; i--)
    {
        if (byte_a_str[i] == '1')
        {
            byte_a |= 1 << i;
        }
        else if (byte_a_str[i] == '0')
        {
            byte_a &= ~(1 << i);
        }
    }

    for (int i = 7 ; i >= 0 ; i--)
    {
        if (byte_b_str[i] == '1')
        {
            byte_b |= 1 << i;
        }
        else if (byte_b_str[i] == '0')
        {
            byte_b &= ~(1 << i);
        }
    }
    val = byte_a;
    val <<= 8;
    val |= byte_b;
    return val;
}

void Deserializer::deserialize_entity(std::string type)
{
    std::vector<std::string> bytes;
    unsigned char nbr = 0;
    short x = 0;
    short y = 0;
    unsigned char state = 0;

    bytes = get_n_next_byte_as_str(6);
    nbr = set_char_with_str(bytes[0]);
    x = set_short_with_str(bytes[1], bytes[2]);
    y = set_short_with_str(bytes[3], bytes[4]);
    state = set_char_with_str(bytes[5]);
    _deserialized_msg += type + "/" + std::to_string(static_cast<int>(nbr)) + ":" + std::to_string(x) + "." + std::to_string(y) + "|!" + std::to_string(state) +"|\n";
}

void Deserializer::deserialize_bullet_vector(std::string type)
{
    unsigned char nbr = 0;
    unsigned short x = 0;
    unsigned short y = 0;
    std::vector<std::string> bytes;
    int id_bullet = 0;
    bytes = get_n_next_byte_as_str(1);
    nbr = set_char_with_str(bytes[0]);
    _deserialized_msg += type + "/" + std::to_string(static_cast<int>(nbr)) + ":";
    for (int i = 0 ; i < static_cast<size_t>(nbr) ; i++)
    {
        bytes = get_n_next_byte_as_str(5);
        id_bullet = set_char_with_str(bytes[0]);
        x = set_short_with_str(bytes[1], bytes[2]);
        y = set_short_with_str(bytes[3], bytes[4]);
        _deserialized_msg += std::to_string(id_bullet) + "*" + std::to_string(x) + "." + std::to_string(y) + "|";
    }
    if (_deserialized_msg.back() == ':')
            _deserialized_msg.append("|");
    _deserialized_msg += "\n";
}

void Deserializer::decompress_msg()
{
    int src_size = _packet->packet.src_size;
    int compressed_data_size = _packet->packet.compressed_data_size;

    char* const regen_buffer = (char*)malloc(src_size);
    const int decompressed_size = LZ4_decompress_safe(reinterpret_cast<char const *>(_packet->packet.msg), regen_buffer, compressed_data_size, src_size);
    // free(_packet->compressed_data);   /* no longer useful */

    for (int i = 0 ; i < 5000 ; i++)
        _packet->packet.msg[i] = 0;
    for (size_t i = 0 ; i < src_size ; i++)
        _packet->packet.msg[i] = regen_buffer[i];
    // memcmp(_packet->packet.msg, tmp, src_size);
}

void Deserializer::deserialize()
{
    _deserialized_msg.append("GAME$");
    std::vector<std::string> bytes;
    unsigned char byte = 0;
    std::string type;

    decompress_msg();
    while(1)
    {
        bytes = get_n_next_byte_as_str(1);
        byte = set_char_with_str(bytes[0]);

        if (byte == 0)
            break;
        type = get_type_from_byte(byte);
        if (type.compare("Nul") == 0)
        {
            std::cout << "ERROR: type not found when deserializing\n";
            // break;
        }
        if (type.rfind("B_", 0) == 0)
        {
            deserialize_bullet_vector(type);
        }
        else
        {
            deserialize_entity(type);
        }
    }
}
