#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "TileBag.h"
#include "Factories.h"
#include "Player.h"

#include <vector>

class GameState {
public:
	GameState(int round, Player* player1, Player* player2, TileBag* tileBag, 
				Factories* factories, Player* currentPlayer);
	~GameState();

	int getRound();
	void incrementRound();

	// Returns the initial tile bag for this GameState
	std::string getInitialTileBag();

	// Returns the current TileBag for this GameState
	TileBag* getTileBag();

	// Returns the current Factory states for this GameState
	Factories* getFactories();

	Player* getPlayer1();
	Player* getPlayer2();

	Player* getCurrentPlayer();
	void setCurrentPlayer(Player* player);

	void setFinished(bool gameFinished);
	
	// Returns whether this game is finished (all rounds are over)
	bool isFinished();

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

	bool gameFinished;

	std::vector<std::string>* turns;

};

#endif // GAME_STATE_H