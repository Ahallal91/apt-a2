#include <iostream>
#include "GameManager.h"

#include <limits>

void printLine(std::string message);
void runMenu();
void credits();
void menuText();

int main(int argc, char** argv) {
	runMenu();
	return EXIT_SUCCESS;
}

void runMenu() {
	bool exitMenu = false;
	const std::string choice1 = "1";
	const std::string choice2 = "2";
	const std::string choice3 = "3";
	const std::string choice4 = "4";

	printLine("Welcome to Azul!");
	printLine("-------------------");
	printLine("");

	while (!exitMenu) {
		menuText();
		std::string choice;
		std::cin >> choice;
		
		//ignore any characters after whitespace until \n to not intefere with input later in the program
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if (choice == choice1) {
			exitMenu = true;
			// TODO may not want to declare this inside here. Will move when required later.
			GameManager* gameManager = new GameManager();
			//gameManager->playGame();
			gameManager->newGame();
			delete gameManager;
		} else if (choice == choice2) {

		} else if (choice == choice3) {
			credits();
		} else if (std::cin.eof() || choice == choice4) {
			exitMenu = true;
		} else {
			printLine("Please select a valid option");
		}
	}
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