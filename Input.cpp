#include "Input.h"
#include <iostream>
#include "Player.h"
#include "Types.h"
#include <istream>
#include <sstream>

Input::Input() {}

Input::~Input() {}


// Allows any name excluding entirely whitespace.
Player* Input::enterPlayerName(int playerNum) {
	bool valid = false;
	std::string name = "";
	std::cout << "Enter a name for player " << playerNum << std::endl << "> ";

	do {
		std::cin.ignore();
		std::getline(std::cin, name);
		for (int i = 0; i < name.size() && !valid; i++) {
			if (name.at(i) != ' ') {
				valid = true;
			}
		}
		if (!valid) {
			std::cout << "Please enter a valid name" << std::endl << "> ";
		}
	} while (!valid);
	return new Player(name);
}

// TODO return boolean if user entered EOF character
void Input::getTurn() {

}
