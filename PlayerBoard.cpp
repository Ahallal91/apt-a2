#include "PlayerBoard.h"
#include "Types.h"
#include "PatternLine.h"

PlayerBoard::PlayerBoard() {
	// Create a 5x5 char array for the wall
	wall = new char* [WALL_DIM];
	for (int i = 0; i < WALL_DIM; i++) {
		wall[i] = new char[WALL_DIM];
	}

	// Initialise the 5x5 wall to empty tiles
	for (int y = 0; y < WALL_DIM; y++) {
		for (int x = 0; x < WALL_DIM; x++) {
			wall[y][x] = EMPTY;
		}
	}

	// Initalize the pattern lines; 5 rows.
	this->patternLines = new PatternLine * [WALL_DIM];
	for (int i = 0; i < WALL_DIM; i++) {
		// row 1 (index 0) has 1 column
		// row 2 (index 1) has 2 columns, etc
		this->patternLines[i] = new PatternLine(i + 1);
	}

}

PlayerBoard::~PlayerBoard() {
	// Delete the 5x5 wall char array and patternlines
	for (int i = 0; i < WALL_DIM; i++) {
		delete wall[i];
		delete patternLines[i];
	}
	delete[] wall;
	delete[] patternLines;
}

void PlayerBoard::setWallTile(int x, int y) {
	// Check that x and y are in bounds of wall
	if (x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
		wall[y][x] = pattern[y][x];
	}
}

char PlayerBoard::getWallTile(int x, int y) {
	//Check that x and y are in bounds of wall
	if (x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
		return wall[y][x];
	} else {
		return '\0';
	}
}