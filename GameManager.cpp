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
	TileBag* tileBag = new TileBag("TileBag.txt");
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
				output->outputTestingGameState(gameState);
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
			// outputs the current state of the game
			output->outputCurrentGameState(gameState->getCurrentPlayer(),
											gameState->getFactories());

			// checks for valid move on input
			validateMove(gameState);

			// outputs successful turn for player
			output->turnSuccess(gameState->getCurrentPlayer());

			// changes current player to opposite player
			gameState->setCurrentPlayer(
				gameState->getCurrentPlayer() == gameState->getPlayer1()
				? gameState->getPlayer2() 
				: gameState->getPlayer1());
		}
		// round has ended

		// sets the player with the first tile to the starting player for next round
		gameState->getPlayer2()->getPlayerBoard()->brokenLineHasFirst()
			? gameState->setCurrentPlayer(gameState->getPlayer2())
			: gameState->setCurrentPlayer(gameState->getPlayer1());

		// calculate player points and move to wall
		gameLogic->addToWall(gameState->getPlayer1());
		gameLogic->addToWall(gameState->getPlayer2());

		// reset board and add back to tile bag
		gameLogic->resetBoard(gameState->getPlayer1(), gameState->getTileBag());
		gameLogic->resetBoard(gameState->getPlayer2(), gameState->getTileBag());

		// outputs the end of round and player points information
		output->outputEndOfRound(gameState);
	}

	// game finished, outputs the final winner of the game.
	output->outputWinner(gameState->getPlayer1(), gameState->getPlayer2());
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

	// an array to represent how many of each valid tile has been read in
	// the goal is to read in 20 of each tile
	int tileCounts[NUM_TILES] = {};
	
	// check that 100 tiles are in the string
	if (tileString.length() == 100) {
		for (char tile : tileString) {

			// check each individual tile is a valid one. if valid, increase the tileCount for the respective tile
			for(int i = 0; i < NUM_TILES; i++) { // FIX MAGIC NUMBER
				if(tile == validTile[i]) {
					tileCounts[i]++;
				}
			}
		}
	} else {
		validGame = false;
	}

	// check that 20 of each tile were read in
	if(validGame) {
		for(int i = 0; i < NUM_TILES; i++) {
			if(tileCounts[i] != 20) {
				validGame = false;
			}
		}
	}

	// if the tile string passed validation check (20 of each tile), then add the tiles to the bag
	if(validGame) {
		for(char tile : tileString) {
			bag->addToBag(tile);
		}
	}

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

				validMove = gameLogic
							->takeTiles(factories, gameState->getCurrentPlayer(),
							stoi(commands[1]),
							commands[2].at(0),
							stoi(commands[3]), bag);

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
			if(!eof) gameState->setCurrentPlayer(gameState->getCurrentPlayer()
					== gameState->getPlayer1() 
					? gameState->getPlayer2() 
					: gameState->getPlayer1());

			//LOG("changing player " + gameState->getCurrentPlayer()->getPlayerName());
		}
			
		if(validGame && gameLogic->roundOver(factories)) {
			// round has ended

			// calculate player points and move to wall
			gameLogic->addToWall(gameState->getPlayer1());
			gameLogic->addToWall(gameState->getPlayer2());

			// reset board and add back to tile bag
			gameLogic->resetBoard(gameState->getPlayer1(), gameState->getTileBag());
			gameLogic->resetBoard(gameState->getPlayer2(), gameState->getTileBag());

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
		output->requestInput();
		commands = input->getGameplayInput(std::cin);

		if (!commands.empty()) {
			if (commands[0] == "turn") {
				moveSuccess = gameLogic->takeTiles(gameState->getFactories(),
							gameState->getCurrentPlayer(),
							stoi(commands[1]),
							commands[2].at(0),
							stoi(commands[3]),
							gameState->getTileBag());

				// if succesfull move, add it to the game state turn history
				if(moveSuccess) {
					logTurn(commands, gameState);
				}
				
			} else if (commands[0] == "save") {
				exportGame(gameState, commands.at(1));
				output->saveSuccess(commands.at(1));
			}
		}

		// display invalid input if they entered nothing or they entered invalid turn
		// (lazy operator avoids exception)
		if (commands.empty() || (commands[0] == "turn" && !moveSuccess)) {
			output->invalidInput();
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