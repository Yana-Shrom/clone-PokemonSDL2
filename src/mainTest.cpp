#include "models/Item.h"
#include "models/Game.h"
#include "models/Map.h"
#include "models/Player.h"

int main() 
{
    Map map(20,20);
    Pokemon bulbasaur(PokeName::Bulbasaur, 5, true, {PokeType::Plant, PokeType::Poison});
    Player player(Vector2D(0,0));
    Game game(map, player, bulbasaur);

    game.testRegression();
}