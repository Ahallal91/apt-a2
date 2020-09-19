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

	// Starts a new game by asking for player names and creating a default GameState
	void newGame();

	// Loads a game from a save file by asking for save file input and resuming the game.
	// If called with a file name as its parameter, will instead show the output of the
	// current game state which is used during testing mode
	void loadGame(std::string testFile = "");

	// Main Game Loop
	// Plays a Game from a GameState until finished or exited
	void playGame(GameState* gameState);

	// Imports a game from a save file
	// Returns a GameState of the game if successfull, otherwise returns nullptr
	GameState* importGame(std::string fileName);

	// Exports a game to a save file
	void exportGame(GameState* gameState, std::string fileName);

private:
	GameLogic* gameLogic;
	Input* input;
	Output* output;

	void validateMove(GameState* gameState);
};

#endif // GAME_MANAGER_H