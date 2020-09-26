#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>

class Player;
class Output;
class Input;
class GameLogic;
class Factories;
class TileBag;
class FileHandler;

class GameState;

class GameManager {
public:
	GameManager();
	~GameManager();

	// Starts a new game by asking for player names and creating a default GameState
	bool newGame();

	// Loads a game from a save file by asking for save file input and resuming the game.
	// If called with a file name as its parameter, will instead show the output of the
	// current game state which is used during testing mode
	void loadGame(std::string testFile = "");

	// Main Game Loop
	// Plays a Game from a GameState until finished or exited
	void playGame(GameState* gameState);

	// Imports a game from a save file
	// Returns a GameState of the game if it is valid, otherwise returns a nullptr
	GameState* importGame(std::string fileName);

	// Exports a game to a save file
	void exportGame(GameState* gameState, std::string fileName);

private:
	GameLogic* gameLogic;
	Input* input;
	Output* output;
	FileHandler* fileHandler;
	// used to end the game if player decides to quit
	bool playing;

	bool validateMove(GameState* gameState);

	// Logs a valid turn vector of arguments to a GameState's turn history
	// Eg: if input recieved as vector: ["turn", 4, 'R', 2],
	// will record the turn as: turn 4 R 2
	void logTurn(std::vector<std::string> commands, GameState* gameState);
};

#endif // GAME_MANAGER_H