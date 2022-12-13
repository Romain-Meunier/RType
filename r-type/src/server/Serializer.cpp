/*
** EPITECH PROJECT, 2022
** epitechTek3 [WSL : Ubuntu-20.04]
** File description:
** Serializer
*/

#include "Serializer.hpp"
#include "Deserializer.hpp"
Serializer::Serializer(std::string raw_msg)
{
    _packet = new GameMessage;
    // _packet->packet. new packet_t;
    _raw_msg = raw_msg;
    std::vector<std::string> tmp_vect = parse_string(_raw_msg, '$');
    if (tmp_vect[0].compare("INFO") == 0)
    {
        _type = INFO;
        _raw_msg = tmp_vect[1];
    }
    else if (tmp_vect[0].compare("GAME") == 0)
    {
        _type = GAME;
        _raw_msg = tmp_vect[1];
    }
}

Serializer::~Serializer()
{
}

void Serializer::run_screaming(const char* message, const int code)
{
    printf("%s \n", message);
    // exit(code);
}

std::vector<std::string> Serializer::parse_string(std::string s, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);
    while (getline(ss, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

GameMessage *Serializer::get_packet()
{
    return _packet;
}

void Serializer::init_packet()
{
    _packet->packet.cmd = GAME_UPDATE;
    _packet->cursor_msg = 0;
    for (int i = 0; i < 256; i++)
        _packet->packet.msg[i] = 0;
}

void Serializer::encode_coord_bullet_vector(std::string coords)
{
    std::vector<std::string> coords_parsed = parse_string(coords, '|');
    std::vector<std::string> tmp_coord;
    std::vector<std::string> tmp_coord_bis;
    short x = 0;
    short y = 0;

    for (auto line : coords_parsed)
    {
        tmp_coord_bis = parse_string(line, '*');
        tmp_coord = parse_string(tmp_coord_bis[1], '.');
        _packet->packet.msg[_packet->cursor_msg] = std::stoi(tmp_coord_bis[0]); // to copy the first 8 bits.
        _packet->cursor_msg++;
        x = static_cast<short>(std::stoi(tmp_coord[0]));
        y = static_cast<short>(std::stoi(tmp_coord[1]));
        _packet->packet.msg[_packet->cursor_msg] = x >> 8; // to copy the first 8 bits.
        _packet->cursor_msg++;
        // x = x >> 8; //push the other 8 bits to the right
        _packet->packet.msg[_packet->cursor_msg] = x;
        _packet->cursor_msg++;

        _packet->packet.msg[_packet->cursor_msg] = y >> 8; // to copy the first 8 bits.
        _packet->cursor_msg++;
        // y = y >> 8; //push the other 8 bits to the right
        _packet->packet.msg[_packet->cursor_msg] = y; 
        _packet->cursor_msg++;
    }
}

void Serializer::encode_coord_entity(std::string coords)
{
    std::vector<std::string> coords_parsed = parse_string(coords, '|');
    std::vector<std::string> tmp_coord;
    short x = 0;
    short y = 0;
    short tmp_short = 0;

    for (auto line : coords_parsed)
    {
        if (line[0] == '!')
        {
            line.erase(0, 1);
            _packet->packet.msg[_packet->cursor_msg] = std::stoi(line);
            _packet->cursor_msg++;
        }
        else
        {
            tmp_coord = parse_string(line, '.');
            x = static_cast<short>(std::stoi(tmp_coord[0]));
            y = static_cast<short>(std::stoi(tmp_coord[1]));
            _packet->packet.msg[_packet->cursor_msg] = x >> 8; // to copy the first 8 bits.
            _packet->cursor_msg++;
            // x = x >> 8; //push the other 8 bits to the right
            _packet->packet.msg[_packet->cursor_msg] = x;
            _packet->cursor_msg++;

            _packet->packet.msg[_packet->cursor_msg] = y >> 8; // to copy the first 8 bits.
            _packet->cursor_msg++;
            // y = y >> 8; //push the other 8 bits to the right
            _packet->packet.msg[_packet->cursor_msg] = y; 
            _packet->cursor_msg++;
        }
    }
}

void Serializer::compress_msg()
{
    unsigned char* src = (unsigned char *) malloc(sizeof(char) * _packet->cursor_msg);
    // std::string src;
    int src_size = 0;
    int max_dst_size = 0;
    char* compressed_data = NULL;
    
    for (size_t i = 0 ; i < _packet->cursor_msg ; i++)
        src[i] = _packet->packet.msg[i];

    src_size = _packet->cursor_msg;
    max_dst_size = LZ4_compressBound(src_size);
    compressed_data = (char*)malloc((size_t)max_dst_size);
    if (compressed_data == NULL)
        run_screaming("Failed to allocate memory for *compressed_data.", 1);
    const int compressed_data_size = LZ4_compress_default(reinterpret_cast<const char*>(src), compressed_data, src_size, max_dst_size);
    if (compressed_data_size <= 0)
        run_screaming("A 0 or negative result from LZ4_compress_default() indicates a failure trying to compress the data. ", 1);

    compressed_data = (char *)realloc(compressed_data, (size_t)compressed_data_size);
    // if (compressed_data == NULL)
    //     run_screaming("Failed to re-alloc memory for compressed_data.  Sad :(", 1);
    _packet->compressed_data = compressed_data;
    _packet->packet.compressed_data_size = compressed_data_size;
    _packet->packet.src_size = src_size;
    for (int i = 0 ; i < 5000 ; i++)
        _packet->packet.msg[i] = 0;
    for (size_t i = 0 ; i < compressed_data_size ; i++)
        _packet->packet.msg[i] = _packet->compressed_data[i];
}

void Serializer::serialize()
{
    if (_type == GAME)
    {
        std::string id;
        std::string nbr;
        std::string coords;
        std::vector<std::string> tmp_vect;
        std::vector<std::string> tmp_vect_bis;
        std::vector<std::string> raw_msg_parsed = parse_string(_raw_msg, '\n');

        init_packet();
        for (auto line : raw_msg_parsed)
        {
            tmp_vect = parse_string(line, '/');
            id = tmp_vect[0];
            tmp_vect_bis = parse_string(tmp_vect[1], ':');
            nbr = tmp_vect_bis[0];
            coords = tmp_vect_bis[1];

            for (auto it : map_of_type)
            {
                if (it.first.compare(id) == 0)
                {
                    _packet->packet.msg[_packet->cursor_msg] = it.second;
                    _packet->cursor_msg++;

                    _packet->packet.msg[_packet->cursor_msg] = stoi(nbr);
                    _packet->cursor_msg++;
                    if (id.rfind("B_", 0) == 0)
                    {
                        if (stoi(nbr) > 0)
                            encode_coord_bullet_vector(coords);
                    }
                    else
                        encode_coord_entity(coords);
                }
            }
        }
        compress_msg();
    }
    else if (_type == INFO)
    {
        std::string id;
        std::string nbr;
        std::string health;
        std::string coords;
        std::vector<std::string> tmp_vect;
        std::vector<std::string> line_parsed;
        std::vector<std::string> raw_msg_parsed = parse_string(_raw_msg, '\n');
        int nb_of_entity = std::stoi(raw_msg_parsed[0]);
        raw_msg_parsed.erase(raw_msg_parsed.begin());
        int count = 0;

        for (auto line : raw_msg_parsed)
        {
            if (count == nb_of_entity)
            {
                line_parsed = parse_string(line, ':');
                short score = static_cast<short>(std::stoi(line_parsed[1]));
                _packet->packet.msg[_packet->cursor_msg] = score >> 8;
                _packet->cursor_msg++;

                _packet->packet.msg[_packet->cursor_msg] = score;
                _packet->cursor_msg++;
            }
            else
            {
                line_parsed = parse_string(line, ':');
                id = line_parsed[0];
                tmp_vect = parse_string(line_parsed[1], '/');
                nbr = tmp_vect[0];
                health = tmp_vect[1];
                for (auto it : map_of_type)
                {
                    if (it.first.compare(id) == 0)
                    {
                        _packet->packet.msg[_packet->cursor_msg] = it.second;
                        _packet->cursor_msg++;

                        _packet->packet.msg[_packet->cursor_msg] = stoi(nbr);
                        _packet->cursor_msg++;
                        
                        _packet->packet.msg[_packet->cursor_msg] = stoi(health);
                        _packet->cursor_msg++;
                    }
                }
                count++;
            }
        }
    }
}