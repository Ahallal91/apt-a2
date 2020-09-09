#include "PlayerBoard.h"
#include "Types.h"
//#include "PatternLine.h"

PlayerBoard::PlayerBoard() {
	// Create a 5x5 char array for the wall and patternline
	this->patternLines = new PatternLine * [WALL_DIM];
	this->wall = new char* [WALL_DIM];
	for (int i = 0; i < WALL_DIM; i++) {
		this->patternLines[i] = new PatternLine(i + 1);
		this->wall[i] = new char[WALL_DIM];
	}
	// Initialise broken line
	brokenLine = new std::vector<char>;

	// Initialise the 5x5 wall to empty tiles
	for (int y = 0; y < WALL_DIM; y++) {
		for (int x = 0; x < WALL_DIM; x++) {
			wall[y][x] = EMPTY;
		}
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

	// Clean up broken line
	brokenLine->clear();
	delete brokenLine;
}

bool PlayerBoard::setWallTile(int row, char tile) {
	bool success = false;

	if (row >= 0 && row < WALL_DIM) {
		for (int col = 0; col < WALL_DIM && !success; col++) {
			if (pattern[row][col] == tile) {
				this->wall[row][col] = tile;
				success = true;
			}
		}
	}

	return success;
}

//void PlayerBoard::removeWallTile(int x, int y) {
//	//Check that x and y are in bounds of wall
//	if (x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
//		wall[y][x] = EMPTY;
//	}
//}

char PlayerBoard::getWallTile(int x, int y) {
	char tile = '\0';

	//Check that x and y are in bounds of wall
	if (x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
		tile = wall[y][x];
	}

	return tile;
}

// PATTERN LINE METHODS

PatternLine* PlayerBoard::getPatternLine(int row) {
	PatternLine* patternLine = nullptr;

	if (row >= 0 && row < WALL_DIM) {
		patternLine = patternLines[row];
	}

	return patternLine;
}

// BROKEN LINE METHODS

bool PlayerBoard::addBrokenTile(char tile) {
	bool success = false;

	if (brokenLine->size() < NUM_BROKEN_TILES && tile != '\0') {
		brokenLine->push_back(tile);
		success = true;
	}

	return success;
}

char PlayerBoard::getBrokenTile(int index) {
	char tile = '\0';

	if (index >= 0 && index < NUM_BROKEN_TILES && index < (int) brokenLine->size()) {
		tile = brokenLine->at(index);
	}

	return tile;
}

int PlayerBoard::getBrokenSize() {
	return brokenLine->size();
}

void PlayerBoard::clearBrokenLine() {
	brokenLine->clear();
}