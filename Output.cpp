#include "Output.h"
#include <iostream>

#include "Player.h"
#include "Types.h"
#include "Factories.h"
#include "GameState.h"
#include "SingleFactory.h"

Output::Output() {
	this->advancedMode = false;
	this->wallSize = WALL_DIM;
}

Output::Output(bool advancedMode) {
	this->advancedMode = advancedMode;
	if (advancedMode) {
		this->wallSize = ADV_WALL_DIM;
	} else {
		this->wallSize = WALL_DIM;
	}
}

Output::~Output() {}

void Output::outputCurrentGameState(Player* currentPlayer, 
	Factories* factories) {
	outputTurn(currentPlayer);
	outputFactory(factories);
	outputBoard(currentPlayer);
}

void Output::outputGreyBoardMode(Player* currentPlayer) {
	outputTurn(currentPlayer);
	outputBoard(currentPlayer);
}

void Output::outputEndOfRound(GameState* gamestate) {
	outputScore(gamestate->getPlayer1());
	outputScore(gamestate->getPlayer2());
	std::cout << std::endl;
	outputBoard(gamestate->getPlayer1());
	outputBoard(gamestate->getPlayer2());
}

void Output::outputPromptGreyBoard() {
	std::cout << 
	"Use command 'move' <patternline> <wallcolumn> to move tiles." 
	<< std::endl;
}

void Output::outputTestingGameState(GameState* gameState) {
	outputRound(gameState);
	outputFactory(gameState->getFactories());
	outputScore(gameState->getPlayer1());
	outputBoard(gameState->getPlayer1());

	outputScore(gameState->getPlayer2());
	outputBoard(gameState->getPlayer2());
}

void Output::outputRound(GameState* gameState) {
	if(!gameState->isFinished()) {
		std::cout << "=== Round " << gameState->getRound() << " ===" << std::endl << std::endl;
	} else {
		std::cout << "=== Game is Finished ===" << std::endl << std::endl;
	}
}

void Output::saveSuccess(std::string fileName) {
	std::cout << "Save filed successfully generated as: " << fileName << ".azul" << std::endl;
}

void Output::outputTurn(Player* player) {
	std::cout << "TURN FOR PLAYER: " << player->getPlayerName() << std::endl;
}

void Output::turnSuccess(Player* currentPlayer) {
	std::cout << "Turn successful" << std::endl;
	outputBoard(currentPlayer);
}

void Output::requestInput() {
	std::cout << "> ";
}

void Output::outputScore(Player* player) {
	std::cout << "Score for " << player->getPlayerName() << ": " << player->getPoints() << std::endl;
}

void Output::outputWinner(Player* player1, Player* player2) {
	std::cout << "::Final scores::" << std::endl;
	outputScore(player1);
	outputScore(player2);
	if (player1->getPoints() == player2->getPoints()) {
		std::cout << "Tie!" << std::endl;
	} else {
		Player* winner = player1->getPoints() > player2->getPoints() ? player1 : player2;
		std::cout << std::endl;
		std::cout << winner->getPlayerName() << " wins!" << std::endl << std::endl;
	}
}

// output the current factory
void Output::outputFactory(Factories* factory) {

	std::cout << "Factories:" << std::endl;

	// output the center factory
	std::cout << "0: ";
	for (unsigned int i = 0; i < factory->getCenterFactorySize(); ++i) {
		std::cout << factory->getCenterFactoryTile(i) << " ";
	}

	// output the factories
	for (int i = 0; i < NUM_FACTORIES; i++) {
		std::cout << std::endl << (i + 1) << ": ";
		std::cout << factory->getFactory(i)->toString() << " ";
	}
	std::cout << std::endl << std::endl;
}



// outputs invalid input line
void Output::invalidInput() {
	std::cout << "Invalid input. Please enter a valid move" << std::endl;
}

// outputs the players board
void Output::outputBoard(Player* player) {
	std::cout << "Mosaic for " << player->getPlayerName() << ":" << std::endl;

	// Output pattern lines and wall
	for (int y = 0; y < wallSize; y++) {

		// Pattern line
		std::cout << (y + 1) << ":";
		// Blank spaces
		for (int i = 0; i < wallSize - player->getPlayerBoard()->getPatternLine(y)->getSize(); i++) {
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
		for (int x = 0; x < wallSize; x++) {
			std::cout << " " << player->getPlayerBoard()->getWallTile(x, y);
		}
		std::cout << std::endl;
	}

	// Output broken tiles
	if (advancedMode) {
		std::cout << "7: broken |";
	} else {
		std::cout << "6: broken |";
	}
	for (int i = 0; i < player->getPlayerBoard()->getBrokenSize(); i++) {
		std::cout << " " << player->getPlayerBoard()->getBrokenTile(i);
	}
	std::cout << std::endl;

	// Print a blank line for seperation purposes
	std::cout << std::endl;
}
