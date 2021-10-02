#include "PlayerBoard.h"
#include "Types.h"
#include <iostream>
#define EMPTY_TUPLE 	-1

PlayerBoard::PlayerBoard() {
	this->wallSize = WALL_DIM;
	this->numBrokenTiles = NUM_BROKEN_TILES;
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
	clearPlayerWall();
}

PlayerBoard::PlayerBoard(bool advancedMode, bool greyBoard) {
	this->greyBoard = greyBoard;
	this->advancedMode = advancedMode;
	if (advancedMode) {
		this->wallSize = ADV_WALL_DIM;
		this->numBrokenTiles = ADV_NUM_BROKEN_TILES;
	} else {
		this->wallSize = WALL_DIM;
		this->numBrokenTiles = NUM_BROKEN_TILES;
	}
	// Create a 5x5 char array for the wall and patternline
	this->patternLines = new PatternLine * [wallSize];
	this->wall = new char* [wallSize];
	for (int i = 0; i < wallSize; i++) {
		this->patternLines[i] = new PatternLine(i + 1);
		this->wall[i] = new char[wallSize];
	}

	// Initialise broken line
	brokenLine = new std::vector<char>;

	// Initialise the 5x5 wall to empty tiles
	clearPlayerWall();
}

PlayerBoard::PlayerBoard(PlayerBoard& other) {
	this->greyBoard = other.greyBoard;
	this->advancedMode = other.advancedMode;
	this->numBrokenTiles = other.numBrokenTiles;
	this->wallSize = other.wallSize;
	this->brokenLine = other.brokenLine;
	this->patternLines = other.patternLines;
	this->wall = new char* [wallSize];

	for (int i = 0; i < wallSize; i++) {
		this->patternLines[i] = new PatternLine(i + 1);
		this->wall[i] = new char[wallSize];
	}
	for (int y = 0; y < wallSize; y++) {
		for (int x = 0; x < wallSize; x++) {
			wall[y][x] = other.wall[y][x];
		}
		this->patternLines[y] = other.patternLines[y];
	}
}

PlayerBoard::PlayerBoard(PlayerBoard&& other) {
	this->greyBoard = other.greyBoard;
	this->advancedMode = other.advancedMode;
	this->numBrokenTiles = other.numBrokenTiles;
	this->wallSize = other.wallSize;
	this->brokenLine = other.brokenLine;
	this->patternLines = other.patternLines;
	this->wall = new char* [wallSize];

	for (int i = 0; i < wallSize; i++) {
		this->patternLines[i] = new PatternLine(i + 1);
		this->wall[i] = new char[wallSize];
	}
	for (int y = 0; y < wallSize; y++) {
		for (int x = 0; x < wallSize; x++) {
			wall[y][x] = other.wall[y][x];
		}
		this->patternLines[y] = other.patternLines[y];
	}
}

PlayerBoard::~PlayerBoard() {
	// Delete the 5x5 wall char array and patternlines
	for (int i = 0; i < wallSize; i++) {
		delete wall[i];
		delete patternLines[i];
	}
	delete[] wall;
	delete[] patternLines;

	// Clean up broken line
	brokenLine->clear();
	delete brokenLine;
}

bool PlayerBoard::setWallTile(int x, int y, char tile) {
	bool success = false;

	//Check that x and y are in bounds of wall
	if (x >= 0 && x < wallSize && y >= 0 && y < wallSize) {
		if (wall[y][x] == EMPTY) {
			if(greyBoard) {
				wall[y][x] = tile;
			} else if (advancedMode) {
				wall[y][x] = advPattern[y][x];
			} else {
				wall[y][x] = pattern[y][x];
			}
			success = true;
		}
	}

	return success;
}

void PlayerBoard::removeWallTile(int x, int y) {
	//Check that x and y are in bounds of wall
	if (x >= 0 && x < wallSize && y >= 0 && y < wallSize) {
		wall[y][x] = EMPTY;
	}
}

char PlayerBoard::getWallTile(int x, int y) {
	char tile = EMPTY;

	//Check that x and y are in bounds of wall
	if (x >= 0 && x < wallSize && y >= 0 && y < wallSize) {
		tile = wall[y][x];
	}

	return tile;
}

bool PlayerBoard::checkWallCol(int y, char tile) {
	bool retValue = false;
	if (y >= 0 && y < wallSize) {
		for (int x = 0; x < wallSize; ++x) {
			if (wall[y][x] == tile) {
				retValue = true;
			}
		}
	}
	return retValue;
}

std::tuple<int, int, char> PlayerBoard::getWallCombo(int y, int previousX) {
	std::tuple<int, int, char> retValue;
	bool done = false;

	for(int x = 0; x < wallSize && !done; ++x) {
		if(wall[y][x] != EMPTY) {
			if(x+1 < wallSize && wall[y][x + 1] == EMPTY) {
				retValue = getWallCharForCombo(y, x + 1);
				done = true;
			} else if ((x-1 >= 0) && wall[y][x-1] == EMPTY) {
				retValue = getWallCharForCombo(y, x-1);
				done = true;
			}
		} 
	}
	
	for(int x = 0; x < wallSize && !done; ++x) {
		if(wall[y][x] == EMPTY) {
			retValue = getWallCharForCombo(y, x);
			done = true;
		}
	}
	
	while (!done) {
		if (previousX == -1) {
			for(int i = 0; i < wallSize && !done; ++i) {
				if(wall[y][i] == EMPTY) {
					retValue = getWallCharForCombo(y, i);
					done = true;
				}
			}
		} else {
			while(wall[y][previousX] != EMPTY) {
				previousX++;
			}
			retValue = getWallCharForCombo(y, previousX);
			done = true;
		}	
	}
	return retValue;
}

std::tuple<int, int, char> PlayerBoard::getWallCharForCombo(int y, int x) {
	std::tuple<int, int, char> retValue;
	char tile = pattern[y][x];
	retValue = std::make_tuple(y, x, tile);
	return retValue;
}

// PATTERN LINE METHODS

PatternLine* PlayerBoard::getPatternLine(int row) {
	PatternLine* patternLine = nullptr;

	if (row >= 0 && row < wallSize) {
		patternLine = patternLines[row];
	}

	return patternLine;
}

// BROKEN LINE METHODS
bool PlayerBoard::addBrokenTile(char tile) {
	bool success = false;

	if ( (int) brokenLine->size() < numBrokenTiles && tile != '\0') {
		brokenLine->push_back(tile);
		success = true;
	}

	return success;
}

char PlayerBoard::getBrokenTile(int index) {
	char tile = EMPTY;

	if (index >= 0 && index < numBrokenTiles && index < (int) brokenLine->size()) {
		tile = brokenLine->at(index);
	}

	return tile;
}

bool PlayerBoard::brokenLineHasFirst() {
	bool retValue = false;
	unsigned int index = 0;
	while(index < brokenLine->size() && !retValue) {
		if (getBrokenTile(index) == FIRST) {
			retValue = true;
		}
		index++;
	}

	return retValue;
}

int PlayerBoard::getBrokenSize() {
	return brokenLine->size();
}

void PlayerBoard::clearBrokenLine() {
	brokenLine->clear();
}

void PlayerBoard::clearPlayerWall() {
	for (int y = 0; y < wallSize; y++) {
		for (int x = 0; x < wallSize; x++) {
			wall[y][x] = EMPTY;
		}
	}
}

std::map<int, int> PlayerBoard::getAvailablePatternLines() {
	std::map<int, int> retValue;
	for(int i = 0; i < wallSize; ++i) {
		if(!patternLines[i]->isFull()) {
			retValue.insert(std::pair<int, int>(i, patternLines[i]->sizeDifference())); 
		}
	}
	return retValue;
}