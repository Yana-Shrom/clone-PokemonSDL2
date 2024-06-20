#include "Inventory.h"
#include <algorithm> 

Inventory::Inventory() {}

Inventory::~Inventory() {}

Pokemon Inventory::getPokemon(unsigned int index) const {
    if (index >= 0 && index < listPokemons.size()) {
        return listPokemons[index];
    } else {
        return Pokemon(); // Retourne un Pokemon par défaut en cas d'erreur
    }
}

void Inventory::movePokemon(unsigned int fromIndex, unsigned int toIndex) {
    if (fromIndex >= 0 && fromIndex < listPokemons.size() &&
        toIndex >= 0 && toIndex < listPokemons.size()) {
        std::swap(listPokemons[fromIndex], listPokemons[toIndex]);
    }
}

std::vector<Pokemon> Inventory::getAllPokemons() const {
    return listPokemons;
}
