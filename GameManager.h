#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>

class Player;
class Output;
class Input;
class GameLogic;
class Factories;
class TileBag;

class GameState;

class GameManager {
public:
	GameManager();
	~GameManager();

	void newGame();
	void loadGame();
	
	// main game loop
	void playGame();

	// TODO the new play method (will be used once the old on is no longer needed when moved to GameState)
	void playGame(GameState* gameState);

	GameState* importGame(std::string fileName);
	void exportGame(GameState* gameState, std::string fileName);

private:
	GameLogic* gameLogic;
	Input* input;
	Output* output;

	void validateMove(GameState* gameState, Player* currentPlayer);

	// old fields (can delete when ready)
	// THESE WILL MOVE TO GAME STATE, HERE FOR NOW THOUGH

	//Player* player1;
	//Player* player2;

	//Factories* factories;
	//TileBag* tileBag;

	//bool validateMove(Player* currentPlayer);

	//int currentRound;
};

#endif // GAME_MANAGER_H