#include <iostream>
#include "GameManager.h"
#include "Output.h"
#include "Types.h"
#include "Player.h"
#include "Input.h"
#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"

// TODO overload this constructor to take in a file; that is a save file.
GameManager::GameManager():
	currentRound(1) {
	this->gameLogic = new GameLogic();
	this->input = new Input();
	this->output = new Output();
	this->factories = new Factories();
	this->tileBag = new TileBag();
	this->player1 = this->input->enterPlayerName(1);
	this->player2 = this->input->enterPlayerName(2);
}


GameManager::~GameManager() {
	delete this->player1;
	delete this->player2;
	delete this->gameLogic;
	delete this->input;
	delete this->output;
	delete this->factories;
	delete this->tileBag;
}

// main game loop
// remember to end the loop if player enter ends of line character
void GameManager::playGame() {
	Player* currentPlayer = this->player1;

	for (; currentRound <= NUM_ROUNDS; currentRound++) {
		// start of round
		this->gameLogic->initFactoryTiles(this->factories, this->tileBag);
		this->output->outputRound(currentRound);

		while (!this->gameLogic->roundOver(this->factories)) {
			// this could all be in one method in output, then these methods could become private
			this->output->outputTurn(currentPlayer);
			this->output->outputFactory(this->factories);
			this->output->outputBoard(currentPlayer);
			this->output->requestInput();


			while (!this->validateMove(currentPlayer)) {
				output->invalidInput();
				output->requestInput();
			}

			this->output->turnSuccess();
			this->output->outputBoard(currentPlayer);

			currentPlayer = currentPlayer == this->player1 ? this->player2 : this->player1;
		}
		// round has ended

		// calculate player points and move to wall
		this->gameLogic->calculatePoints(this->player1);
		this->gameLogic->calculatePoints(this->player2);

		// reset board and add back to tile bag
		this->gameLogic->resetBoard(this->player1, this->tileBag);
		this->gameLogic->resetBoard(this->player2, this->tileBag);

		// output score
		this->output->outputScore(this->player1);
		this->output->outputScore(this->player2);
	}

	// game finished
	 this->output->outputWinner(this->player1, this->player2);
}

bool GameManager::validateMove(Player* currentPlayer) {
	std::vector<std::string> commands = {};
	bool validMove = true;

	commands = this->input->getGameplayInput();

	if (commands.empty()) {
		validMove = false;
	}

	if (validMove) {
		validMove = this->gameLogic->takeTiles
		(factories, currentPlayer, stoi(commands.at(1)), commands.at(2).at(0), stoi(commands.at(3))
		,tileBag);
	}

	return validMove;
}