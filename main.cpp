#include <iostream>

#include "GameManager.h"
#include "Input.h"

#define TESTING_MODE_ARGUMENT	"-t"

void runMenu(GameManager* gameManager);
void credits();
void menuText();

int main(int argc, char** argv) {
	GameManager* gameManager = new GameManager();

	if (argc >= 2 && std::string(argv[1]) == TESTING_MODE_ARGUMENT) {
		if (argc == 3) {
			gameManager->loadGame(std::string(argv[2]));
		} else {
			std::cout << "Unrecognised arguments for testing mode\n\nUSAGE:\n\t" 
			<< TESTING_MODE_ARGUMENT << " <filename>" << std::endl;
		}
	} else {
		if (argc > 1) {
			std::cout << 
			"Unknown command line arguments specified, starting game normally..." 
			<< std::endl << std::endl;
		}

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
