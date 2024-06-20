#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <string>
#include <cstring>
#include <thread>
#include "SDLSprite.h"

/**
 * @file Client.h
 * @brief Fichier d'en-tête déclarant la classe Client pour gérer la communication client-serveur.
 */

/**
 * @class Client
 * @brief Classe responsable de la gestion de la communication client-serveur.
 *
 * Cette classe encapsule la logique nécessaire pour créer un client et communiquer avec un serveur distant.
 */
class Client {
private:
    TCPsocket client_socket; /**< Socket du client pour la communication. */

public:
    /**
     * @brief Constructeur de la classe Client.
     *
     * Initialise le client en se connectant au serveur distant.
     */
    Client() {
        SDLNet_Init();
        IPaddress ip;
        SDLNet_ResolveHost(&ip, "127.0.0.1", 5555);
        client_socket = SDLNet_TCP_Open(&ip);
        if (!client_socket) {
            std::cerr << "Erreur lors de la création du socket client\n";
            exit(EXIT_FAILURE);
        }
        std::cout << "Connecté au serveur\n";
    }

    /**
     * @brief Envoie des données au serveur.
     * @param data Les données à envoyer sous forme de chaîne de caractères.
     */
    void send_data(std::string data) {
        SDLNet_TCP_Send(client_socket, data.c_str(), data.size() + 1);
    }

    /**
     * @brief Reçoit des données du serveur.
     * @return Les données reçues sous forme de chaîne de caractères.
     */
    std::string receive_data() {
        char buffer[1024];
        SDLNet_TCP_Recv(client_socket, buffer, sizeof(buffer));
        return std::string(buffer);
    }

    /**
     * @brief Destructeur de la classe Client.
     *
     * Ferme le socket du client et libère les ressources utilisées.
     */
    ~Client() {
        SDLNet_TCP_Close(client_socket);
        SDLNet_Quit();
    }
};

#endif
