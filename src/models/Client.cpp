#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    IPaddress ip;
    SDLNet_ResolveHost(&ip, "127.0.0.1", 1234);

    TCPsocket client = SDLNet_TCP_Open(&ip);

    if (!client) {
        std::cout << "Échec de la connexion au serveur." << std::endl;
        return -1;
    }

    std::cout << "Connecté au serveur!" << std::endl;


    SDLNet_TCP_Close(client);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}