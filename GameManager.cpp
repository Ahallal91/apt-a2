#include <iostream>
#include "GameManager.h"
#include "Output.h"
#include "Types.h"
#include "Player.h"
#include "Input.h"
#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
#include "GameState.h"
#include <fstream>

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

	delete gameState;
}

GameState* GameManager::getGameState() {
	return gameState;
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
			// TODO will need to clean up
			std::vector<std::string> commands = {};
			bool validMove = true;
			do {
				validMove = true;

				commands = this->input->getGameplayInput();

				if (commands.empty()) {
					validMove = false;
				}

				if (validMove) {
					validMove = this->gameLogic->takeTiles
					(this->factories, currentPlayer, stoi(commands.at(1)), commands.at(2).at(0), stoi(commands.at(3)));

					// START JOHN CODE
					std::string com = commands.at(0) + " " + commands.at(1) + " " + commands.at(2) + " " + commands.at(3);
					this->turns.push_back(com);

					std::cout << "OUT!" << std::endl;

					exportGame(nullptr, "export.txt");

					// END JOHN CODE
				}

				if (!validMove) {
					this->output->invalidInput();
					this->output->requestInput();
				}
			} while (!validMove);
			// end of asking for valid input

			// DEBUGGING
			std::cout << "Player board is now:" << std::endl;
			this->output->outputBoard(currentPlayer);

			currentPlayer = currentPlayer == this->player1 ? this->player2 : this->player1;
		}
		std::cout << "ROUND OVERR" << std::endl;
	}
}

GameState* GameManager::importGame(std::string fileName) {
	bool validGame = true;
	GameState* gameState = nullptr;
	
	std::ifstream file(fileName);
	
	// check file exists
	if(file.good()) {

		// prepare the bag
		TileBag bag;

		// Import the Tile Bag
		std::string tileString;
		std::getline(file, tileString);

		std::vector<char> tiles;
		if(tileString.length() == 100) {
			for(char tile : tileString) {
				if(tile == RED || tile == YELLOW || tile == DARK_BLUE || tile == LIGHT_BLUE || tile == BLACK) {
					bag.addToBag(tile);
				} else {
					validGame = false;
				}
			}
		} else {
			validGame = false;
		}

		// Import Players
		std::string name1;
		std::string name2;

		std::getline(file, name1);
		std::getline(file, name2);

		Player player1(name1);
		Player player2(name2);

		// Import Moves
		//TODO

		// Create a new GameState
		
		//testing
		/*
		std::cout << "TILES: " << std::endl;
		for(int i = 0; i < bag.size(); i++) {
			std::cout << bag.at(i) << std::endl;
		}
		std::cout << "NAMES: " << std::endl;
		std::cout << name1 << std::endl;
		std::cout << name2 << std::endl;
		*/

		
		if(validGame) {
			gameState = new GameState();
		}

		return gameState;
	}
}

// TODO might be outputting the updated tile bag when it should stick to initial order!!!
// TODO currently doing from GameManager rather than GameState (for testing)
void GameManager::exportGame(GameState* gameState, std::string fileName) {
	std::ofstream file(fileName.c_str());

	// Output Tile Bag
	for(int i = 0; i < tileBag->size(); i++) {
		file << tileBag->at(i);
	}
	file << std::endl;

	// Output Player Names
	file << player1->getPlayerName() << std::endl;
	file << player2->getPlayerName() << std::endl;

	for(std::string turn : turns) {
		file << turn << std::endl;
	}
}

Player* GameManager::getPlayer1() {
	return this->player1;
}

Player* GameManager::getPlayer2() {
	return this->player2;
}