#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>

class Player;
class Factories;



// used for outputting the game to the console; does not modify any state
class Output {
public:
	Output();
	~Output();

	// TODO too many methods
	void outputRound(int roundNum);
	void outputFactory(Factories* factory);
	void outputBoard(Player* player);
	void outputTurn(Player* player);
	void requestInput();
	void invalidInput();
	void turnSuccess();
	void outputScore(Player* player);
	void outputWinner(Player* player1, Player* player2);
	void saveSuccess(std::string name);
};

#endif // OUTPUT_H