#ifndef OUTPUT_H
#define OUTPUT_H

class Player;
class Factories;

// used for outputting the game to the console; does not modify any state
class Output {
public:
	Output();
	~Output();

	void outputRound(int roundNum);
	void outputFactory(Factories* factory);
	void outputBoard(Player* player);
};

#endif // OUTPUT_H