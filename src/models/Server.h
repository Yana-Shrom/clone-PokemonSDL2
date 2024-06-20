#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <string>
#include <cstring>
#include <thread>
#include "SDLSprite.h"

/**
 * @file Server.h
 * @brief Fichier d'en-tête déclarant la classe Server pour gérer le serveur de communication.
 */

/**
 * @class Server
 * @brief Classe gérant le serveur de communication.
 *
 * Cette classe encapsule la logique nécessaire pour gérer un serveur de communication utilisant SDL_net pour envoyer et recevoir des données.
 */
class Server
{
private:
    SDLNet_SocketSet socket_set; /**< Ensemble de sockets utilisé pour surveiller les connexions entrantes. */
    TCPsocket server_socket; /**< Socket du serveur. */
    TCPsocket client_socket; /**< Socket du client connecté. */

public:
    /**
     * @brief Constructeur par défaut de la classe Server.
     */
    Server();

    /**
     * @brief Envoie des données au client connecté.
     * @param data Les données à envoyer.
     */
    void send_data(std::string data);

    /**
     * @brief Reçoit des données du client connecté.
     * @return Les données reçues.
     */
    std::string receive_data();

    /**
     * @brief Destructeur de la classe Server.
     */
    ~Server();
};

#endif 