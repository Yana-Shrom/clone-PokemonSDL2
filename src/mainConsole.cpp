#include "controllers/GameMaster.h"
#include "models/Item.h"
#include "models/Game.h"
#include "models/Map.h"
#include "models/Player.h"
ItemType threeOrRock()
{
    ItemType type;
    int r= rand() % 2+1;
    if(r==2){
        type=ItemType::TREE;
    }
    else{
        type=ItemType::ROCK;
    }
    return type;
};
int main() {
    Map map(20,20);
    Pokemon bulbasaur(PokeName::Bulbasaur, 5, true, {PokeType::Plant, PokeType::Poison});
    Player player(Vector2D(0,0));
    Game game(map, player, bulbasaur);
    GameMaster gm(game);
    Item tree(Vector2D(2, 2), ItemType::TREE);
    Item rock(Vector2D(5, 3), ItemType::ROCK);
    gm.getGame()->getMap().placeItem(tree);
    gm.getGame()->getMap().placeItem(rock);

    gm.start();

    return 0;
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