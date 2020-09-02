#include <iostream>
#include "GameManager.h"
#include "Output.h"
#include "Types.h"
#include "Player.h"

// TODO store the output class as an instance variable
GameManager::GameManager():
	currentRound(1) {
	this->player1 = this->enterPlayerName(1);
	this->player2 = this->enterPlayerName(2);
	this->output = new Output();
}

// main game loop
void GameManager::playGame() {
	for (; currentRound <= NUM_ROUNDS; currentRound++) {
		this->output->outputRound(currentRound);


	}
}

GameManager::~GameManager() {
	delete this->player1;
	delete this->player2;
	delete this->output;
}

Player* GameManager::getPlayer1() {
	return this->player1;
}

Player* GameManager::getPlayer2() {
	return this->player2;
}

Player* GameManager::enterPlayerName(int playerNum) {
	std::cin.ignore();
	std::string name = "";
	std::cout << "Enter a name for player " << playerNum << std::endl;
	std::getline(std::cin, name);

	// while they haven't inputted a name, keep asking
	while (name.size() == 0) {
		std::cout << "Please enter a valid name for player " << playerNum << std::endl;
		std::getline(std::cin, name);
	}

	return new Player(name);
}