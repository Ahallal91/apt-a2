#include "Output.h"
#include <iostream>


Output::Output() {}

Output::~Output() {}


void Output::outputRound(int roundNum) {
	std::cout << "== START ROUND " << roundNum << " ==" << std::endl;
}

// output the current factory
void Output::outputFactory(Factory* factory) {

}

// outputs the players board
void Output::outputBoard(Player* player) {

}

