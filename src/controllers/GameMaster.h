#ifndef _GAMEMASTER_H
#define _GAMEMASTER_H

#include "../models/Game.h"
#include "../models/Player.h"
#include "../models/Pokemon.h"

/**
 * @file GameMaster.h
 * @brief Fichier d'en-tête déclarant la classe GameMaster pour gérer les interactions du jeu.
 */

/**
 * @class GameMaster
 * @brief Classe responsable de la gestion des interactions du jeu.
 *
 * Cette classe encapsule la logique nécessaire pour gérer les interactions au sein du jeu, notamment l'affichage des cartes, la journalisation des messages et le démarrage du jeu.
 */
class GameMaster
{
private:
    Game game; /**< Instance du jeu gérant la logique de base. */

public:
    /**
     * @brief Constructeur de la classe GameMaster.
     * @param game_ Référence à un objet Game.
     */
    GameMaster(const Game& game_);

    /**
     * @brief Affiche la carte du jeu.
     * @param map Référence à la carte à afficher.
     * @param player Référence à l'objet joueur.
     * @param pokemon Référence à l'objet Pokémon.
     */
    void displayMap(const Map& map, const Player& player, const Pokemon& pokemon);

    /**
     * @brief Journalise un message.
     * @param message Le message à journaliser.
     */
    void logMessage(const std::string& message);

    /**
     * @brief Obtient un pointeur vers l'instance du jeu.
     * @return Un pointeur vers l'instance du jeu.
     */
    Game* getGame();

    /**
     * @brief Lance le jeu.
     */
    void start();
};

#endif
