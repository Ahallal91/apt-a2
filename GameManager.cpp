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

bool GameManager::newGame() {
	TileBag* tileBag = new TileBag(DEFAULT_TILE_BAG_FILE);
	Factories* factories = new Factories();

	// TODO might want to change the enterPlayerName and do looping here instead (Input class should be strictly for input - no game logic!)
	Player* player1 = input->enterPlayerName(1);
	Player* player2 = input->enterPlayerName(2);

	// Create a default GameState
	GameState* gameState = new GameState(1, player1, player2, tileBag, factories, player1);
	bool playing = playGame(gameState);

	delete gameState;
	return !playing;
}

bool GameManager::loadGame(std::string testFile) {
	GameState* gameState = nullptr;
	bool testMode = !testFile.empty();
	bool playing = false;

	// If not in testing mode, ask a user to import a game
	if (!testMode) {
		while (gameState == nullptr && !std::cin.eof()) {
			std::string fileName;

			std::cout << "Enter the filename from which to load a game" << std::endl;
			output->requestInput();
			std::getline(std::cin, fileName);

			if (fileHandler->fileExists(fileName)) {
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
		playing = playGame(gameState);

		// If launched in testing mode
	} else {
		if (fileHandler->fileExists(testFile)) {
			gameState = importGame(testFile);

			if (gameState != nullptr) {
				this->output->outputTestingGameState(gameState);
			} else {
				std::cout << "Testing mode failed - This is not a valid azul game!" << std::endl;
			}
		} else {
			std::cout << "Testing mode failed - Could not find the file specified" << std::endl;
		}

	}

	delete gameState;
	return !playing;
}

// remember to end the loop if player enter ends of line character
bool GameManager::playGame(GameState* gameState) {
	bool playing = true;

	while (gameState->getRound() <= NUM_ROUNDS && playing) {
		// start of round
		// ONLY CHECK THIS AT NEW ROUND (dont do if loading a game mid round)
		if (gameLogic->roundOver(gameState->getFactories())) {
			LOG("[DEBUG] THE ROUND IS OVER!!!");
			this->gameLogic->initFactoryTiles(gameState->getFactories(), gameState->getTileBag());
			this->output->outputRound(gameState);
		}

		output->outputCurrentGameState(gameState->getCurrentPlayer(),
									   gameState->getFactories());

		playing = this->validateMove(gameState);

		if (playing) {
			// output turn info
			if (!this->gameLogic->roundOver(gameState->getFactories())) {
				this->output->turnSuccess(gameState->getCurrentPlayer());

				gameState->setCurrentPlayer(gameState->getCurrentPlayer() == gameState->getPlayer1() ? gameState->getPlayer2() : gameState->getPlayer1());
			}
			// else output roundOver info
			else if (this->gameLogic->roundOver(gameState->getFactories())) {
				// the round is over

				// sets the player with the first tile to the starting player for next round
				gameState->getPlayer2()->getPlayerBoard()->brokenLineHasFirst()
				? gameState->setCurrentPlayer(gameState->getPlayer2())
				: gameState->setCurrentPlayer(gameState->getPlayer1());
				
				// calculate player points and move to wall
				this->gameLogic->addToWall(gameState->getPlayer1());
				this->gameLogic->addToWall(gameState->getPlayer2());

				// reset board and add back to tile bag
				this->gameLogic->resetBoard(gameState->getPlayer1(), gameState->getTileBag());
				this->gameLogic->resetBoard(gameState->getPlayer2(), gameState->getTileBag());

				// output score
				this->output->outputEndOfRound(gameState);

				// increment the round
				gameState->incrementRound();
			}
		}
	}

	// output the winner
	if (playing) {
		this->output->outputWinner(gameState->getPlayer1(), gameState->getPlayer2());
	}

	// returns true or false whether the player quit the game
	return playing;
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
			for (int i = 0; i < NUM_TILES; i++) { // FIX MAGIC NUMBER
				if (tile == validTile[i]) {
					tileCounts[i]++;
				}
			}
		}
	} else {
		validGame = false;
	}

	// check that 20 of each tile were read in
	if (validGame) {
		for (int i = 0; i < NUM_TILES; i++) {
			if (tileCounts[i] != 20) {
				validGame = false;
			}
		}
	}

	// if the tile string passed validation check (20 of each tile), then add the tiles to the bag
	if (validGame) {
		for (char tile : tileString) {
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
			if (!commands.empty() && commands[0] == TURN_COMMAND) {

				validMove = gameLogic
					->takeTiles(factories, gameState->getCurrentPlayer(),
								stoi(commands[1]),
								commands[2].at(0),
								stoi(commands[3]), bag);

				if (!validMove) {
					validGame = false;
				} else {
					logTurn(commands, gameState);
				}
			} else if (!commands.empty() && commands[0] == EOF_COMMAND) {
				eof = true;
			} else {
				validGame = false;
			}

			// switch players
			if (!eof) gameState->setCurrentPlayer(gameState->getCurrentPlayer()
												  == gameState->getPlayer1()
												  ? gameState->getPlayer2()
												  : gameState->getPlayer1());
		}

		if (validGame && gameLogic->roundOver(factories)) {
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

			if (gameState->getRound() < NUM_ROUNDS) {
				gameState->incrementRound();
			} else {
				std::cout << "[Debug] GAME FINISHED!" << std::endl;
				eof = true;
			}
		}
	}

	// if the game is not valid, return a nullptr
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

bool GameManager::validateMove(GameState* gameState) {
	std::vector<std::string> commands = {};
	bool moveSuccess = false;

	while (!moveSuccess) {
		this->output->requestInput();
		commands = this->input->getGameplayInput(std::cin);

		if (!commands.empty()) {
			if (commands[0] == TURN_COMMAND) {
				moveSuccess = this->gameLogic->takeTiles(gameState->getFactories(), gameState->getCurrentPlayer(), stoi(commands[1]), commands[2].at(0), stoi(commands[3]), gameState->getTileBag());

				// if succesfull move, add it to the game state turn history
				if (moveSuccess) {
					logTurn(commands, gameState);
				}

			} else if (commands[0] == SAVE_COMMAND) {
				this->exportGame(gameState, commands.at(1));
				this->output->saveSuccess(commands.at(1));
			} else if (commands[0] == EOF_COMMAND) {
				moveSuccess = true;
			}
		}

		// display invalid input if they entered nothing or they entered invalid turn
		// (lazy operator avoids exception)
		if (commands.empty() || (commands[0] == TURN_COMMAND && !moveSuccess)) {
			this->output->invalidInput();
		}
	}

	// return false if the user quit so the game ends
	return commands[0] != EOF_COMMAND;
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