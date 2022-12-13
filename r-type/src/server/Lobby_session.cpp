#include "Lobby_session.hpp"
#include "Server.hpp"
#include "Room.hpp"

Lobby_session::Lobby_session(asio::ip::tcp::socket socket, Server* server): _socket(std::move(socket)), _server(server)
{
    handle();
}

Lobby_session::~Lobby_session()
{
    std::cout << "disconecting tcp client (lobby destructor)" << std::endl;
    _socket.close();
}

void Lobby_session::create_room_cmd()
{

            
    // you first read the message legenth then the message then the port 
    asio::async_read(_socket,
        asio::buffer(&buffer.strlen, sizeof(buffer.strlen)), 
        [this](std::error_code ec, std::size_t length) 
        {
            asio::async_read(_socket,
                asio::buffer(&buffer.msg, (size_t) buffer.strlen), 
                [this](std::error_code ec, std::size_t length) 
                {
                    asio::async_read(_socket,
                        asio::buffer(&buffer.port, sizeof(buffer.port)), 
                        [this](std::error_code ec, std::size_t length) 
                        {
                            asio::async_read(_socket,
                                asio::buffer(&buffer.addr, sizeof(char) * 16), 
                                [this](std::error_code ec, std::size_t length) 
                                {
                                    std::cout << _socket.local_endpoint().address().to_string() << std::endl;
                                    //std::cout << "cmd:" << (int) buffer.cmd << std::endl;
                                    //std::cout << "msg_length:" << (int) buffer.strlen << std::endl;
                                    //std::cout << "msg:" << buffer.msg << std::endl;
                                    //std::cout << "tcp port client:" << (int) buffer.port << std::endl;
                                    //std::cout << "addr ip :" << buffer.addr << std::endl;

                                    //create a room with the name given by client
                                    _server->add_room(std::string(buffer.msg));
                                    //and add the client to it
                                    Room *room_created = _server->get_room(std::string(buffer.msg));
                                    short cli_port_tcp = buffer.port;
                                    //then we send the udp port of the room to the client
                                    buffer.cmd = SERVER_GIVE_ROOM_PORT;
                                    asio::write(_socket, asio::buffer(&buffer.cmd, sizeof(buffer.cmd)));
                                    buffer.port = room_created->getPort();
                                    asio::write(_socket, asio::buffer(&buffer.port, sizeof(buffer.port)));
                                    room_created->add_client(cli_port_tcp, buffer.addr, std::move(_socket));
                                    handle();
                                }
                            );
                        }
                    );
                }
            );
        }
    );
}

void Lobby_session::join_room_cmd()
{

            
    // you first read the message legenth then the message then the port 

    asio::async_read(_socket,
        asio::buffer(&buffer.strlen, sizeof(buffer.strlen)), 
        [this](std::error_code ec, std::size_t length) 
        {
            asio::async_read(_socket,
                asio::buffer(&buffer.msg, (size_t) buffer.strlen), 
                [this](std::error_code ec, std::size_t length) 
                {
                    asio::async_read(_socket,
                        asio::buffer(&buffer.port, sizeof(buffer.port)), 
                        [this](std::error_code ec, std::size_t length) 
                        {
                            asio::async_read(_socket,
                                asio::buffer(&buffer.addr, sizeof(char) * 16), 
                                [this](std::error_code ec, std::size_t length) 
                                {
                                    // std::cout << "cmd:" << (int) buffer.cmd << std::endl;
                                    // std::cout << "msg_length:" << (int) buffer.strlen << std::endl;
                                    // std::cout << "msg:" << buffer.msg << std::endl;
                                    // std::cout << "tcp port client:" << (int) buffer.port << std::endl;
                                    // std::cout << "addr ip :" << buffer.addr << std::endl;

                                    //add the client to the room he wrote in msg
                                    std::cout << "\"" << buffer.msg << "\"" << std::endl;
                                    Room *room_selected = _server->get_room(std::string(buffer.msg));
                                    if (room_selected == NULL)
                                    {
                                        std::cout << "error: didnt found the room" << std::endl;
                                        buffer.cmd = ROOM_ACCESS_DENIED;
                                        asio::write(_socket, asio::buffer(&buffer.cmd, sizeof(buffer.cmd)));
                                        handle();
                                    } else if (room_selected->state_Room() != 0 || room_selected->clients_nbr_in_room() > 3) {
                                        std::cout << "error: Can't access to the room" << std::endl;
                                        buffer.cmd = ROOM_ACCESS_DENIED;
                                        asio::write(_socket, asio::buffer(&buffer.cmd, sizeof(buffer.cmd)));
                                        handle();
                                    } else
                                    {
                                        std::cout << "State: " << room_selected->state_Room() << std::endl;
                                        short cli_port = buffer.port;
                                        //then we send the udp port of the room to the client
                                        buffer.cmd = SERVER_GIVE_ROOM_PORT;
                                        buffer.port = room_selected->getPort();

                                        asio::write(_socket, asio::buffer(&buffer.cmd, sizeof(buffer.cmd)));
                                        asio::write(_socket, asio::buffer(&buffer.port, sizeof(buffer.port)));
                                        ///!\\//
                                        room_selected->add_client(cli_port, buffer.addr, std::move(_socket));
                                    }
                                }
                            );
                        }
                    );
                }
            );
        }
    );
}

void Lobby_session::disconnect_cmd()
{
    //need to remove player from room of disconect from room

    _server->delete_lobbie(this);
}

void Lobby_session::cmd_join_room() {
    // std::cout << "cmd:" << (int) buffer.cmd << std::endl;
    // std::cout << "msg_length:" << (int) buffer.strlen << std::endl;
    // std::cout << "msg:" << buffer.msg << std::endl;
    // std::cout << "tcp port client:" << (int) buffer.port << std::endl;
    // std::cout << "addr ip :" << buffer.addr << std::endl;

    //add the client to the room he wrote in msg
    std::cout << "\"" << (int)_buffer.cmd << "|" << _buffer.msg << "\"" << _buffer.port << std::endl;
    Room *room_selected = _server->get_room(std::string(_buffer.msg));
    if (room_selected == NULL) {
        std::cout << "error: didnt found the room" << std::endl;
        buffer.cmd = ROOM_ACCESS_DENIED;
        asio::write(_socket, asio::buffer(&buffer, sizeof(buffer)));
        handle();
    } else if (room_selected->state_Room() != 0 || room_selected->clients_nbr_in_room() > 3) {
        std::cout << "error: Can't access to the room" << std::endl;
        buffer.cmd = ROOM_ACCESS_DENIED;
        asio::write(_socket, asio::buffer(&buffer, sizeof(buffer)));
        handle();
    } else {
        std::cout << "State: " << room_selected->state_Room() << std::endl;
        short cli_port = _buffer.port;
        //then we send the udp port of the room to the client
        buffer.cmd = SERVER_GIVE_ROOM_PORT;
        buffer.port = room_selected->getPort();
        asio::write(_socket, asio::buffer(&buffer, sizeof(buffer)));
        //asio::write(_socket, asio::buffer(&buffer.port, sizeof(buffer.port)));
        ///!\\//
        room_selected->add_client(cli_port, _buffer.addr, std::move(_socket));
    }
}

void Lobby_session::cmd_create_room() {
    std::cout << _socket.local_endpoint().address().to_string() << std::endl;
    std::cout << "cmd:" << (int) _buffer.cmd << std::endl;
    std::cout << "msg_length:" << (int) _buffer.strlen << std::endl;
    std::cout << "msg:" << _buffer.msg << std::endl;
    std::cout << "tcp port client:" << (int) _buffer.port << std::endl;
    std::cout << "addr ip :" << _buffer.addr << std::endl;
    //create a room with the name given by client
    _server->add_room(std::string(_buffer.msg));
    //and add the client to it
    Room *room_created = _server->get_room(std::string(_buffer.msg));
    short cli_port_tcp = _buffer.port;
    //then we send the udp port of the room to the client
    _buffer.cmd = SERVER_GIVE_ROOM_PORT;
    _buffer.port = room_created->getPort();
    //asio::write(_socket, asio::buffer(&_buffer.cmd, sizeof(_buffer.cmd)));
//    asio::write(_socket, asio::buffer(&buffer.port, sizeof(buffer.port)));
    asio::write(_socket, asio::buffer(&_buffer, sizeof(_buffer)));
    room_created->add_client(cli_port_tcp, _buffer.addr, std::move(_socket));
}

void Lobby_session::handle() {

    //std::cout << ">> Hello" << std::endl;
    asio::async_read(_socket,
        asio::buffer(&_buffer, sizeof(_buffer)), 
        [this](std::error_code ec, std::size_t length)
    {
        std::cout << "CMDI: " << (int)_buffer.cmd << " " << _buffer.port << std::endl;
        int value = 0;
        if (!ec) {
            switch (_buffer.cmd)
            {
            case DISCONNECT:
                disconnect_cmd();
                break;
            case JOIN_ROOM:
                cmd_join_room();
                break;
            case CREATE_ROOM:
                cmd_create_room();
                handle();
                break;
            default:
                std::cout << "ERROR: command received not found" << std::endl;
                break;
            }
            //std::cout << ">> new handle" << std::endl;
        } else {
//            _server->delete_lobbie(this);
//            return;
        }
        //std::cout << ">> here" << std::endl;
    });
}