#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>

#define DEFAULT_TILE_BAG_FILE 	"TileBag.txt"
#define FILE_NAME_EXTENSION 	".azul"

#define NUM_ROUNDS				5

#define STARTING_ROUND			1

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

	/* Starts a new game by asking for player names and creating a default GameState
	 * Returns whether the eof was entered during gameplay
	 */
	bool newGame();

	/* Loads a game from a save file by asking for save file input and resuming the game.
	 * If called with a file name as its parameter, will instead show the output of the
	 * current game state which is used during testing mode
	 * Returns whether eof was entered during gameplay
	 */
	bool loadGame(std::string testFile = "");

	/* Main Game Loop
	 * Plays a Game from a GameState until finished or exited
	 * Returns whether eof was entered during gameplay
	 */
	bool playGame(GameState* gameState);

	/* Imports a game from a save file
	 * Returns a GameState of the game if it is valid, otherwise returns a nullptr
	 */
	GameState* importGame(std::string fileName);

	// Exports a game to a save file
	void exportGame(GameState* gameState, std::string fileName);

private:
	GameLogic* gameLogic;
	Input* input;
	Output* output;
	FileHandler* fileHandler;
	
	// used to end the game if player decides to quit
	bool validateMove(GameState* gameState);

	// Validates the tile bag when importing a game. Returns whether bag is valid
	bool validateTileBag(std::string& tileString, bool& validGame, TileBag* bag);

	// used at end of round, in importGame method and playGame
	void gameRoundEnd(GameState* gameState, GameLogic* gameLogic);

	/* Logs a valid turn vector of arguments to a GameState's turn history
	 * Eg: if input recieved as vector: ["turn", 4, 'R', 2],
	 * will record the turn as: turn 4 R 2
	 */
	void logTurn(std::vector<std::string> commands, GameState* gameState);
};

#endif // GAME_MANAGER_H