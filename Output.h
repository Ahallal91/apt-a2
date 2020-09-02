#ifndef OUTPUT_H
#define OUTPUT_H

class Player;

// used for outputting the game to the console
class Output {
public:
	Output();
	~Output();

	void outputBoard(Player*& player);
};

#endif // OUTPUT_H