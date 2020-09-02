#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class PlayerBoard;

class Player {
public:
	Player();
	Player(std::string name);
	~Player();

	// Returns the Player's name
	std::string getPlayerName();

	// Returns the Player's current points
	int getPoints();

	// Returns the Player's playing board
	PlayerBoard* getPlayerBoard();

private:

	// The name of the Player
	std::string name;

	// The Player's points
	int points;

	// The Player's playing board object
	PlayerBoard* playerBoard;
};

#endif