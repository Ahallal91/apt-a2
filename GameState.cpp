#include "GameState.h"

GameState::GameState() {

}

GameState::GameState(int round, Player* player1, Player* player2, TileBag* tileBag, Factories* factories) :
    round(round),
    tileBag(tileBag),
    factories(factories),
    player1(player1),
    player2(player2)
{
    turns = new std::vector<std::string>;

    // Initialise initial tile bag order
    for(int i = 0; i < tileBag->size(); i++) {
        initialTileBag += tileBag->at(i);
    }
    
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

void GameState::incrementRound() {
    round++;
}

std::string GameState::getInitialTileBag() {
    return initialTileBag;
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

std::vector<std::string>* GameState::getTurns() {
    return turns;
}