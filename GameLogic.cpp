#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
#include "Player.h"
#include "Types.h"

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

// returns true if all factories and center are empty, false otherwise
// used for checking if a round is over
bool GameLogic::roundOver(Factories* factories) {
	bool roundOver = true;

	// if center factory isn't empty, then the round isn't over
	if (!factories->getCenterFactory()->empty()) {
		roundOver = false;
	}

	// check all factory tiles. If there exists a tile, the round isn't over
	for (int i = 0; i < NUM_FACTORIES && roundOver; i++) {
		char* tiles = factories->getFactory(i);
		for (int j = 0; j < FACTORY_SIZE && roundOver; j++) {
			if (tiles[j] != '\0') {
				roundOver = false;
			}
		}
	}

	return roundOver;
}

/* Allows the player to select tiles from a specified factory and place those
 * tiles into their patternLine/brokenLine. Players can only place tiles in
 * PatternLines that match the tile colour or are empty.
 * Returns true if the tiles are placed in the players patternLine/brokenLine
 */
bool GameLogic::takeTiles(Factories* factories, Player* player,
	int factoryNumber, char tile, int destPatternLine) {
	bool retValue = false;
	// reduces input patternLine by 1 to fit array
	destPatternLine--;
	// checks if tile can be placed in patternLine
	if (playerTileCheck(player, tile, destPatternLine)) {
		if(factoryNumber >= 1 && factoryNumber <= NUM_FACTORIES) {
			char* tempTiles = factories->takeTilesFactory(factoryNumber - 1, tile);
			for (int i = 0; i < FACTORY_SIZE; ++i) {
				if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)->
					addTile(tempTiles[i]))) {
					player->getPlayerBoard()->addBrokenTile(tempTiles[i]);
				}
			}
			delete tempTiles;
			tempTiles = nullptr;
			retValue = true;
		} else if (factoryNumber == 0) {
			// adds tiles from center factory to playerboard
			retValue = addTilesFromCenterFact(factories, player, factoryNumber, 
												tile, destPatternLine);
		}
	}
	return retValue;
}

/* Takes tiles from the center factory and places them in the players 
 * patternLine or brokenLine, returns true if the amount of tiles added is greater
 * than zero.
 */
bool GameLogic::addTilesFromCenterFact(Factories* factories, Player* player,
	int factoryNumber, char tile, int destPatternLine) {
	bool retValue = false;
	std::vector<char>* tempTiles = factories->takeTilesCenterFactory(tile);
	for (unsigned int i = 0; i < tempTiles->size(); ++i) {
		if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)->
			addTile(tempTiles->at(i)))) {
			player->getPlayerBoard()->addBrokenTile(tempTiles->at(i));
		}
	}
	if (tempTiles->size() > 0) {
		retValue = true;
	}
	delete tempTiles;
	tempTiles = nullptr;
	return retValue;
}

/* Checks if the tile passed in matches the type of tile in the players
 * patternLine. If the patternLine is empty or matching it will return true
 */
bool GameLogic::playerTileCheck(Player* player, char tile, int destPatternLine) {
	bool retValue = false;
	char tileType = player->
		getPlayerBoard()->
		getPatternLine(destPatternLine)->
		getTileType();
	if (tileType == EMPTY || tileType == tile) {
		retValue = true;
	}
	return retValue;
}