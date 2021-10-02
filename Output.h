#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>

class Player;
class Factories;
class GameState;

// used for outputting the game to the console; does not modify any state
class Output {
public:
	Output();
	// use this to launch advanced 6-tile mode.
	Output(bool advancedMode);
	
	~Output();

	// outputs the round number info, if game is finished it output end of game.
	void outputRound(GameState* gameState);

	// outputs the current game factories, the players and their board
	void outputCurrentGameState(Player* currentPlayer, Factories* factories);

	// output both players current boards and scores
	void outputEndOfRound(GameState* gameState);

	// output for greyboard mode, moving tiles to wall
	void outputGreyBoardMode(Player* currentPlayer);

	void outputPromptGreyBoard();

	// outputs the current player turn and their board
	void turnSuccess(Player* currentPlayer);
	
	// outputs the winner at the end of the game
	void outputWinner(Player* player1, Player* player2);

	// output for testing mode.
	void outputTestingGameState(GameState* gameState);
	
	// This is the output for request input character '>'
	void requestInput();

	// output for invalid move
	void invalidInput();

	// output for successfully saved file
	void saveSuccess(std::string name);

private:
	// output for of which players turn it is.
	void outputTurn(Player* player);

	// output of current factories of game
	void outputFactory(Factories* factory);

	// output of specific players board information
	void outputBoard(Player* player);

	// output for a players score.
	void outputScore(Player* player);

	bool advancedMode;

	int wallSize;
};

#endif // OUTPUT_H