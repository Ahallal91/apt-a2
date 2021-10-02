#include <iostream>
#include <fstream>
#include "GameManager.h"
#include "Output.h"
#include "Types.h"
#include "Player.h"
#include "Input.h"
#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
#include "GameState.h"
#include "AI.h"
#include "FileHandler.h"

#define DEFAULT_NUM_TILES	5
#define ADV_NUM_TILES		6

GameManager::GameManager() {
	this->gameLogic = new GameLogic();
	this->input = new Input();
	this->output = new Output();
	this->fileHandler = new FileHandler();
	this->advancedMode = false;
	this->greyBoard = false;
	this->aiMode = false;
	this->ai = nullptr;
}

GameManager::GameManager(bool advancedMode, bool greyBoard) {
	this->advancedMode = advancedMode;
	this->greyBoard = greyBoard;
	this->gameLogic = new GameLogic(advancedMode, greyBoard);
	this->output = new Output(advancedMode);
	this->input = new Input(advancedMode, greyBoard);		
	this->fileHandler = new FileHandler();
	this->aiMode = false;
	this->ai = nullptr;
}

GameManager::GameManager(bool advancedMode, bool greyBoard, bool aiMode) {
	this->advancedMode = advancedMode;
	this->greyBoard = greyBoard;
	this->gameLogic = new GameLogic(advancedMode, greyBoard);
	this->output = new Output(advancedMode);
	this->input = new Input(advancedMode, greyBoard);		
	this->fileHandler = new FileHandler();
	this->aiMode = aiMode;
	if(aiMode) {
		this->ai = new AI();
		this->ai2 = new AI();
	} else {
		ai = nullptr;
	}
}

GameManager::~GameManager() {
	delete this->gameLogic;
	delete this->input;
	delete this->output;
	delete this->fileHandler;
	delete this->ai;
}

bool GameManager::newGame() {
	bool playing = false;
	
	std::string name1;
	std::string name2;
	if(aiMode) {
		name2 = "Computer AI";
	}
	while(name1.empty()) {
		name1 = input->enterPlayerName(1);
	}
	while(name2.empty()) {
		name2 = input->enterPlayerName(2);
	}

	// check that eof was not entered (indicated by empty player name)
	if(!name2.empty()) {
		TileBag* tileBag = nullptr;
		Factories* factories = new Factories();
		Player* player1 = nullptr;
		Player* player2 = nullptr;

		if (advancedMode) {
			tileBag = new TileBag(ADV6TILE_TILE_BAG_FILE);
			player1 = new Player(name1, advancedMode, greyBoard);
			player2 = new Player(name2, advancedMode, greyBoard);
		} else if (greyBoard) {
			tileBag = new TileBag(DEFAULT_TILE_BAG_FILE);
			player1 = new Player(name1, false, greyBoard);
			player2 = new Player(name2, false, greyBoard);
		} else if (aiMode) {
			tileBag = new TileBag(DEFAULT_TILE_BAG_FILE);
			player1 = new Player(name1);
			player2 = new Player(name2);
			ai->setPlayer(player2);
			ai2->setPlayer(player1);
		} else {
			tileBag = new TileBag(DEFAULT_TILE_BAG_FILE);
			player1 = new Player(name1);
			player2 = new Player(name2);
		}


		// Create a default GameState
		GameState* gameState = new GameState(STARTING_ROUND, player1, player2, 
											tileBag, factories, player1);
		
		// Play the game
		playing = playGame(gameState, std::cin);

		// Delete the gameState after playing has stopped
		delete gameState;
	}

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

			if(!std::cin.eof()) {
				if (fileHandler->fileExists(fileName)) {
					gameState = importGame(fileName);

					if (gameState == nullptr) {
						std::cout << "Load failed - This is not a valid azul game!" << std::endl << std::endl;
					}
				} else {
					std::cout << "Load failed - Could not find the file specified" << std::endl << std::endl;
				}
			}
		}

		// If gameState is not null (AKA a valid game) and EOF was not entered, resume the game
		if(!std::cin.eof()) {
			std::cout << "Azul game successfully loaded" << std::endl << std::endl;
			playing = playGame(gameState, std::cin);
		}

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

	// Delete the gameState after playing has stopped or EOF was entered
	delete gameState;
	
	return !playing;
}

bool GameManager::playGame(GameState* gameState, std::istream& file) {
	bool playing = true;

	while (gameState->getRound() <= NUM_ROUNDS && !gameState->isFinished() && playing) {
		
		// start of round
		if (gameLogic->roundOver(gameState->getFactories())) {
			this->gameLogic->initFactoryTiles(gameState->getFactories(), gameState->getTileBag());
			this->output->outputRound(gameState);
		}

		output->outputCurrentGameState(gameState->getCurrentPlayer(),
									   gameState->getFactories());

		if (aiMode && gameState->getCurrentPlayer() == gameState->getPlayer2()) {

			ai->calculateTurn(gameState->getFactories());
			playing = this->validateMove(gameState, file, ai->makeMove());
		} else if (aiMode && gameState->getCurrentPlayer() == gameState->getPlayer1()) {
			ai2->calculateTurn(gameState->getFactories());
			playing = this->validateMove(gameState, file, ai2->makeMove());
		}

		if (playing) {
			// output turn info
			if (!this->gameLogic->roundOver(gameState->getFactories())) {
				this->output->turnSuccess(gameState->getCurrentPlayer());

				gameState->setCurrentPlayer(gameState->getCurrentPlayer() 
											== gameState->getPlayer1() 
											? gameState->getPlayer2() 
											: gameState->getPlayer1());
			}
			// else output roundOver info
			else if (this->gameLogic->roundOver(gameState->getFactories())) {
				// the round is over
				gameRoundEnd(gameState, gameLogic, file);				
				// output score
				this->output->outputEndOfRound(gameState);

				// increment the round
				gameState->incrementRound();
			}
		}
	}

	// output the winner
	if (playing) {
		gameState->setFinished(true);
		output->outputRound(gameState);
		this->output->outputWinner(gameState->getPlayer1(), gameState->getPlayer2());
	}

	// returns true or false whether the player quit the game
	return playing;
}

GameState* GameManager::importGame(std::string fileName) {
	bool validGame = true;
	GameState* gameState = nullptr;

	std::ifstream file(fileName);

	// prepare the bag and factories
	TileBag* bag = new TileBag();
	Factories* factories = new Factories();

	// Import the Tile Bag
	std::string tileString;
	std::getline(file, tileString);

	// validates the tile bag
	validGame = validateTileBag(tileString, validGame, bag);



	// Import Players
	std::string name1;
	std::string name2;

	std::getline(file, name1);
	std::getline(file, name2);
	// check that names are not empty
	if(name1.empty() || name2.empty()) {
		validGame = false;
	}

	Player* player1;
	Player* player2;

	if (advancedMode) {
		player1 = new Player(name1, advancedMode, greyBoard);
		player2 = new Player(name2, advancedMode, greyBoard);
	} else if (greyBoard) {
		player1 = new Player(name1, false, greyBoard);
		player2 = new Player(name2, false, greyBoard);
	} else if (ai) {
		player1 = new Player(name1);
		player2 = new Player(name2);
		ai->setPlayer(player2);
	} else {
		player1 = new Player(name1);
		player2 = new Player(name2);
	}

	// // Create GameState
	gameState = new GameState(STARTING_ROUND, player1, player2, bag, factories, player1);
	
	// playTheGame
	playGame(gameState, file);

	file.close();
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

	file.close();
}

bool GameManager::validateMove(GameState* gameState, std::istream& file, std::string aiMode) {
	std::vector<std::string> commands = {};
	bool moveSuccess = false;
	
	while (!moveSuccess) {
		this->output->requestInput();
		if(!aiMode.empty()) {
			commands = this->input->getGameplayInput(file, aiMode);
		} else if (!file.eof()) {
			commands = this->input->getGameplayInput(file, "");
		} else {
			commands = this->input->getGameplayInput(std::cin, "");
		}
		
		if (!commands.empty()) {
			if (commands[0] == TURN_COMMAND) {
				moveSuccess = gameLogic->takeTiles(gameState->getFactories(),
							 	gameState->getCurrentPlayer(),
								stoi(commands[1]),
								commands[2].at(0),
								stoi(commands[3]),
								gameState->getTileBag());

				// if succesfull move, add it to the game state turn history
				if (moveSuccess) {
					logTurn(commands, gameState);
				}

			} else if (commands[0] == GREYBOARD_COMMAND) {
				
				moveSuccess = gameLogic->playerMoveTileToWall(
								gameState->getCurrentPlayer(),
								stoi(commands[1]),
								stoi(commands[2]));
				
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
		if (commands.empty() || (commands[0] == TURN_COMMAND && !moveSuccess) ||
		(commands[0] == GREYBOARD_COMMAND && !moveSuccess)) {
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

void GameManager::gameRoundEnd(GameState* gameState, GameLogic* gameLogic, std::istream& file) {
	if (greyBoard) {	
		greyBoardMoveTiles(gameState, gameLogic, file);
		gameState->setCurrentPlayer(gameState->getCurrentPlayer() 
							== gameState->getPlayer1() 
							? gameState->getPlayer2() 
							: gameState->getPlayer1());
		greyBoardMoveTiles(gameState, gameLogic, file);
	} else {
		// calculate player points and move to wall
		gameLogic->addToWall(gameState->getPlayer1());
		gameLogic->addToWall(gameState->getPlayer2());
	}
	// sets the player with the first tile to the starting player for next round
	gameState->getPlayer2()->getPlayerBoard()->brokenLineHasFirst()
	? gameState->setCurrentPlayer(gameState->getPlayer2())
	: gameState->setCurrentPlayer(gameState->getPlayer1());

	// reset board and add back to tile bag
	gameLogic->resetBoard(gameState->getPlayer1(), gameState->getTileBag());
	gameLogic->resetBoard(gameState->getPlayer2(), gameState->getTileBag());
}

bool GameManager::validateTileBag(std::string& tileString, bool& validGame, TileBag* bag) {
	// an array to represent how many of each valid tile has been read in
	// the goal is to read in 20 of each tile
	int numTiles = 0;
	int tileBagSize = 0;
	if (advancedMode) {
		numTiles = ADV_NUM_TILES;
		tileBagSize = ADV_TILE_BAG_SIZE;
	} else {
		numTiles = DEFAULT_NUM_TILES;
		tileBagSize = TILE_BAG_SIZE;
	}
	int tileCounts[numTiles] = {};
	
	// total number of tiles that should be in the bag, goal is 100
	int totalTileCount = 0;
	
	// check that 100 tiles are in the string if default mode or
	// check that 120 tiles are in a string if adv 6 tile mode.
	for (char& tile : tileString) {

		// check each individual tile is a valid one. if valid, 
		// increase the tileCount for the respective tile
		for (int i = 0; i < numTiles; i++) {
			// if game is run in advanced mode 6 tile, checks orange tile array
			if(advancedMode) {
				if (tile == advValidTile[i]) {
					tileCounts[i]++;
				}
			} else {
				if (tile == validTile[i]) {
					tileCounts[i]++;
				}
			}
		}
		totalTileCount++;
	}

	if (totalTileCount != tileBagSize) {
		validGame = false;
	}
		
	// check that 20 of each tile were read in
	if (validGame) {
		for (int i = 0; i < numTiles; i++) {
			if (tileCounts[i] != (tileBagSize / numTiles)) {
				validGame = false;
			}
		}
	}

	// if the tile string passed validation check (20 of each tile), then add the tiles to the bag
	if (validGame) {
		for (char& tile : tileString) {
			bag->addToBag(tile);
		}
	}

	return validGame;
}

void GameManager::greyBoardMoveTiles(GameState* gameState, GameLogic* gameLogic, std::istream& file) {
	this->output->outputPromptGreyBoard();
	while (gameLogic->playerPatternLinesFull(gameState->getCurrentPlayer())) {
		this->output->outputGreyBoardMode(gameState->getCurrentPlayer());
		this->validateMove(gameState, file, "");
	}
}