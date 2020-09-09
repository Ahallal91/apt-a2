#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "TileBag.h"
#include "Factories.h"
#include "Player.h"

#include <vector>

class GameState {
public:
    GameState();
    ~GameState();

    void setRound(int round);
    int getRound();

    TileBag* getTileBag();

    Player* getPlayer1();
    Player* getPlayer2();

    void addTurn(std::string turn);

private:
    int round;

    TileBag* tileBag;
    Factories* factories;

    Player* player1;
    Player* player2;

    std::vector<std::string> turns;

};

#endif // GAME_STATE_H