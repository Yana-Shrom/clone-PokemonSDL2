#include "Server.h"

Server::Server() {
    SDLNet_Init();
    IPaddress ip;
    SDLNet_ResolveHost(&ip, NULL, 5555);
    server_socket = SDLNet_TCP_Open(&ip);
    if (!server_socket) {
        std::cerr << "Error creating server socket\n";
        exit(EXIT_FAILURE);
    }
    socket_set = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(socket_set, server_socket);
    std::cout << "Server started\n";
}

void Server::send_data(std::string data) {
        SDLNet_TCP_Send(client_socket, data.c_str(), data.size() + 1);
    }

    std::string Server::receive_data() {
        char buffer[1024];
        SDLNet_TCP_Recv(client_socket, buffer, sizeof(buffer));
        return std::string(buffer);
    }

    Server::~Server() {
        SDLNet_TCP_Close(client_socket);
        SDLNet_TCP_Close(server_socket);
        SDLNet_FreeSocketSet(socket_set);
        SDLNet_Quit();
    }
