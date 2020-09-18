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
	void loadGame(std::string testingFile = "");

	// main game loop
	void playGame(GameState* gameState);

	GameState* importGame(std::string fileName);
	void exportGame(GameState* gameState, std::string fileName);

private:
	GameLogic* gameLogic;
	Input* input;
	Output* output;

	bool validateMove(GameState* gameState, Player* currentPlayer);
};

#endif // GAME_MANAGER_H