#include "Game.h"
#include <cassert>
#include <iostream>



Game::Game(): map(), player(), pokemon(){}

Game::~Game()
{
}

void Game::actionKeyboard(const char key)
{
    switch (key)
	{
	case 'q':
		player.left(map);
		break;
	case 'd':
		player.right(map);
		break;
	case 'z':
		player.up(map);
		break;
	case 's':
		player.down(map);
		break;
	}

}







/*
//TEST DE REGRESSION
void Game::testRegression()
{
    // Test de récupération de la carte
    Map* retrievedMap = &getMap();
    //faire une fonction de test dans map.
    if (retrievedMap=NULL) {
        int mapWidth = retrievedMap->getLargeur();
        int mapHeight = retrievedMap->getHauteur();
        assert(mapWidth > 0 && mapHeight > 0); // Vérifie que la carte a une taille valide
        std::cout << "Test de récupération de la carte réussi." << std::endl;
    } else {
        std::cerr << "Erreur : impossible de récupérer la carte." << std::endl;
    }

    // Test de récupération du joueur
    Player* retrievedPlayer = &getPlayer();
    if (retrievedPlayer != NULL) {
        std::string playerName = retrievedPlayer->getPlayerName();
        //assert(!playerName.empty()); // Vérifie que le nom du joueur n'est pas vide
        std::cout << "Test de récupération du joueur réussi." << std::endl;
    } else {
        std::cerr << "Erreur : impossible de récupérer le joueur." << std::endl;
    }

    // Test de récupération du Pokémon
    Pokemon* retrievedPokemon = &getPokemon();
    if (retrievedPokemon != nullptr) {
        PokeName pokemonName = retrievedPokemon->getName();
        assert(pokemonName != PokeName::INVALID_POKEMON_NAME); // Vérifie que le nom du Pokémon est connu
        std::cout << "Test de récupération du Pokémon réussi." << std::endl;
    } else {
        std::cerr << "Erreur : impossible de récupérer le Pokémon." << std::endl;
    }
}
*/
