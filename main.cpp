#include <iostream>

#include "GameManager.h"
#include "Input.h"

#define TESTING_MODE_ARGUMENT			"-t"
#define ADV_6_TILE_MODE_ARGUMENT		"--6tile"
#define ADV_GREY_BOARD_MODE_ARGUMENT	"--gadv"
#define AI_MODE_ARGUMENT				"--ai"

/*
* Welcome to Azul M3 <Commands below>
* To launch 6 tile advanced mode "--6tile"
* To launch greyboard advanced mode "--gadv"
* To launch duel advanced mode type any order "--6tile" "--gadv"
* To launch testing mode with any advanced mode type commands in any order with file name at end
* 		"--6tile" or "--gadv" with "-t" <filename>
* To launch ai mode "--ai"
*/

void runMenu(GameManager* gameManager);
void credits();
void menuText();
void testing(int argc, char** argv,  bool sixTileMode, bool greyBoardMode, GameManager* gameManager);
void gameTypePrint(bool sixTileMode, bool greyBoardMode, bool ai);

int main(int argc, char** argv) {
	GameManager* gameManager = nullptr;
	bool testingMode = false;
	bool sixTileMode = false;
	bool greyBoardMode = false;
	bool ai = false;

	// iterates over arguements and sets modes
	for(int i = 0; i < argc; ++i) {
		std::string arguement = argv[i];
		if(arguement == TESTING_MODE_ARGUMENT) {
			testingMode = true;
		}
		if (arguement == ADV_6_TILE_MODE_ARGUMENT) {
			sixTileMode = true;
		}
		if (arguement == ADV_GREY_BOARD_MODE_ARGUMENT) {
			greyBoardMode = true;
		}
		if (arguement == AI_MODE_ARGUMENT) {
			ai = true;
		}
	}

	if (testingMode) {
		testing(argc, argv, sixTileMode, greyBoardMode, gameManager);
	} else if ((sixTileMode || greyBoardMode) && !ai) {
		gameTypePrint(sixTileMode, greyBoardMode, ai);
		gameManager = new GameManager(sixTileMode, greyBoardMode, ai);
		runMenu(gameManager);
	} else if (ai && !sixTileMode && !greyBoardMode) {
		gameTypePrint(sixTileMode, greyBoardMode, ai);
		gameManager = new GameManager(sixTileMode, greyBoardMode, ai);
		runMenu(gameManager);
	} else {
		if (argc > 1) {
			std::cout << 
			"Unknown command line arguments specified, starting game normally..." 
			<< std::endl << std::endl;
		}
		gameManager = new GameManager();
		// Run the main menu
		runMenu(gameManager);
	}

	delete gameManager;

	return EXIT_SUCCESS;
}

void runMenu(GameManager* gameManager) {
	const std::string choice1 = "1";
	const std::string choice2 = "2";
	const std::string choice3 = "3";
	const std::string choice4 = "4";

	std::cout << "Welcome to Azul!" << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << "" << std::endl;

	Input input;
	std::string choice;
	
	bool exitMenu = false;
	while (!exitMenu) {
		menuText();
		std::cout << std::endl;
		
		choice = input.getSingleInput();

		if (choice == choice1) {
			exitMenu = gameManager->newGame();
		} else if (choice == choice2) {
			exitMenu = gameManager->loadGame();
		} else if (choice == choice3) {
			credits();
		} else if (choice == EOF_COMMAND || choice == choice4) {
			exitMenu = true;
		} else {
			std::cout << "Please select a valid option" << std::endl << std::endl;
		}
	}

	std::cout << "Goodbye"  << std::endl;
}

void menuText() {
	std::cout << "Menu"  << std::endl;
	std::cout << "----"  << std::endl;
	std::cout << "1. New Game"  << std::endl;
	std::cout << "2. Load Game"  << std::endl;
	std::cout << "3. Credits (Show student information)"  << std::endl;
	std::cout << "4. Quit" << std::endl;
}

void credits() {
	std::cout << "-------------------------CREDITS-------------------------" << std::endl;
	std::cout << "Joshua Cervenjak (S3783156)  S3783156@student.rmit.edu.au" << std::endl;
	std::cout << "John   Patrikios (S3780973)  S3780973@student.rmit.edu.au" << std::endl;
	std::cout << "Alicia Hallal    (S3811836)  S3811836@student.rmit.edu.au" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void testing(int argc, char** argv, bool sixTileMode, bool greyBoardMode, 
				GameManager* gameManager) 
{
	if (argc == 3 && !sixTileMode && !greyBoardMode) {
		gameManager = new GameManager();
		gameManager->loadGame(std::string(argv[2]));
 	} else if (((argc == 4) && (sixTileMode && !greyBoardMode)) ||
		  ((argc == 4) && (!sixTileMode && greyBoardMode))) {
		gameManager = new GameManager(sixTileMode, greyBoardMode, false); 
		gameManager->loadGame(std::string(argv[3]));
	} else if (argc == 5 &&  sixTileMode && greyBoardMode) {
		gameManager = new GameManager(sixTileMode, greyBoardMode, false);  
		gameManager->loadGame(std::string(argv[4]));
	} else {
		std::cout << "Unrecognised arguments for testing mode\n\nUSAGE:\n\t" 
		<< TESTING_MODE_ARGUMENT << " <filename>" << std::endl;
	}
}

void gameTypePrint(bool sixTileMode, bool greyBoardMode, bool ai) {
	if (ai) {
		std::cout << "**Launching AI mode**" << std::endl;
		std::cout << std::endl;
	} else if (sixTileMode && !greyBoardMode) {
		std::cout << "**Launching 6 tile mode**" << std::endl;
		std::cout << std::endl;
	} else if (greyBoardMode && !sixTileMode) {
		std::cout << "**Launching GreyBoard mode**" << std::endl;
		std::cout << std::endl;
	} else if (sixTileMode && greyBoardMode) {
		std::cout << "**Launching GreyBoard mode with 6 Tiles**" << std::endl;
		std::cout << std::endl;
	}
}