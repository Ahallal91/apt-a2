#include <iostream>

#include "../Player.h"
#include "../Types.h"

void testBoardOutput();

void outputBoard(Player* player);

int main() {
    testBoardOutput();
    
    return EXIT_SUCCESS;
}

void testBoardOutput() {
    Player* player = new Player("Mark");

    outputBoard(player);

    // wall output
    player->getPlayerBoard()->setWallTile(1, 1);
    player->getPlayerBoard()->setWallTile(2, 1);
    player->getPlayerBoard()->setWallTile(3, 1);
    player->getPlayerBoard()->setWallTile(3, 2);
    player->getPlayerBoard()->setWallTile(3, 3);

    // pattern lines output
    player->getPlayerBoard()->getPatternLine(1)->addTile(RED);
    player->getPlayerBoard()->getPatternLine(3)->addTile(DARK_BLUE);
    player->getPlayerBoard()->getPatternLine(3)->addTile(DARK_BLUE);

    // broken line output
    player->getPlayerBoard()->addBrokenTile(FIRST);
    player->getPlayerBoard()->addBrokenTile(RED);
    player->getPlayerBoard()->addBrokenTile(LIGHT_BLUE);

    outputBoard(player);

    // Modify the board
    player->getPlayerBoard()->removeWallTile(1, 1);
    player->getPlayerBoard()->removeWallTile(2, 1);
    player->getPlayerBoard()->setWallTile(3, 4);
    player->getPlayerBoard()->setWallTile(4, 4);

    player->getPlayerBoard()->getPatternLine(1)->clear();
    player->getPlayerBoard()->getPatternLine(3)->clear();
    player->getPlayerBoard()->getPatternLine(0)->addTile(LIGHT_BLUE);
    player->getPlayerBoard()->getPatternLine(2)->addTile(YELLOW);

    player->getPlayerBoard()->addBrokenTile(YELLOW);
    player->getPlayerBoard()->addBrokenTile(BLACK);

    outputBoard(player);

    delete player;
}

// sample method to print the board, using the same code as output class
void outputBoard(Player* player) {
	std::cout << "Mosaic for " << player->getPlayerName() << ":" << std::endl;

	// Output pattern lines and wall
	for (int y = 0; y < WALL_DIM; y++) {

		// Pattern line
		std::cout << (y + 1) << ":";
		// Blank spaces
		for (int i = 0; i < WALL_DIM - player->getPlayerBoard()->getPatternLine(y)->getSize(); i++) {
			std::cout << " " << " ";
		}
		// Tiles
		for (int i = player->getPlayerBoard()->getPatternLine(y)->getSize() - 1; i >= 0; i--) {
			if (i > player->getPlayerBoard()->getPatternLine(y)->getCurrentSize() - 1) {
				std::cout << " " << EMPTY;
			} else {
				std::cout << " " << player->getPlayerBoard()->getPatternLine(y)->getTileType();
			}
		}

		// Seperator
		std::cout << " " << "||";

		// Wall row
		for (int x = 0; x < WALL_DIM; x++) {
			std::cout << " " << player->getPlayerBoard()->getWallTile(x, y);
		}
		std::cout << std::endl;
	}

	// Output broken tiles
	std::cout << "6: broken |";
	for (int i = 0; i < player->getPlayerBoard()->getBrokenSize(); i++) {
		std::cout << " " << player->getPlayerBoard()->getBrokenTile(i);
	}
	std::cout << std::endl;

	// Print a blank line for seperation purposes
	std::cout << std::endl;
}