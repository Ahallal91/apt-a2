#include <iostream>
#include <limits>

#include "GameManager.h"

void printLine(std::string message);
void runMenu(GameManager* gameManager);
void credits();
void menuText();

int main(int argc, char** argv) {
	GameManager* gameManager = new GameManager();

	if (argc >= 2 && std::string(argv[1]) == "-t") {
		if (argc == 3) {
			gameManager->loadGame(std::string(argv[2]));
		} else {
			std::cout << "Unrecognised arguments for testing mode\n\nUSAGE:\n\t -t <filename>" << std::endl;
		}
	} else {
		if (argc > 1) {
			std::cout << "Unknown command line arguments specified, starting game normally..." << std::endl << std::endl;
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

	printLine("Welcome to Azul!");
	printLine("-------------------");
	printLine("");

	bool exitMenu = false;
	while (!exitMenu) {
		menuText();
		std::string choice;
		std::cin >> choice;

		//ignore any characters after whitespace until \n to not intefere with input later in the program
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (choice == choice1) {
			exitMenu = gameManager->newGame();
		} else if (choice == choice2) {
			exitMenu = gameManager->loadGame();
		} else if (choice == choice3) {
			credits();
		} else if (std::cin.eof() || choice == choice4) {
			exitMenu = true;
		} else {
			printLine("Please select a valid option");
		}
	}

	printLine("Goodbye");
}

void menuText() {
	printLine("Menu");
	printLine("----");
	printLine("1. New Game");
	printLine("2. Load Game");
	printLine("3. Credits (Show student information)");
	printLine("4. Quit");
	std::cout << "> ";
}

void credits() {
	printLine("-------------------------CREDITS-------------------------");
	printLine("Joshua Cervenjak (S3783156)  S3783156@student.rmit.edu.au");
	printLine("John   Patrikios (S3780973)  S3780973@student.rmit.edu.au");
	printLine("Alicia Hallal    (S3811836)  S3811836@student.rmit.edu.au");
	printLine("---------------------------------------------------------");
}

void printLine(std::string message) {
	std::cout << message << std::endl;
}