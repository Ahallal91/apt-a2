#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "PlayerBoard.h"

class Player {
public:
	Player();
	Player(std::string name);
	~Player();

	// Returns the Player's name
	std::string getPlayerName();
	
	// Set the Player's current points
	void setPoints(int points);
	
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