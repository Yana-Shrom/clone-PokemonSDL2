#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Pokemon.h"

/**
 * @file Inventory.h
 * @brief Fichier d'en-tête déclarant la classe Inventory pour gérer l'inventaire de Pokémon.
 */

/**
 * @class Inventory
 * @brief Classe responsable de la gestion de l'inventaire de Pokémon.
 *
 * Cette classe encapsule la logique nécessaire pour gérer l'inventaire de Pokémon, y compris l'ajout, la récupération et le déplacement des Pokémon.
 */
class Inventory {
private:
    std::vector<Pokemon> listPokemons; /**< Liste des Pokémon dans l'inventaire. */

public:
    /**
     * @brief Constructeur par défaut de la classe Inventory.
     */
    Inventory();

    /**
     * @brief Destructeur de la classe Inventory.
     */
    ~Inventory();

    /**
     * @brief Obtient un Pokémon de l'inventaire par son index.
     * @param index L'index du Pokémon à récupérer.
     * @return Le Pokémon correspondant à l'index spécifié.
     */
    Pokemon getPokemon(unsigned int index) const;

    /**
     * @brief Déplace un Pokémon de l'inventaire d'une position à une autre.
     * @param fromIndex L'index de départ du Pokémon à déplacer.
     * @param toIndex La nouvelle position où placer le Pokémon.
     */
    void movePokemon(unsigned int fromIndex,unsigned int toIndex);

    /**
     * @brief Obtient tous les Pokémon de l'inventaire.
     * @return La liste de tous les Pokémon dans l'inventaire.
     */
    std::vector<Pokemon> getAllPokemons() const;

    /**
     * @brief Ajoute un nouveau Pokémon à l'inventaire.
     * @param newPokemon Le nouveau Pokémon à ajouter à l'inventaire.
     */
    void addPokemon(const Pokemon &newPokemon);
};

/**
 * @brief Ajoute un nouveau Pokémon à l'inventaire.
 * @param newPokemon Le nouveau Pokémon à ajouter à l'inventaire.
 */
inline void Inventory::addPokemon(const Pokemon& newPokemon) {
    // Ajoute le nouveau Pokémon à la liste des Pokémon de l'inventaire
    listPokemons.push_back(newPokemon);
}

#endif