#ifndef INPUT_H
#define INPUT_H

class Player;
// used for getting and validating input.
class Input {
public:
	Input();
	~Input();

	Player* enterPlayerName(int playerNum);
	void getTurn();


private:

};


#endif //INPUT_H