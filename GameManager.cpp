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
GameManager::GameManager() {
	this->gameLogic = new GameLogic();
	this->input = new Input();
	this->output = new Output();
}

GameManager::~GameManager() {
	delete this->gameLogic;
	delete this->input;
	delete this->output;
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

			gameState = importGame(fileName);

			if (gameState == nullptr && !std::cin.eof()) {
				std::cout << "This is not a valid azul game!" << std::endl;
			}
		}

		// If gameState is not null (AKA a valid game), resume the game
		playGame(gameState);

		// If launched in testing mode
	} else {
		gameState = importGame(testFile);

		if (gameState != nullptr) {
			// output the state of the game (testing mode)
			// will need a new method in Output for this
		} else {
			std::cout << "Testing mode failed - This is not a valid azul game!" << std::endl;
		}
	}

	delete gameState;
}

// remember to end the loop if player enter ends of line character
void GameManager::playGame(GameState* gameState) {

	for (; gameState->getRound() <= NUM_ROUNDS; gameState->incrementRound()) {
		// start of round
		this->gameLogic->initFactoryTiles(gameState->getFactories(), gameState->getTileBag());
		this->output->outputRound(gameState->getRound());

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

		// output score
		this->output->outputScore(gameState->getPlayer1());
		this->output->outputScore(gameState->getPlayer2());
	}

	// game finished
	this->output->outputWinner(gameState->getPlayer1(), gameState->getPlayer2());
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

		if (validGame) {
			// need copy constructor
			gameState = new GameState();
		}
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
		commands = this->input->getGameplayInput();
		std::cout << commands.size() << std::endl;

		if (!commands.empty()) {
			if (commands[0] == "turn") {
				moveSuccess = this->gameLogic->takeTiles(gameState->getFactories(), gameState->getCurrentPlayer(), stoi(commands[1]), commands[2].at(0), stoi(commands[3]), gameState->getTileBag());

				// add the valid turn to turn history
				std::string turn;
				for (unsigned int i = 0; i < commands.size(); i++) {
					turn.append(commands[i]);
					if (i != commands.size() - 1) {
						turn.append(" ");
					}
				}
				gameState->addTurn(turn);
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