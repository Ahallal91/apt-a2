#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>

// User input Commands config
#define TURN_COMMAND 		"turn"
#define SAVE_COMMAND		"save"
#define EOF_COMMAND			"quit"

#define TURN_ARGUMENTS 		4
#define SAVE_ARGUMENTS		2

class Player;
// used for getting and validating input.
class Input {
public:
	Input();
	~Input();

	Player* enterPlayerName(int playerNum);
	
	/* Requests the user to enter a command during the game and validates the commands arguments
	 *
	 * Returns a vector of the arguments entered by the user ONLY IF the command is valid.
	 * If user enters EOF, will return vector containing quit string
	 * If the command was NOT valid in any way, returns an empty vector
	 *
	 * Example inputs:
	 * "hello" - not valid (hello not a command)
	 * "turn 7 P 8 9" - not valid (numbers too big for board, P not a tile and too many arguments)
	 * "turn 3 Y 1" - valid
	 * "save azulgame" - valid
	 * "save azulgame?/*" - not valid (not allowed question mark, forward slash or asterix in filenames)
	 */
	std::vector<std::string> getGameplayInput(std::istream& stream);

private:
	// Validates the turn command parameters
	bool validateTurnCommand(std::vector<std::string>& arguments);

	// Validates the save command parameters
	bool validateSaveCommand(std::vector<std::string>& arguments);

	// A helper function to split a string into a vector of strings deliminated by white space
	std::vector<std::string> explode(std::string input);

	// Converts a String to Uppercase
	void toUpper(std::string& str);
	
	// Convers a String to Lowercase
	void toLower(std::string& str);

};


#endif //INPUT_H