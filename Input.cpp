#include <istream>
#include <sstream>
#include <iostream>

#include "Input.h"
#include "Player.h"
#include "Types.h"

Input::Input() {
	this->advancedMode = false;
	this->greyBoard = false;
}

Input::Input(bool advancedMode, bool greyBoard) {
	this->advancedMode = advancedMode;
	this->greyBoard = greyBoard;
}

Input::~Input() {}


std::string Input::enterPlayerName(int playerNum) {
	std::string name = "";
	bool eof = false;

	while (name.empty() && !eof) {
		std::string input = "";
		std::cout << "Enter a name for Player " << playerNum << std::endl << "> ";
		
		std::getline(std::cin, input);
		
		if(std::cin.eof()) {
			eof = true;
		}

		// A vector that contains the name seperated by white spaces
		std::vector<std::string> nameVec = explode(input);

		// Append each vector index to the name if not empty
		if (!nameVec.empty()) {
			for (unsigned int i = 0; i < nameVec.size(); i++) {
				name.append(nameVec[i]);

				// Dont append a space if its the last string in vector
				if (i != nameVec.size() - 1) {
					name.append(" ");
				}
			}
		}

		if (name.empty() && !eof) {
			std::cout << "Please enter a valid name!" << std::endl;
		}
	}
	
	return name;
}

std::string Input::getSingleInput() {
	std::string retVal = "";
	
	std::string input;
	std::cout << "> ";
	std::getline(std::cin, input);

	if(std::cin.eof()) {
		retVal = EOF_COMMAND;
	} else {
		std::vector<std::string> inputVec = explode(input);

		if(inputVec.size() == 1) {
			retVal = inputVec[0];
		}
	}

	return retVal;

}

std::vector<std::string> Input::getGameplayInput(std::istream& stream, std::string aiCommand) {
	
	// A string containing the full line a user inputted
	std::string input;

	// Checks whether eof was entered to quit the game
	bool eof = false;

	// Gets the input of the user one char at a time while checking for EOF
	bool entered = false;
	while (!entered && aiCommand.empty()) {
		if (stream.eof()) {
			entered = true;
			eof = true;
		}

		char c = stream.get();
		if (c != '\n') {
			input = input + c;
		} else {
			entered = true;
		}
	}

	if(!aiCommand.empty()) {
		input = aiCommand;
	}
	
	// The arguments entered in the users command
	std::vector<std::string> arguments = explode(input);
	
	std::string command;
	if(!arguments.empty()) {
		// convert the command to lowercase to accept non case sensitive inputs
		toLower(arguments[0]);
		
		command = arguments[0];
	}

	// Checks whether an input is valid
	bool valid = false;

	// Turn command
	if (command == TURN_COMMAND) {
		// Validate turn command | FORMAT: turn [0-5] [RYDBU] [1-6]
		if (arguments.size() == TURN_ARGUMENTS) {
			valid = validateTurnCommand(arguments);
		}

		// Save command
	} else if (command == SAVE_COMMAND) {
		// Validate save command (FORMAT: save [filename])
		if (arguments.size() == SAVE_ARGUMENTS) {
			valid = validateSaveCommand(arguments);
		}
	} else if (command == GREYBOARD_COMMAND && greyBoard) {
		if (arguments.size() == MOVE_ARGUMENTS) {
			valid = validateMoveCommand(arguments);
		}
	}

	// If the input is not valid in any way, return an empty vector
	if (!valid) {
		arguments.clear();
	}

	// If EOF was entered, set the return argument to "quit"
	if (eof) {
		arguments = explode(EOF_COMMAND);
	}

	return arguments;
}

bool Input::validateTurnCommand(std::vector<std::string>& arguments) {
	bool factoryValid = false;
	bool tileValid = false;
	bool rowValid = false;
	int wallSize = 0;
	if (advancedMode) {
		wallSize = ADV_WALL_DIM;
	} else {
		wallSize = WALL_DIM;
	}
	// Convert the tile input to uppercase to allow non case sensitive input
	toUpper(arguments[2]);

	std::string factoryStr = arguments[1];
	std::string tileStr = arguments[2];
	std::string rowStr = arguments[3];

	// Validate the factory (2nd parameter) is a number 0 - 5
	try {
		int factory = std::stoi(factoryStr);
		factoryValid = (factory >= 0 && factory <= wallSize && factoryStr.length() == 1);
	} catch (const std::exception& e) {}

	// Validate that the tile (3rd parameter) is a tile char
	if (tileStr.length() == 1) {
		char tile = tileStr[0];
		tileValid = (tile == RED || tile == YELLOW || tile == DARK_BLUE 
					|| tile == LIGHT_BLUE || tile == BLACK || 
					(advancedMode && tile == ORANGE));
	}

	// Validate the row / pattern line (4th parameter) is a number 1 - 6
	try {
		int row = std::stoi(rowStr);
		rowValid = (row > 0 && row <= wallSize + 1 && rowStr.length() == 1);
	} catch (const std::exception& e) {}

	return (factoryValid && tileValid && rowValid);
}

bool Input::validateMoveCommand(std::vector<std::string>& arguments) {
	bool wallColValid = false;
	bool patValid = false;
	int wallSize = 0;

	if (advancedMode) {
		wallSize = ADV_WALL_DIM;
	} else {
		wallSize = WALL_DIM;
	}

	std::string patternStr = arguments[1];
	std::string wallCol = arguments[2];

	// Validate the row / pattern line (4th parameter) is a number 1 - 6 (or 7 in adv mode)
	try {
		int row = std::stoi(patternStr);
		patValid = (row > 0 && row <= wallSize + 1 && patternStr.length() == 1);
	} catch (const std::exception& e) {}

	// Validate the wall col
	try {
		int row = std::stoi(wallCol);
		wallColValid = (row > 0 && row <= wallSize + 1 && wallCol.length() == 1);
	} catch (const std::exception& e) {}

	return (wallColValid && patValid);
}

bool Input::validateSaveCommand(std::vector<std::string>& arguments) {
	bool filenameValid = true;

	std::string filename = arguments[1];

	// Characters not allowed in filenames
	const char invalidCharacters[] = {'<', '>', ':', '"', '/', '\\', '|', '?', '*'};

	for (const char& c : invalidCharacters) {
		if (filename.find(c) != std::string::npos) {
			filenameValid = false;
		}
	}

	return filenameValid;
}

std::vector<std::string> Input::explode(std::string str) {

	// Vector of the command arguments seperated by white space
	std::vector<std::string> arguments;

	std::string word = "";
	for (char& c : str) {
		if (c == ' ') {
			if (word.find_first_not_of(' ') != std::string::npos) {
				arguments.push_back(word);
			}
			word = "";
		} else {
			word = word + c;
		}
	}
	if (word.find_first_not_of(' ') != std::string::npos) {
		arguments.push_back(word);
	}

	return arguments;
}

void Input::toUpper(std::string& str) {
	std::string newStr;
	
	for(char& c : str) {
		newStr += std::toupper(c);
	}

	str = newStr;
}

void Input::toLower(std::string& str) {
	std::string newStr;
	
	for(char& c : str) {
		newStr += std::tolower(c);
	}

	str = newStr;
}
