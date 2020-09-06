#include "Input.h"
#include <iostream>
#include "Player.h"
#include "Types.h"
#include <istream>
#include <sstream>

Input::Input() {}

Input::~Input() {}


// could have loop, but for now we'll assume the user will enter a single name
Player* Input::enterPlayerName(int playerNum) {
	std::string name = "";
	std::cout << "Enter a name for player " << playerNum << std::endl << "> ";
	std::cin >> name;

	return new Player(name);
}

// TODO return boolean if user entered EOF character
void Input::getTurn() {

}
