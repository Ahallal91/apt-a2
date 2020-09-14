#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
#include "Player.h"
#include "Types.h"

// REMEMBER TO DELET AFTER; used for debugging
#include <iostream>

GameLogic::GameLogic() {}

GameLogic::~GameLogic() {}

void GameLogic::initFactoryTiles(Factories* factories, TileBag* tileBag) {
	factories->resetFactories();

	// add the tiles from the tile bag onto the factory
	for (int numFactory = 0; numFactory < NUM_FACTORIES; numFactory++) {
		for (int numToAdd = 0; numToAdd < FACTORY_SIZE; numToAdd++) {
			factories->addToFactory(numFactory, tileBag->removeFrontTile());
		}
	}
}

/*
* Moves wall tiles and calculates points
* Also subtracts points based on number of broken tiles
*/
void GameLogic::addToWall(Player* player) {
	PlayerBoard* playerBoard = player->getPlayerBoard();

	// for all patterns
	for (int row = 0; row < WALL_DIM; row++) {
		if (playerBoard->getPatternLine(row)->isFull()) {
			bool found = false;
			// find where to place on the wall
			for (int col = 0; col < WALL_DIM && !found; col++) {
				if (playerBoard->getPatternLine(row)->getTileType() == pattern[row][col]) {
					playerBoard->setWallTile(col, row);
					calculatePoints(player, col, row);
					found = true;
				}
			}
		}
	}
}

void GameLogic::calculatePoints(Player* player, int x, int y) {
	PlayerBoard* playerBoard = player->getPlayerBoard();

	int playerPoints = player->getPoints();
	int pointsToAdd = 1; // 1 point for adding a new tile
	bool comboCol = false;
	bool comboRow = false;

	// counts tiles above
	bool finished = false;
	for (int row = y - 1; row >= 0 && !finished; row--) {
		if (playerBoard->getWallTile(x, row) != EMPTY) {
			comboCol = true;
			pointsToAdd++;
		} else {
			finished = true;
		}
	}

	// count tiles below
	finished = false;
	for (int row = y + 1; row < WALL_DIM && !finished; row++) {
		if (playerBoard->getWallTile(x, row) != EMPTY) {
			comboCol = true;
			pointsToAdd++;
		} else {
			finished = true;
		}
	}


	// count tiles left
	finished = false;
	for (int col = x - 1; col >= 0 && !finished; col--) {
		if (playerBoard->getWallTile(col, y) != EMPTY) {
			comboRow = true;
			pointsToAdd++;
		} else {
			finished = true;
		}
	}

	// count tiles right
	finished = false;
	for (int col = x + 1; col < WALL_DIM && !finished; col++) {
		if (playerBoard->getWallTile(col, y) != EMPTY) {
			comboRow = true;
			pointsToAdd++;
		} else {
			finished = true;
		}
	}

	// additional point for connecting both row and col
	if (comboCol && comboRow) {
		pointsToAdd++;
	}

	/*
	std::cout << player->getPlayerName() << " has been awared "
		<< pointsToAdd << " for placing tile at (" << x << ", " << y << ")" << std::endl;
	*/

	// calculate final scoring
	playerPoints += pointsToAdd;
	playerPoints += brokenLinePoints[playerBoard->getBrokenSize()];
	player->setPoints(playerPoints);
}

/*
This method resets a players board and adds remaing tiles back to the tile bag.

The order of traversal is the top pattern line to the bottom, then the broken line.
At each pattern line, takes the tiles starting from index 0, which would be visually
right-to-left on the console. The broken line is also removed the same way, right-to-left
(starting at largest index for broken line though)
*/
void GameLogic::resetBoard(Player* player, TileBag* tileBag) {
	// traverse all pattern lines
	for (int i = 0; i < WALL_DIM; i++) {
		PatternLine* patternLine = player->getPlayerBoard()->getPatternLine(i);

		// add tiles back to bag. -1 if it's full since it will be moved to the wall
		int numToAdd = patternLine->isFull() ? patternLine->getCurrentSize() - 1 : patternLine->getCurrentSize();
		for (int i = 0; i < numToAdd; i++) {
			tileBag->addToBag(patternLine->getTileType());
		}

		// clear the pattern line if it's full, else keep remaining tiles
		if (patternLine->isFull()) {
			patternLine->clear();
		}
	}

	// add the broken line tiles to back of the tile bag and clear
	for (int i = player->getPlayerBoard()->getBrokenSize() - 1; i >= 0; i--) {
		// don't add the tile of type FIRST back to the bag
		if (player->getPlayerBoard()->getBrokenTile(i) != FIRST) {
			tileBag->addToBag(player->getPlayerBoard()->getBrokenTile(i));
		}
	}
	player->getPlayerBoard()->clearBrokenLine();
}


// returns true if all factories and center are empty, false otherwise
// used for checking if a round is over
bool GameLogic::roundOver(Factories* factories) {
	return factories->areFactoriesEmpty();
}

/*
 * Allows the player to select tiles from a specified factory and place those
 * tiles into their patternLine/brokenLine. Players can only place tiles in
 * PatternLines that match the tile colour or are empty.
 * Returns true if the tiles are placed in the players patternLine/brokenLine
 */
bool GameLogic::takeTiles(Factories* factories, Player* player,
						  int factoryNumber, char tile, int destPatternLine, TileBag* tileBag) {
	bool retValue = false;
	// reduces input patternLine by 1 to fit array
	destPatternLine--;
	// checks if tile can be placed in patternLine
	if (playerTileCheck(player, tile, destPatternLine) &&
		factories->isTileInFactories(factoryNumber, tile) &&
		playerWallCheck(player, tile, destPatternLine)) {
		if (factoryNumber >= 1 && factoryNumber <= NUM_FACTORIES) {
			retValue = addTilesFromFact(factories, player, factoryNumber, tile,
										destPatternLine, tileBag);
		} else if (factoryNumber == 0) {
			// adds tiles from center factory to playerboard
			retValue = addTilesFromCenterFact(factories, player, factoryNumber,
											  tile, destPatternLine, tileBag);
		}
	}
	return retValue;
}

/* Takes tiles from the center factory and places them in the players
 * patternLine or brokenLine, tiles not added to brokenline go back to tilebag
 * returns true if the amount of tiles added is greater than zero.
 */
bool GameLogic::addTilesFromCenterFact(Factories* factories, Player* player,
									   int factoryNumber, char tile,
									   int destPatternLine, TileBag* tileBag) {
	bool retValue = false;
	std::vector<char>* tempTiles = factories->takeTilesCenterFactory(tile);
	for (unsigned int i = 0; i < tempTiles->size(); ++i) {
		if(destPatternLine != BROKEN_LINE) {
			if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)->addTile(tempTiles->at(i)))) {
				if (!(player->getPlayerBoard()->addBrokenTile(tempTiles->at(i)))) {
					tileBag->addToBag(tempTiles->at(i));
				}
			}
		} else if (destPatternLine == BROKEN_LINE) {
			if (!(player->getPlayerBoard()->addBrokenTile(tempTiles->at(i)))) {
				tileBag->addToBag(tempTiles->at(i));
			}
		}
	}
	if (tempTiles->size() > 0) {
		retValue = true;
	}
	delete tempTiles;
	tempTiles = nullptr;
	return retValue;
}

/* Takes tiles from factory and places them in the players
 * patternLine or brokenLine, tiles which cannot be added to the brokenLine
 * go back to the tilebag, returns true if any tile added was not empty.
 */
bool GameLogic::addTilesFromFact(Factories* factories, Player* player,
								 int factoryNumber, char tile, int destPatternLine, TileBag* tileBag) {
	bool retValue = false;
	char* tempTiles = factories->takeTilesFactory(factoryNumber - 1, tile);
	for (unsigned int i = 0; i < FACTORY_SIZE; ++i) {
		if (destPatternLine != BROKEN_LINE) {
			if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)->
			  addTile(tempTiles[i]))) {
				if (!(player->getPlayerBoard()->addBrokenTile(tempTiles[i]))) {
					tileBag->addToBag(tempTiles[i]);
				}
			}
		} else if (destPatternLine == BROKEN_LINE) {
			if (!(player->getPlayerBoard()->addBrokenTile(tempTiles[i]))) {
				tileBag->addToBag(tempTiles[i]);
			}
		}
		if (tempTiles[i] != '\0') {
			retValue = true;
		}
	}
	delete tempTiles;
	tempTiles = nullptr;
	return retValue;
}

/* Checks if the tile passed in matches the type of tile in the players
 * patternLine. If the patternLine is empty or matching it will return true
 * if the destination is the brokenLine it will also return true.
 */
bool GameLogic::playerTileCheck(Player* player, char tile, int destPatternLine) {
	bool retValue = false;
	if (destPatternLine != BROKEN_LINE) {
		char tileType = player->
			getPlayerBoard()->
			getPatternLine(destPatternLine)->
			getTileType();
		if (tileType == EMPTY || tileType == tile) {
			retValue = true;
		}
	} else if (destPatternLine == BROKEN_LINE) {
		retValue = true;
	}
	return retValue;
}

bool GameLogic::playerWallCheck(Player* player, char tile, int destPatternLine) {
	bool retValue = true;
	if (destPatternLine != BROKEN_LINE) {
		int tileLocation = this->tileLocation(destPatternLine, tile);
		if (player->getPlayerBoard()->getWallTile(tileLocation, destPatternLine) == tile) {
				retValue = false;
		}
	} else if (destPatternLine == BROKEN_LINE) {
		retValue = true;
	}
	return retValue;
}

int GameLogic::tileLocation(int destPatternLine, char tile) {
	int tileCount = 0;
	if (tile == DARK_BLUE) {
		tileCount = 0;
	} else if (tile == YELLOW) {
		tileCount = 1;
	} else if (tile == RED) {
		tileCount = 2;
	} else if (tile == BLACK) {
		tileCount = 3;
	} else if (tile == LIGHT_BLUE) {
		tileCount = 4;
	}

	tileCount = tileCount + destPatternLine;
	if (tileCount > WALL_DIM) {
		tileCount = 0 + destPatternLine;
	}
	return tileCount;
}