#include "Battle.h"
#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

Battle::Battle(const Player& player_, const Pokemon& enemyPokemon_) : player(player_), enemyPokemon(enemyPokemon_)
{
}


// Logique pour traiter les actions du joueur dans le combat Pokemon
void Battle::process_action(std::string action) {
    state=action;
}

void Battle::attack()
{
    enemyPokemon.damage(20);
}

void Battle::defense()
{
    enemyPokemon.damage(10);
}


void Battle::loopBattle()
{
    bool playerTurn = true;
    while(enemyPokemon.getLife()<=0 || player.getInventory().getPokemon(0).getLife() <=0){
        if(playerTurn){
            if(getState()=="Attack"){
                attack();
            }
            else{
                state="Il ne se passe rien !";
            }
            
            playerTurn=false;
        }
        else{
            if(getState()== "Defense"){
                defense();
            }
            else{
                player.getInventory().getPokemon(0).damage(20);
            }
            playerTurn=true;
        }

        if(getState()=="Catch" && enemyPokemon.getLife()<=40){
            player.getInventory().addPokemon(enemyPokemon);
            break;
        }
        
    }
}


std::string Battle::getState() {
    return state; 
}


