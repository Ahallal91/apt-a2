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
	for (; currentRound <= NUM_ROUNDS; currentRound++) {
		this->gameLogic->initFactoryTiles(this->factories, this->tileBag);

		this->output->outputRound(currentRound);
		this->output->outputFactory(this->factories);
		this->output->requestInput();

		// keep asking until valid input 
		std::vector<std::string> commands = {};
		commands = this->input->getGameplayInput();

		while (commands.at(0) != "quit" || commands.empty()) {
			this->output->invalidInput();
			this->output->requestInput();
		}

	}
}

Player* GameManager::getPlayer1() {
	return this->player1;
}

Player* GameManager::getPlayer2() {
	return this->player2;
}