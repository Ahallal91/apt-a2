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

// TODO this will create a new GameState and ask for player names in here (rather than constructor)
// The current constructor should be moved to this method (apart from GameLogic, Input and Output fields)
void GameManager::newGame() {

}

// TODO this will loop user input and calling importGame() until a valid game is found, then create a GameState from that
// After a valid game file is detected, should call playGame(GameState* gameState) to play the game from the GameState
void GameManager::loadGame() {

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
		this->gameLogic->addToWall(this->player1);
		this->gameLogic->addToWall(this->player2);

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

// TODO need copy constructors before dealing with this to copy the stack GameState to a heap allocated one (if the import is valid)
GameState* GameManager::importGame(std::string fileName) {
	bool validGame = true;
	GameState* gameState = nullptr;

	std::ifstream file(fileName);

	// check file exists
	if (file.good()) {

		// prepare the bag
		TileBag bag;

		// Import the Tile Bag
		std::string tileString;
		std::getline(file, tileString);

		std::vector<char> tiles;
		if (tileString.length() == 100) {
			for (char tile : tileString) {
				if (tile == RED || tile == YELLOW || tile == DARK_BLUE || tile == LIGHT_BLUE || tile == BLACK) {
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


		if (validGame) {
			// need copy constructor
			gameState = new GameState();
		}		
	}
	return gameState;
}

// TODO might be outputting the updated tile bag when it should stick to initial order!!!
// TODO currently doing from GameManager rather than GameState (for testing)
void GameManager::exportGame(GameState* gameState, std::string fileName) {
	std::ofstream file(fileName.c_str());

	// Output Tile Bag
	for (int i = 0; i < tileBag->size(); i++) {
		file << tileBag->at(i);
	}
	file << std::endl;

	// Output Player Names
	file << player1->getPlayerName() << std::endl;
	file << player2->getPlayerName() << std::endl;

	/* COMMENTED OUT UNTIL MOVE TO GAMESTATE
	for(std::string turn : turns) {
		file << turn << std::endl;
	}
	*/
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
		 , tileBag);
	}

	return validMove;
}