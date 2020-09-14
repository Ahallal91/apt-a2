#include "Output.h"
#include <iostream>

#include "Player.h"
#include "Types.h"
#include "Factories.h"

Output::Output() {}

Output::~Output() {}


void Output::outputRound(int roundNum) {
	std::cout << "== START ROUND " << roundNum << " ==" << std::endl;
}

void Output::saveSuccess(std::string fileName) {
	std::cout << "Save filed successfully generated as: " << fileName << ".txt" << std::endl;
}

void Output::outputTurn(Player* player) {
	std::cout << "TURN FOR PLAYER: " << player->getPlayerName() << std::endl;
}

void Output::turnSuccess() {
	std::cout << "Turn successful" << std::endl;
}

void Output::requestInput() {
	std::cout << "> ";
}

void Output::outputScore(Player* player) {
	std::cout << "Score for " << player->getPlayerName() << ": " << player->getPoints() << std::endl;
}

void Output::outputWinner(Player* player1, Player* player2) {
	this->outputScore(player1);
	this->outputScore(player2);
	if (player1->getPoints() == player2->getPoints()) {
		std::cout << "Tie!" << std::endl;
	} else {
		Player* winner = player1->getPoints() > player2->getPoints() ? player1 : player2;
		std::cout << winner->getPlayerName() << " wins!" << std::endl;
	}
}

// output the current factory
void Output::outputFactory(Factories* factory) {

	std::cout << "Factories:" << std::endl;

	// output the center factory
	std::cout << "0: ";
	for (char tile : *factory->getCenterFactory()) {
		std::cout << tile << " ";
	}

	// output the factories
	for (int i = 0; i < NUM_FACTORIES; i++) {
		std::cout << std::endl << (i + 1) << ": ";
		char* tiles = factory->getFactory(i);
		for (int j = 0; j < FACTORY_SIZE; j++) {
			if (tiles[j] != '\0') {
				std::cout << tiles[j] << " ";
			}
		}
	}
	std::cout << std::endl << std::endl;
}



// TODO could maybe tell the user what the valid commands are, 
// but for now, just say invalid
void Output::invalidInput() {
	std::cout << "Invalid input. Please enter a valid move" << std::endl;
}

// outputs the players board
void Output::outputBoard(Player* player) {
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

