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

	Player* getPlayer1();
	Player* getPlayer2();

	// main game loop
	void playGame();

	GameState* importGame(std::string fileName);
	void exportGame(GameState* gameState, std::string fileName);

private:

	// THESE WILL MOVE TO GAME STATE, HERE FOR NOW THOUGH

	Player* player1;
	Player* player2;

	GameLogic* gameLogic;
	Input* input;
	Output* output;
	Factories* factories;
	TileBag* tileBag;

	int currentRound;

	std::vector<std::string> turns;
};

#endif // GAME_MANAGER_H