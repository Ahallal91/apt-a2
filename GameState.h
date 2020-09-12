#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "TileBag.h"
#include "Factories.h"
#include "Player.h"

#include <vector>

class GameState {
public:
    GameState();
    GameState(int round, Player* player1, Player* player2, TileBag* tileBag, Factories* factories);
    ~GameState();

    int getRound();

    TileBag* getTileBag();

    Factories* getFactories();

    // TODO could make these methods less redundant and use 1 that takes in player number
    Player* getPlayer1();
    Player* getPlayer2();

    // Add a turn (the command inputted by the player) to the history of turns
    void addTurn(std::string turn);

private:
    int round;

    TileBag* tileBag;
    Factories* factories;

    Player* player1;
    Player* player2;

    std::vector<std::string>* turns;

};

#endif // GAME_STATE_H