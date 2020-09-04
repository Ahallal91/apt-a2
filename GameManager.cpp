#include <iostream>
#include "GameManager.h"
#include "Output.h"
#include "Types.h"
#include "Player.h"
#include "Input.h"
#include "GameLogic.h"

GameManager::GameManager():
	currentRound(1) {
	this->player1 = this->enterPlayerName(1);
	this->player2 = this->enterPlayerName(2);
	this->gameLogic = new GameLogic();
	this->input = new Input();
	this->output = new Output();
}


GameManager::~GameManager() {
	delete this->player1;
	delete this->player2;
	delete this->gameLogic;
	delete this->input;
	delete this->output;
}

// main game loop
void GameManager::playGame() {
	for (; currentRound <= NUM_ROUNDS; currentRound++) {
		this->output->outputRound(currentRound);


	}
}


Player* GameManager::getPlayer1() {
	return this->player1;
}

Player* GameManager::getPlayer2() {
	return this->player2;
}

// could have loop, but for now we'll assume the user will enter a single name
Player* GameManager::enterPlayerName(int playerNum) {
	std::string name = "";
	std::cout << "Enter a name for player " << playerNum << std::endl;
	std::cin >> name;

	return new Player(name);
}