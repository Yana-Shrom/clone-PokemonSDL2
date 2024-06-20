#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Vector2D.h"
#include "Map.h"
#include "Inventory.h"

/**
 * @file Player.h
 * @brief Fichier d'en-tête déclarant la classe Player pour représenter le joueur.
 */

/**
 * @class Player
 * @brief Classe représentant le joueur.
 *
 * Cette classe encapsule la logique nécessaire pour représenter le joueur dans le jeu, y compris son nom, son inventaire et sa position.
 */
class Player {
private:
    std::string name; /**< Nom du joueur. */
    Inventory inventory; /**< Inventaire du joueur. */
    Vector2D position; /**< Position du joueur sur la carte. */

public:
    /**
     * @brief Constructeur par défaut de la classe Player.
     */
    Player();

    /**
     * @brief Constructeur de la classe Player avec une position initiale.
     * @param position Position initiale du joueur.
     */
    Player(Vector2D position);

    /**
     * @brief Destructeur de la classe Player.
     */
    ~Player();

    /**
     * @brief Obtient le nom du joueur.
     * @return Le nom du joueur.
     */
    std::string getPlayerName() const;

    /**
     * @brief Obtient une référence vers l'inventaire du joueur.
     * @return L'inventaire du joueur.
     */
    Inventory& getInventory();

    // /**
    //  * @brief Obtient une référence constante vers l'inventaire du joueur.
    //  * @return L'inventaire du joueur.
    //  */
    // const Inventory &getInventory() const;

    /**
     * @brief Définit le nom du joueur.
     * @param name Le nom à définir pour le joueur.
     */
    void setPlayerName(std::string name);

    /**
     * @brief Déplace le joueur vers la gauche sur la carte.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void left(const Map &map);

    /**
     * @brief Déplace le joueur vers la droite sur la carte.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void right(const Map &map);

    /**
     * @brief Déplace le joueur vers le haut sur la carte.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void up(const Map &map);

    /**
     * @brief Déplace le joueur vers le bas sur la carte.
     * @param map La carte sur laquelle le joueur se déplace.
     */
    void down(const Map &map);

    /**
     * @brief Obtient la position actuelle du joueur sur la carte.
     * @return La position actuelle du joueur.
     */
    Vector2D getPosition() const;
};

/**
 * @brief Obtient la position actuelle du joueur sur la carte.
 * @return La position actuelle du joueur.
 */
inline Vector2D Player::getPosition() const
{
    return position;
}

#endif
