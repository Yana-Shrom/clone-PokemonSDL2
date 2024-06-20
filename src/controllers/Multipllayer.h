#ifndef _MULTIPLAYER_H
#define _MULTIPLAYER_H

#include <thread>
#include <Battle.h>
#include <Client.h>
#include <Server.h>
#include <functional>

/**
 * @file Multiplayer.h
 * @brief Fichier d'en-tête déclarant la classe Multiplayer pour gérer le jeu en mode multijoueur.
 */

/**
 * @class Multiplayer
 * @brief Classe responsable de la gestion du jeu en mode multijoueur.
 *
 * Cette classe encapsule la logique nécessaire pour gérer le jeu en mode multijoueur, y compris le fonctionnement du serveur et du client, ainsi que la gestion des batailles.
 */
class Multiplayer
{
private:
    Server server; /**< Instance du serveur pour la communication réseau. */
    Client client; /**< Instance du client pour la communication réseau. */
    Battle battle; /**< Instance de la bataille en cours. */
    std::thread server_thread; /**< Thread pour exécuter le serveur. */
    std::thread client_thread; /**< Thread pour exécuter le client. */

public:
    /**
     * @brief Constructeur par défaut de la classe Multiplayer.
     */
    Multiplayer();

    /**
     * @brief Fonction exécutée par les threads pour gérer la communication réseau.
     */
    void threadFunction();
};

/**
 * @brief Fonction membre inline pour gérer la communication réseau.
 *
 * Cette fonction est exécutée par les threads pour gérer la communication réseau entre le serveur et le client.
 */
inline void Multiplayer::threadFunction()
{
    while (true) {
        std::string data = server.receive_data();
        battle.process_action(data);
        server.send_data(battle.getState());
    }
}

#endif
