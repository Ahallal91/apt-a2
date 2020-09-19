#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "TileBag.h"
#include "Factories.h"
#include "Player.h"

#include <vector>

class GameState {
public:
    GameState();

    // TODO some of these constructor fields can be moved to setters to make it smaller
    GameState(int round, Player* player1, Player* player2, TileBag* tileBag, Factories* factories, Player* currentPlayer);
    ~GameState();

    int getRound();
    void incrementRound();

    std::string getInitialTileBag();

    TileBag* getTileBag();

    Factories* getFactories();

    // TODO could make these methods less redundant and use 1 that takes in player number
    Player* getPlayer1();
    Player* getPlayer2();

    Player* getCurrentPlayer();
    void setCurrentPlayer(Player* player);
    
    // Add a turn (the command inputted by the player) to the history of turns
    void addTurn(std::string turn);

    std::vector<std::string>* getTurns();

private:
    int round;
    std::string initialTileBag;

    TileBag* tileBag;
    Factories* factories;

    Player* player1;
    Player* player2;

    Player* currentPlayer;

    std::vector<std::string>* turns;

};

#endif // GAME_STATE_H