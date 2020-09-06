#include "Output.h"
#include <iostream>

#include "Player.h"
#include "Types.h"

Output::Output() {}

Output::~Output() {}


void Output::outputRound(int roundNum) {
	std::cout << "== START ROUND " << roundNum << " ==" << std::endl;
}

// output the current factory
void Output::outputFactory(Factories* factory) {

}

// outputs the players board
void Output::outputBoard(Player* player) {
	std::cout << "Mosaic for " << player->getPlayerName() << ":" << std::endl;
	
	// Output pattern lines and wall
	for(int y = 0; y < WALL_DIM; y++) {
		
		// Pattern line
		std::cout << (y+1) << ": ";
		// Blank spaces
		for(int i = 0; i < WALL_DIM - player->getPlayerBoard()->getPatternLine(y)->getSize(); i++) {
			std::cout << " " << " ";
		}
		// Tiles
		for(int i = player->getPlayerBoard()->getPatternLine(y)->getSize() - 1; i >= 0 ; i--) {
			std::cout << player->getPlayerBoard()->getPatternLine(y)->getTile(i) << " ";
		}

		// Seperator
		std::cout << "||" << " ";
		
		// Wall row
		for(int x = 0; x < WALL_DIM; x++) {
			std::cout << player->getPlayerBoard()->getWallTile(x, y) << " ";
		}
		std::cout << std::endl;
	}

	// Output broken tiles
	std::cout << "broken: ";
    for(int i = 0; i < player->getPlayerBoard()->getBrokenSize(); i++) {
        std::cout << player->getPlayerBoard()->getBrokenTile(i) << " ";
    }
	std::cout << std::endl;

    // Print a blank line for seperation purposes
	std::cout << std::endl;
}

