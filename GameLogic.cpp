#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
#include "Player.h"
#include "Types.h"
#include "PlayerBoard.h"

#define POSITIVE 		'+'
#define NEGATIVE 		'-'
#define DEFAULT_BROKEN_LINE 5
#define ADV_BROKEN_LINE 6

// amount of points lost where the index is the amount of broken line tiles
constexpr int brokenLinePoints[] = {0, -1, -2, -4, -6, -8, -11, -14};
// amount of points lost where the index is the amount of broken line tiles
constexpr int advBrokenLinePoints[] = {0, -1, -2, -4, -6, -8, -11, -14, -18};

GameLogic::GameLogic() {
	this->advancedMode = false;
	this->greyBoard = false;
	this->wallSize = WALL_DIM;
	this->brokenLineNumber = DEFAULT_BROKEN_LINE;
}

GameLogic::GameLogic(bool advancedMode, bool greyBoard) {
	this->advancedMode = advancedMode;
	this->greyBoard = greyBoard;
	if (advancedMode) {
		this->wallSize = ADV_WALL_DIM;
		this->brokenLineNumber = ADV_BROKEN_LINE;
	} else {
		this->wallSize = WALL_DIM;
		this->brokenLineNumber = DEFAULT_BROKEN_LINE;
	}
}

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

void GameLogic::addToWall(Player* player) {
	// for all patterns
	for (int row = 0; row < wallSize; row++) {
		if (player->getPlayerBoard()->getPatternLine(row)->isFull()) {
			bool found = false;
			
			// find where to place on the wall
			for (int col = 0; col < wallSize && !found; col++) {
				if (player->getPlayerBoard()->getPatternLine(row)->getTileType() 
					== pattern[row][col] || 
					(player->getPlayerBoard()->getPatternLine(row)->getTileType() 
					== advPattern[row][col] && advancedMode)) {
					player->getPlayerBoard()->setWallTile(col, row, EMPTY);
					calculatePoints(player, col, row);
					found = true;
				}
			}
		}
	}
	
	// minus points from broken line.
	if(advancedMode) {
		player->setPoints(player->getPoints()
			+ advBrokenLinePoints[player->getPlayerBoard()->getBrokenSize()]);
	} else {
		player->setPoints(player->getPoints()
			+ brokenLinePoints[player->getPlayerBoard()->getBrokenSize()]);
	}
}

void GameLogic::calculatePoints(Player* player, int x, int y) {
	int playerPoints = player->getPoints();
	// 1 point for adding a new tile
	int pointsToAdd = 1;
	bool comboCol = false;
	bool comboRow = false;

	// counts tiles above
	countTiles(y, x, NEGATIVE, pointsToAdd, comboCol, player->getPlayerBoard(), false);

	// count tiles below
	countTiles(y, x, POSITIVE, pointsToAdd, comboCol, player->getPlayerBoard(), false);

	// count tiles left
	countTiles(x, y, NEGATIVE, pointsToAdd, comboRow, player->getPlayerBoard(), true);

	// count tiles right
	countTiles(x, y, POSITIVE, pointsToAdd, comboRow, player->getPlayerBoard(), true);

	// additional point for connecting both row and col
	if (comboCol && comboRow) {
		pointsToAdd++;
	}

	// calculate final scoring
	playerPoints += pointsToAdd;
	player->setPoints(playerPoints);
}


void GameLogic::countTiles(int start, int tileLoc, char sign, int& pointsToAdd,
						   bool& combo, PlayerBoard* playerBoard, bool horizontal) {
	bool finished = false;
	if (sign == NEGATIVE) {
		for (int row = start - 1; row >= 0 && !finished; row--) {
			char compareTile = '\0';
			if (horizontal) {
				compareTile = playerBoard->getWallTile(row, tileLoc);
			} else {
				compareTile = playerBoard->getWallTile(tileLoc, row);
			}
			if (compareTile != EMPTY) {
				combo = true;
				pointsToAdd++;
			} else {
				finished = true;
			}
		}
	} else if (sign == POSITIVE) {
		for (int row = start + 1; row < wallSize && !finished; row++) {
			char compareTile = '\0';
			if (horizontal) {
				compareTile = playerBoard->getWallTile(row, tileLoc);
			} else {
				compareTile = playerBoard->getWallTile(tileLoc, row);
			}
			if (compareTile != EMPTY) {
				combo = true;
				pointsToAdd++;
			} else {
				finished = true;
			}
		}
	}
}

void GameLogic::resetBoard(Player* player, TileBag* tileBag) {
	// traverse all pattern lines
	for (int i = 0; i < wallSize; i++) {
		PatternLine* patternLine = player->getPlayerBoard()->getPatternLine(i);

		// add tiles back to bag. -1 if it's full since it will be moved to the wall
		int numToAdd = patternLine->isFull()
			? patternLine->getCurrentSize() - 1
			: patternLine->getCurrentSize();

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

bool GameLogic::roundOver(Factories* factories) {
	return factories->areFactoriesEmpty();
}

bool GameLogic::takeTiles(Factories* factories, Player* player,
						  int factoryNumber, char tile, int destPatternLine,
						  TileBag* tileBag) {
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

bool GameLogic::addTilesFromCenterFact(Factories* factories, Player* player,
									   int factoryNumber, char tile, int destPatternLine, 
									   TileBag* tileBag) {
	bool retValue = false;
	std::vector<char>* tempTiles = factories->takeTilesCenterFactory(tile);
	for (unsigned int i = 0; i < tempTiles->size(); ++i) {
		if (destPatternLine != brokenLineNumber) {
			if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)
				  ->addTile(tempTiles->at(i)))) {
				if (!(player->getPlayerBoard()->addBrokenTile(tempTiles->at(i)))) {
					tileBag->addToBag(tempTiles->at(i));
				}
			}
		} else if (destPatternLine == brokenLineNumber) {
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

bool GameLogic::addTilesFromFact(Factories* factories, Player* player,
								 int factoryNumber, char tile, int destPatternLine, 
								 TileBag* tileBag) {
	bool retValue = false;
	char* tempTiles = factories->takeTilesFactory(factoryNumber - 1, tile);
	for (unsigned int i = 0; i < FACTORY_SIZE; ++i) {
		if (destPatternLine != brokenLineNumber) {
			if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)->
				  addTile(tempTiles[i]))) {
				if (!(player->getPlayerBoard()->addBrokenTile(tempTiles[i]))) {
					tileBag->addToBag(tempTiles[i]);
				}
			}
		} else if (destPatternLine == brokenLineNumber) {
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

bool GameLogic::playerTileCheck(Player* player, char tile, int destPatternLine) {
	bool retValue = false;
	if (destPatternLine != brokenLineNumber) {
		char tileType = player->
			getPlayerBoard()->
			getPatternLine(destPatternLine)->
			getTileType();
		if (tileType == EMPTY || tileType == tile) {
			retValue = true;
		}
	} else if (destPatternLine == brokenLineNumber) {
		retValue = true;
	}

	return retValue;
}

bool GameLogic::playerWallCheck(Player* player, char tile, int destPatternLine) {
	bool retValue = true;
	if (destPatternLine != brokenLineNumber) {
		for (int i = 0; i < wallSize; ++i) {
			if (player->getPlayerBoard()->getWallTile(i, destPatternLine) == tile) {
				retValue = false;
			}
		}
	} else if (destPatternLine == brokenLineNumber) {
		retValue = true;
	}

	return retValue;
}

bool GameLogic::playerMoveTileToWall(Player* player, int patternLine, int wallColumn) {
	bool retValue = false;
	// reduces input to fit real-pattern line array.
	patternLine--;
	wallColumn--;
	// gets the tile type of the patternline
	char tileType = player->getPlayerBoard()->getPatternLine(patternLine)->getTileType();

	if (patternLine >= 0 && patternLine < wallSize && wallColumn >= 0 && wallColumn
		< wallSize) {
		if(player->getPlayerBoard()->getPatternLine(patternLine)->isFull()) {
			if (player->getPlayerBoard()->checkWallCol(wallColumn, tileType) ||
				!(playerWallCheck(player, tileType, patternLine))) {
				retValue = false;
			} else {
				player->getPlayerBoard()->setWallTile(wallColumn, patternLine, tileType);
				player->getPlayerBoard()->getPatternLine(patternLine)->clear();
				calculatePoints(player, wallColumn, patternLine);
				retValue = true;
			}
		}
	}
	
	// minus points from broken line.
	if(advancedMode && retValue) {
		player->setPoints(player->getPoints()
			+ advBrokenLinePoints[player->getPlayerBoard()->getBrokenSize()]);
	} else if (retValue) {
		player->setPoints(player->getPoints()
			+ brokenLinePoints[player->getPlayerBoard()->getBrokenSize()]);
	}

	return retValue;
}

bool GameLogic::playerPatternLinesFull(Player* player) {
	bool retValue = false;
	for(int i = 0; i < wallSize && !retValue; ++i) {
		if(player->getPlayerBoard()->getPatternLine(i)->isFull()) {
			retValue = true;
		}
	}
	return retValue;
}