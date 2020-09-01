#include "Player.h"

Player::Player() : 
    Player("Player") 
{

}

Player::Player(const std::string& name) :
    name(name)
{
    this->playerBoard = new PlayerBoard();
}

Player::~Player() {
    delete this->playerBoard;
}

std::string Player::getPlayerName() {
    return this->name;
}

int Player::getPoints() {
    return this->points;
}

PlayerBoard* Player::getPlayerBoard() {
    return this->playerBoard;
}