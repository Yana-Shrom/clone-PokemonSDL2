
#ifndef _BATTLE_H
#define _BATTLE_H
#include <iostream>
#include "Player.h"
#include "Pokemon.h"
/**
* @file Battle.h
* @brief Fichier d'en-tête déclarant la classe Battle pour gérer les combats.
*/
/**
* @class Battle
* @brief Classe responsable de la gestion des combats.
*
* Cette classe encapsule la logique nécessaire pour gérer les combats entre le joueur et un Pokémon ennemi.
*/
class Battle
{
private:
Player player; /**< Joueur participant au combat. */
Pokemon enemyPokemon; /**< Pokémon ennemi. */
std::string state; /**< État actuel du combat. */
public :
/**
* @brief Constructeur par défaut de la classe Battle.
*/
Battle();
/**
* @brief Constructeur de la classe Battle avec initialisation des participants.
* @param player_ Objet Player représentant le joueur.
* @param enemyPokemon_ Objet Pokemon représentant le Pokémon ennemi.
*/
Battle(const Player &player_, const Pokemon &enemyPokemon_);
/**
* @brief Traite une action effectuée pendant le combat.
* @param action Action à traiter.
*/
void process_action(std::string action);
/**
* @brief Effectue une attaque pendant le combat.
*/
void attack();
/**
* @brief Effectue une défense pendant le combat.
*/
void defense();
/**
* @brief Boucle principale de gestion du combat.
*/
void loopBattle();
/**
* @brief Récupère l'état actuel du combat.
* @return L'état actuel du combat.
*/
std::string getState();
/**
* @brief Vérifie si un Pokémon est éliminé.
* @param i Indice du Pokémon à vérifier.
* @return True si le Pokémon est éliminé, sinon False.
*/
bool checkPokemonDie(int i);
};
#endif
