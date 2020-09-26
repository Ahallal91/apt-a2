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
	~Output();

	// TODO too many methods
	void outputRound(GameState* gameState);

	// outputs the current game factories, the players and their board
	void outputCurrentGameState(Player* currentPlayer, Factories* factories);

	// output both players current boards and scores
	void outputEndOfRound(GameState* gameState);

	// outputs the current player turn and their board
	void turnSuccess(Player* currentPlayer);
	
	// outputs the winner at the end of the game
	void outputWinner(Player* player1, Player* player2);

	// output for testing mode.
	void outputTestingGameState(GameState* gameState);
	
	void requestInput();
	void invalidInput();

	void saveSuccess(std::string name);

private:
	void outputTurn(Player* player);
	void outputFactory(Factories* factory);
	void outputBoard(Player* player);
	void outputScore(Player* player);
};

#endif // OUTPUT_H