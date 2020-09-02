#include "GameManager.h"
#include "Types.h"
#include <iostream>
#include "Player.h"

GameManager::GameManager():
	currentRound(1) {
	this->enterPlayerName(1, this->player1);
	this->enterPlayerName(2, this->player2);
}

// main game loop
void GameManager::playGame() {

}

GameManager::~GameManager() {
	delete this->player1;
	delete this->player2;
}

Player* GameManager::getPlayer1() {
	return this->player1;
}

Player* GameManager::getPlayer2() {
	return this->player2;
}

void GameManager::enterPlayerName(int playerNum, Player*& player) {
	std::string name = "";
	std::cout << "Enter a name for player " << playerNum << std::endl;
	std::cin >> name;

	// while they haven't inputted a name, keep asking
	while (name.size() == 0) {
		std::cout << "Please enter a valid name for player " << playerNum << std::endl;
		std::cin >> name;
	}

	player = new Player(name);
}