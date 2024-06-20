#include "GameMaster.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

GameMaster::GameMaster(const Game& game_): game(game_)
{
}

void GameMaster::displayMap(const Map& map, const Player& player, const Pokemon& pokemon)
{
    clear(); // Efface l'écran
    for (int x = 0; x < map.getGrille()[0].size() + 2; ++x) {
        printw("# "); // Caractère représentant les limites horizontales de la map
    }
    printw("\n");

    for (int y = 0; y < map.getGrille().size(); ++y) {
        printw("# "); // Caractère représentant les limites verticales de la map
        for (int x = 0; x < map.getGrille()[y].size(); ++x) {
            char symbol = map.getGrille()[y][x];
            if (player.getPosition().x == x && player.getPosition().y == y)
                symbol = 'P'; // Joueur représenté par 'P'
            else if (pokemon.pos.x == x && pokemon.pos.y == y)
                symbol = 'R'; // Pokemon représenté par 'R'
            printw("%c ", symbol); // Affiche le symbole avec un espace
        }
        printw("#\n"); // Nouvelle ligne à chaque fin de ligne de la carte
    }
    for (int x = 0; x < map.getGrille()[0].size() + 2; ++x) {
        printw("# "); // Caractère représentant les limites horizontales de la map
    }
    printw("\n");
    refresh(); // Rafraîchit l'écran
}

void GameMaster::logMessage(const std::string& message)
{
    timeout(1000);
    mvprintw(LINES - 1, 0, message.c_str()); // Affiche le message en bas à gauche
    refresh(); // Rafraîchit l'écran

}

Game* GameMaster::getGame()
{
    return &game;
}

void GameMaster::start()
{
    initscr(); // Initialise l'écran pour ncurses
    keypad(stdscr, TRUE); // Active les touches spéciales
    noecho(); // Désactive l'affichage des caractères saisis
    
    timeout(1000);
    displayMap(game.getMap(), game.getPlayer(), game.getPokemon());
    while (true) {
        int ch = getch(); // Attend une entrée utilisateur
        if (ch == KEY_UP && game.getPlayer().getPosition().y > 0 && game.getMap().getGrille()[game.getPlayer().getPosition().y - 1][game.getPlayer().getPosition().x] != 'r') {
            game.getPlayer().getPosition().y--;
        } else if (ch == KEY_DOWN && game.getPlayer().getPosition().y < game.getMap()->getGrille().size() - 1 && game.getMap()->getGrille()[game.getPlayer().getPosition().y + 1][game.getPlayer().getPosition().x] != 'r') {
            game.getPlayer().getPosition().y++;
        } else if (ch == KEY_LEFT && game.getPlayer().getPosition().x > 0 && game.getMap()->getGrille()[game.getPlayer().getPosition().y][game.getPlayer().getPosition().x - 1] != 'r') {
            game.getPlayer().getPosition().x--;
        } else if (ch == KEY_RIGHT && game.getPlayer().getPosition().x < game.getMap()->getGrille()[0].size() - 1 && game.getMap()->getGrille()[game.getPlayer().getPosition().y][game.getPlayer().getPosition().x + 1] != 'r') {
            game.getPlayer().getPosition().x++;
        }


        int randomMove = rand() % 4; // 0: haut, 1: bas, 2: gauche, 3: droite

        if (randomMove == 0 && game.getPokemon().pos.y > 0 && game.getMap()->getGrille()[game.getPokemon().pos.y - 1][game.getPokemon().pos.x] != 'r') {
            game.getPokemon().pos.y--;
            logMessage("Le Pokemon Bulbasaur s'est déplacé vers le haut à la position (" + std::to_string(game.getPokemon().pos.x) + ", " + std::to_string(game.getPokemon().pos.y) + ")");
       
        } else if (randomMove == 1 && game.getPokemon().pos.y < game.getMap()->getGrille().size() - 1 && game.getMap()->getGrille()[game.getPokemon().pos.y + 1][game.getPokemon().pos.x] != 'r') {
            game.getPokemon().pos.y++;
            logMessage("Le Pokemon Bulbasaur s'est déplacé vers le bas à la position (" + std::to_string(game.getPokemon().pos.x) + ", " + std::to_string(game.getPokemon().pos.y) + ")");
         
        } else if (randomMove == 2 && game.getPokemon().pos.x > 0 && game.getMap()->getGrille()[game.getPokemon().pos.y][game.getPokemon().pos.x - 1] != 'r') {
            game.getPokemon().pos.x--;
            logMessage("Le Pokemon Bulbasaur s'est déplacé vers la gauche à la position (" + std::to_string(game.getPokemon().pos.x) + ", " + std::to_string(game.getPokemon().pos.y) + ")");
        
        } else if (randomMove == 3 && game.getPokemon().pos.x < game.getMap()->getGrille()[0].size() - 1 && game.getMap()->getGrille()[game.getPokemon().pos.y][game.getPokemon().pos.x + 1] != 'r') {
            game.getPokemon().pos.x++;
            logMessage("Le Pokemon Bulbasaur s'est déplacé vers la droite à la position (" + std::to_string(game.getPokemon().pos.x) + ", " + std::to_string(game.getPokemon().pos.y) + ")");
          
        }
        displayMap(game.getMap(), game.getPlayer(), game.getPokemon());
        if (game.getPlayer().getPosition().x == game.getPokemon().pos.x && game.getPlayer().getPosition().y == game.getPokemon().pos.y) {
            logMessage("Vous avez attrapé le Pokemon !");
            
            break;
        }
    }

    endwin(); // Termine ncurses
}


/*
void GameMaster::placeItems(ItemType type)
{
    string n="";
    int random_nb= rand()%3+1;
    Item item;
    int x = rand() % game.getMap().getLargeur();
    int y = rand() % game.getMap().getHauteur();
    if(random_nb == 1){
        item={"Arbre"}
    }
}
*/