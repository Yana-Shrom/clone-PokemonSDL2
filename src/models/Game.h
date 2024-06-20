#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Vector2D.h"
#include "Map.h"
#include "Pokemon.h"
#include <vector>

/**
 * @file Game.h
 * @brief Fichier d'en-tête déclarant la classe Game pour représenter le jeu.
 */

using namespace std;

/**
 * @class Game
 * @brief Classe représentant le jeu.
 *
 * Cette classe encapsule la logique nécessaire pour gérer le jeu, y compris la carte, le joueur et les Pokémon.
 */
class Game 
{
private:
    Map map; /**< La carte du jeu. */
    Player player; /**< Le joueur du jeu. */
    vector<Pokemon> pokemon; /**< La liste des Pokémon dans le jeu. */

public:

    /**
     * @brief Constructeur par défaut de la classe Game.
     */
    Game();

    /**
     * @brief Destructeur de la classe Game.
     */
    ~Game();

    /**
     * @brief Obtient une référence constante vers la carte du jeu.
     * @return Une référence constante vers la carte du jeu.
     */
    const Map &getConstMap() const;

    /**
     * @brief Obtient une référence constante vers le joueur du jeu.
     * @return Une référence constante vers le joueur du jeu.
     */
    const Player &getConstPlayer() const;

    /**
     * @brief Obtient une référence constante vers la liste des Pokémon dans le jeu.
     * @return Une référence constante vers la liste des Pokémon dans le jeu.
     */
    const vector<Pokemon> &getPokemons() const;

    /**
     * @brief Obtient une référence vers le joueur du jeu.
     * @return Une référence vers le joueur du jeu.
     */
    Player &getPlayer();

    /**
     * @brief Ajoute un nouveau Pokémon au jeu.
     * @param newPokemon Le nouveau Pokémon à ajouter.
     */
    void addPokemon(const Pokemon &newPokemon);

    /**
     * @brief Obtient un Pokémon spécifique dans la liste des Pokémon du jeu.
     * @param index L'index du Pokémon dans la liste.
     * @return Une référence vers le Pokémon spécifique.
     */
    Pokemon &getPokemon(unsigned int index);

    /**
     * @brief Crée un certain nombre de Pokémon et les ajoute au jeu.
     * @param numPokemons Le nombre de Pokémon à créer et à ajouter.
     */
    void createPokemons(int numPokemons);

    /**
     * @brief Gère les actions du clavier dans le jeu.
     * @param key La touche du clavier appuyée.
     */
    void actionKeyboard(const char key);
};

/**
 * @brief Obtient une référence constante vers la carte du jeu.
 * @return Une référence constante vers la carte du jeu.
 */
inline const Map &Game::getConstMap() const { return map; }

/**
 * @brief Obtient une référence constante vers le joueur du jeu.
 * @return Une référence constante vers le joueur du jeu.
 */
inline const Player &Game::getConstPlayer() const { return player; }

/**
 * @brief Obtient une référence constante vers la liste des Pokémon dans le jeu.
 * @return Une référence constante vers la liste des Pokémon dans le jeu.
 */
inline const vector<Pokemon>& Game::getPokemons() const { return pokemon; }

/**
 * @brief Obtient une référence vers le joueur du jeu.
 * @return Une référence vers le joueur du jeu.
 */
inline Player &Game::getPlayer() 
{
    return player;
}

/**
 * @brief Ajoute un nouveau Pokémon au jeu.
 * @param newPokemon Le nouveau Pokémon à ajouter.
 */
inline void Game::addPokemon(const Pokemon& newPokemon)
{
    pokemon.push_back(newPokemon);
}

/**
 * @brief Obtient un Pokémon spécifique dans la liste des Pokémon du jeu.
 * @param index L'index du Pokémon dans la liste.
 * @return Une référence vers le Pokémon spécifique.
 */
inline Pokemon& Game::getPokemon(unsigned int index) // Implémentation de la nouvelle fonction
{
    if (index >= 0 && index < pokemon.size()) {
        return pokemon[index];
    } else {
        // Gestion de l'index hors limites, vous pouvez jeter une exception ou renvoyer un Pokémon par défaut
        // Par exemple, renvoyer le premier Pokémon du vecteur ou un Pokémon "vide"
        return pokemon[0]; // Retourne le premier Pokémon pour l'instant, mais vous pouvez ajuster selon vos besoins
    }
}

/**
 * @brief Crée un certain nombre de Pokémon et les ajoute au jeu.
 * @param numPokemon Le nombre de Pokémon à créer et à ajouter.
 */
inline void Game::createPokemons(int numPokemon) {
    for (int i = 0; i < numPokemon; ++i) {
        // Crée un nouveau Pokémon et l'ajoute à la liste
        Pokemon newPokemon;
        pokemon.push_back(newPokemon);
    }
}

#endif
