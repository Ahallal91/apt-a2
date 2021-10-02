#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "PlayerBoard.h"

// Player Config
#define DEFAULT_NAME     	"Player"
#define INITIAL_POINTS   	0

class Player {
public:
	Player();
	Player(Player& other);
	Player(Player&& other);
	Player(std::string name);
	// used for advanced modes.
	Player(std::string name, bool advancedMode, bool greyBoard);
	virtual ~Player();

	// Returns the Player's name
	std::string getPlayerName();
	
	// Set the Player's current points
	void setPoints(int points);
	
	// Returns the Player's current points
	int getPoints();

	// Returns the Player's playing board
	virtual PlayerBoard* getPlayerBoard();

private:

	// The name of the Player
	std::string name;

	// The Player's points
	int points;
	
	// The Player's playing board object
	PlayerBoard* playerBoard;
};

#endif