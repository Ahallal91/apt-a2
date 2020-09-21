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
#include "FileHandler.h"

#define LOG(x) std::cout << x << std::endl

// TODO overload this constructor to take in a file; that is a save file.
GameManager::GameManager() {
	this->gameLogic = new GameLogic();
	this->input = new Input();
	this->output = new Output();
	this->fileHandler = new FileHandler();
}

GameManager::~GameManager() {
	delete this->gameLogic;
	delete this->input;
	delete this->output;
	delete this->fileHandler;
}

void GameManager::newGame() {
	TileBag* tileBag = new TileBag();
	Factories* factories = new Factories();

	// TODO might want to change the enterPlayerName and do looping here instead (Input class should be strictly for input - no game logic!)
	Player* player1 = input->enterPlayerName(1);
	Player* player2 = input->enterPlayerName(2);

	// Create a default GameState
	GameState* gameState = new GameState(1, player1, player2, tileBag, factories, player1);
	playGame(gameState);

	delete gameState;
}

// TODO this will loop user input and calling importGame() until a valid game is found, then create a GameState from that
// After a valid game file is detected, should call playGame(GameState* gameState) to play the game from the GameState
void GameManager::loadGame(std::string testFile) {
	GameState* gameState = nullptr;
	bool testMode = !testFile.empty();

	// If not in testing mode, ask a user to import a game
	if (!testMode) {
		while (gameState == nullptr && !std::cin.eof()) {
			std::string fileName;

			std::cout << "Enter the filename from which to load a game" << std::endl;
			output->requestInput();
			std::getline(std::cin, fileName);

			if(fileHandler->fileExists(fileName)) {
				gameState = importGame(fileName);

				if (gameState == nullptr && !std::cin.eof()) {
					std::cout << "Load failed - This is not a valid azul game!" << std::endl << std::endl;
				}
			} else {
				std::cout << "Load failed - Could not find the file specified" << std::endl << std::endl;
			}
		}

		// If gameState is not null (AKA a valid game), resume the game
		std::cout << "Azul game successfully loaded" << std::endl << std::endl;
		playGame(gameState);

		// If launched in testing mode
	} else {
		if(fileHandler->fileExists(testFile)) {
			gameState = importGame(testFile);

			if (gameState != nullptr) {
				output->outputRound(gameState);
				output->outputFactory(gameState->getFactories());
				output->outputScore(gameState->getPlayer1());
				output->outputBoard(gameState->getPlayer1());

				output->outputScore(gameState->getPlayer2());
				output->outputBoard(gameState->getPlayer2());
			} else {
				std::cout << "Testing mode failed - This is not a valid azul game!" << std::endl;
			}
		} else {
			std::cout << "Testing mode failed - Could not find the file specified" << std::endl;
		}

	}

	delete gameState;
}

// remember to end the loop if player enter ends of line character

void GameManager::playGame(GameState* gameState) {

	for (; gameState->getRound() <= NUM_ROUNDS; gameState->incrementRound()) {
		// start of round
		// ONLY CHECK THIS AT NEW ROUND (dont do if loading a game mid round)
		if(gameLogic->roundOver(gameState->getFactories())) {
			LOG("[DEBUG] THE ROUND IS OVER!!!");
			this->gameLogic->initFactoryTiles(gameState->getFactories(), gameState->getTileBag());
			this->output->outputRound(gameState);
		}

		while (!this->gameLogic->roundOver(gameState->getFactories())) {
			// this could all be in one method in output, then these methods could become private
			this->output->outputTurn(gameState->getCurrentPlayer());
			this->output->outputFactory(gameState->getFactories());
			this->output->outputBoard(gameState->getCurrentPlayer());

			this->validateMove(gameState);

			this->output->turnSuccess();
			this->output->outputBoard(gameState->getCurrentPlayer());

			gameState->setCurrentPlayer(gameState->getCurrentPlayer() == gameState->getPlayer1() ? gameState->getPlayer2() : gameState->getPlayer1());
		}
		// round has ended
		
		// calculate player points and move to wall
		this->gameLogic->addToWall(gameState->getPlayer1());
		this->gameLogic->addToWall(gameState->getPlayer2());

		// reset board and add back to tile bag
		this->gameLogic->resetBoard(gameState->getPlayer1(), gameState->getTileBag());
		this->gameLogic->resetBoard(gameState->getPlayer2(), gameState->getTileBag());

		// OUTPUT round over here
		// output score
		this->output->outputScore(gameState->getPlayer1());
		this->output->outputScore(gameState->getPlayer2());
		std::cout << std::endl;
		this->output->outputBoard(gameState->getPlayer1());
		this->output->outputBoard(gameState->getPlayer2());
	}

	// game finished
	this->output->outputWinner(gameState->getPlayer1(), gameState->getPlayer2());
}

// TODO fix the tilbag (right now is just using default one)
GameState* GameManager::importGame(std::string fileName) {
	bool validGame = true;
	GameState* gameState = nullptr;

	std::ifstream file(fileName);

	// prepare the bag and factories
	// using default bag
	TileBag* bag = new TileBag();
	Factories* factories = new Factories();

	// Import the Tile Bag
	std::string tileString;
	std::getline(file, tileString);

	/*
	if (tileString.length() == 100) {
		for (char tile : tileString) {
			if (tile == RED || tile == YELLOW || tile == DARK_BLUE || tile == LIGHT_BLUE || tile == BLACK) { // MAKE isValidTile(char tile) method!!!
				bag.addToBag(tile);
			} else {
				validGame = false;
			}
		}
	} else {
		validGame = false;
	}
	*/

	// Import Players
	std::string name1;
	std::string name2;

	std::getline(file, name1);
	std::getline(file, name2);

	Player* player1 = new Player(name1);
	Player* player2 = new Player(name2);
		
	//GS
	gameState = new GameState(1, player1, player2, bag, factories, player1);

	// play the game from a file
	bool eof = false;
	while (!eof && validGame) {
		// start of round
		this->gameLogic->initFactoryTiles(factories, bag);

		while (!this->gameLogic->roundOver(factories) && validGame && !eof) {
			// DO STUFF HERE
			std::vector<std::string> commands = input->getGameplayInput(file);
				
			// check that command is valid (lazy operator)
			bool validMove = false;
			if(!commands.empty() && commands[0] == TURN_COMMAND) {
				validMove = gameLogic->takeTiles(factories, gameState->getCurrentPlayer(), stoi(commands[1]), commands[2].at(0), stoi(commands[3]), bag);
				if(!validMove) {
					validGame = false;
				} else {
					logTurn(commands, gameState);
				}
			} else if(!commands.empty() && commands[0] == EOF_COMMAND) {
				eof = true;
			} else {
				validGame = false;
			}

			// might do a check
			if(!eof) gameState->setCurrentPlayer(gameState->getCurrentPlayer() == gameState->getPlayer1() ? gameState->getPlayer2() : gameState->getPlayer1());
			//LOG("changing player " + gameState->getCurrentPlayer()->getPlayerName());
		}
			
		if(validGame && gameLogic->roundOver(factories)) {
			// round has ended

			// calculate player points and move to wall
			this->gameLogic->addToWall(gameState->getPlayer1());
			this->gameLogic->addToWall(gameState->getPlayer2());

			// reset board and add back to tile bag
			this->gameLogic->resetBoard(gameState->getPlayer1(), gameState->getTileBag());
			this->gameLogic->resetBoard(gameState->getPlayer2(), gameState->getTileBag());

			if(gameState->getRound() < NUM_ROUNDS) {
				gameState->incrementRound();
			} else {
				std::cout << "[Debug] GAME FINISHED!" << std::endl;
				eof = true;
			}
		}
	}

	if (!validGame) {
		// no memory leaks as when deleting a gameState, the previously made pointers will get cleaned up
		delete gameState;
		gameState = nullptr;
	}

	return gameState;
}

void GameManager::exportGame(GameState* gameState, std::string fileName) {
	std::ofstream file(fileName + FILE_NAME_EXTENSION);

	// Output Tile Bag
	file << gameState->getInitialTileBag() << std::endl;

	// Output Player Names
	file << gameState->getPlayer1()->getPlayerName() << std::endl;
	file << gameState->getPlayer2()->getPlayerName() << std::endl;

	for (unsigned int i = 0; i < gameState->getTurns()->size(); i++) {
		file << gameState->getTurns()->at(i) << std::endl;
	}
}

void GameManager::validateMove(GameState* gameState) {
	std::vector<std::string> commands = {};
	bool moveSuccess = false;

	while (!moveSuccess) {
		this->output->requestInput();
		commands = this->input->getGameplayInput(std::cin);
		std::cout << commands.size() << std::endl;

		if (!commands.empty()) {
			if (commands[0] == "turn") {
				moveSuccess = this->gameLogic->takeTiles(gameState->getFactories(), gameState->getCurrentPlayer(), stoi(commands[1]), commands[2].at(0), stoi(commands[3]), gameState->getTileBag());

				// if succesfull move, add it to the game state turn history
				if(moveSuccess) {
					logTurn(commands, gameState);
				}
				
			} else if (commands[0] == "save") {
				this->exportGame(gameState, commands.at(1));
				this->output->saveSuccess(commands.at(1));
			}
		}

		// display invalid input if they entered nothing or they entered invalid turn
		// (lazy operator avoids exception)
		if (commands.empty() || (commands[0] == "turn" && !moveSuccess)) {
			this->output->invalidInput();
		}
	}
}

void GameManager::logTurn(std::vector<std::string> commands, GameState* gameState) {
	// add the valid turn to turn history
	std::string turn;
	for (unsigned int i = 0; i < commands.size(); i++) {
		turn.append(commands[i]);
		if (i != commands.size() - 1) {
			turn.append(" ");
		}
	}
	
	gameState->addTurn(turn);
}