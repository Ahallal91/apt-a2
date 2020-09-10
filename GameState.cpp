#include "GameState.h"

GameState::GameState() {

}

GameState::GameState(int round, Player* player1, Player* player2, TileBag* tileBag, Factories* factories) :
    round(round),
    player1(player1),
    player2(player2),
    tileBag(tileBag),
    factories(factories) 
{
    turns = new std::vector<std::string>;
    
}

GameState::~GameState() {
    delete player1;
    delete player2;
    delete tileBag;
    delete factories;

    turns->clear();
    delete turns;
}

int GameState::getRound() {
    return round;
}

TileBag* GameState::getTileBag() {
    return tileBag;
}

Factories* GameState::getFactories() {
    return factories;
}

Player* GameState::getPlayer1() {
    return player1;
}

Player* GameState::getPlayer2() {
    return player2;
}

void GameState::addTurn(std::string turn) {
    turns->push_back(turn);
}