#include <iostream>
#include "GameManager.h"

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

		} else if (std::cin.eof() || choice == choice4) {
			exitMenu = true;
		} else {
			std::cout << "Please select a valid option" << std::endl;
		}
	}
}

void menuText() {
	std::cout << "Welcome to Azul!" << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Menu" << std::endl;
	std::cout << "----" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Credits (Show student information)" << std::endl;
	std::cout << "4. Quit" << std::endl;
}

void credits() {
	std::cout << "----------CREDITS----------" << std::endl;
	std::cout << "Joshua Cervenjak (S3783156)" << std::endl;
	std::cout << "John Patrikios (S3780973)" << std::endl;
	std::cout << "Alicia Hallal (S3811836)" << std::endl;
	std::cout << "---------------------------" << std::endl;
}