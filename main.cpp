#include <iostream>
#include "GameManager.h"

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
		if (choice == choice1) {
			exitMenu = true;
			// TODO may not want to declare this inside here. Will move when required later.
			GameManager* gameManager = new GameManager();
			gameManager->playGame();
			delete gameManager;
		} else if (choice == choice2) {

		} else if (choice == choice3) {
			credits();
		} else if (std::cin.eof() || choice == choice4) {
			exitMenu = true;
		} else {
			std::cout << "Please select a valid option" << std::endl;
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
}

void credits() {
	printLine("----------CREDITS----------");
	printLine("Joshua Cervenjak (S3783156)");
	printLine("John   Patrikios (S3780973)");
	printLine("Alicia Hallal    (S3811836)");
	printLine("---------------------------");
}

void printLine(std::string message) {
	std::cout << message << std::endl;
}