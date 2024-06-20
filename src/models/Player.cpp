#include "Player.h"
#include <iostream>

Player::Player(): name("Unknown"), inventory()
{
    position.x=1;
    position.y=10;
}

Player::Player(Vector2D position) : position(position)
{}

Player::~Player() 
{   
}

std::string Player::getPlayerName() const {
    return name;
}


void Player::setPlayerName(std::string name) {
    this->name = name;
}

void Player::left(const Map &map)
{
    if(map.estPositionValide(position.x-1, position.y)){
        std::cout <<"position valide"<<std::endl;
        position.x--;
    }
}

void Player::right(const Map &map)
{
    if(map.estPositionValide(position.x+1, position.y))
        position.x++;
}

void Player::up(const Map &map)
{
    if(map.estPositionValide(position.x, position.y+1))
        position.y++;
}

void Player::down(const Map &map)
{
    if(map.estPositionValide(position.x, position.y-1))
        position.y--;
}

Inventory& Player::getInventory() {
    return inventory;
}
/*
const Inventory& Player::getInventory() const {
    return inventory;
}*/

