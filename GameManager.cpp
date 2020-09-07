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
	this->player1 = this->input->enterPlayerName(1);
	this->player2 = this->input->enterPlayerName(2);
	this->gameLogic = new GameLogic();
	this->input = new Input();
	this->output = new Output();
	this->factories = new Factories();
	this->tileBag = new TileBag();
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
	this->gameLogic->initFactoryTiles(this->factories, this->tileBag);
	Player* currentPlayer = this->player1;
	for (; currentRound <= NUM_ROUNDS; currentRound++) {

		this->output->outputRound(currentRound);

		while (!this->gameLogic->roundOver(this->factories)) {
			// this could all be in one method in output, then these methods could become private
			this->output->outputTurn(currentPlayer);
			this->output->outputFactory(this->factories);
			this->output->outputBoard(currentPlayer);
			this->output->requestInput();

			// keep asking until valid input 
			std::vector<std::string> commands = {};
			commands = this->input->getGameplayInput();

			//TODO just testing to see if it works, will obviously clean up
			while (commands.empty()) {
				this->output->invalidInput();
				this->output->requestInput();
				commands = this->input->getGameplayInput();
			}

			this->gameLogic->takeTiles(this->factories, currentPlayer, stoi(commands.at(1)), commands.at(2).at(0), stoi(commands.at(3)));
			currentPlayer = currentPlayer == this->player1 ? this->player2 : this->player1;
		}
		std::cout << "ROUND OVERR" << std::endl;
	}
}

Player* GameManager::getPlayer1() {
	return this->player1;
}

Player* GameManager::getPlayer2() {
	return this->player2;
}