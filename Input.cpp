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

std::vector<std::string> Input::getGameplayInput() {

	// A string containing the full line a user inputted
	std::string input;

	// Checks whether eof was entered to quit the game
	bool eof = false;
	
	// Gets the input of the user one char at a time while checking for EOF
	bool entered = false;
	while(!entered) {
		if(std::cin.eof()) {
			entered = true;
			eof = true;
		}

		char c = std::cin.get();
		if(c != '\n') {
			input = input + c;
		} else {
			entered = true;
		}
	}

	// The arguments entered in the users command
	std::vector<std::string> arguments = explode(input);
	std::string command = arguments[0];
	
	// Checks whether an input is valid
	bool valid = false;
	
	// Turn command
	if(command == "turn") {
		// Validate turn command | FORMAT: turn [0-5] [RYDBU] [1-5]
		if(arguments.size() == TURN_ARGUMENTS) {
			valid = validateTurnCommand(arguments);
		}
	
	// Save command
	} else if(command == "save") {
		// Validate save command (FORMAT: save [filename])
		if(arguments.size() == SAVE_ARGUMENTS) {
			valid = validateSaveCommand(arguments);
		}
	}

	// If the input is not valid in any way, return an empty vector
	if(!valid) {
		arguments.clear();
	}

	// If EOF was entered, set the return argument to "quit"
	if(eof) {
		arguments = explode("quit");
	}

	return arguments;
}

bool Input::validateTurnCommand(std::vector<std::string> arguments) {
	bool factoryValid = false;
	bool tileValid = false;
	bool rowValid = false;

	std::string factoryStr = arguments[1];
	std::string tileStr = arguments[2];
	std::string rowStr = arguments[3];
	
	// Validate the factory (2nd parameter) is a number 0 - 5
	try {
		int factory = std::stoi(factoryStr);
		factoryValid = (factory >= 0 && factory <= WALL_DIM);
	} catch(const std::exception& e) {}
	
	// Validate that the tile (3rd parameter) is a tile char
	if(tileStr.length() == 1) {
		char tile = tileStr[0];
		tileValid = (tile == RED || tile == YELLOW || tile == DARK_BLUE || tile == LIGHT_BLUE || tile == BLACK);
	}

	// Validate the row / pattern line (4th parameter) is a number 1 - 5
	try {
		int row = std::stoi(rowStr);
		rowValid = (row > 0 && row <= WALL_DIM);
	} catch(const std::exception& e) {}

	return (factoryValid && tileValid && rowValid);
}

bool Input::validateSaveCommand(std::vector<std::string> arguments) {
	bool filenameValid = true;

	std::string filename = arguments[1];

	// Characters not allowed in filenames
	char invalidCharacters[] = {'<', '>', ':', '"', '/', '\\', '|', '?', '*'};

	for(char c : invalidCharacters) {
		if(filename.find(c) != std::string::npos) {
			filenameValid = false;
		}
	}

	return filenameValid;
}

std::vector<std::string> Input::explode(std::string str) {
	
	// Vector of the command keywords seperated by white space
	std::vector<std::string> arguments;

	std::string word = "";

	for(char c : str) {
		if(c == ' ') {
			arguments.push_back(word);
			word = "";
		} else {
			word = word + c;
		}
	}
	arguments.push_back(word);

	return arguments;
}
