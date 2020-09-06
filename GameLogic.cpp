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

bool GameLogic::takeTiles(Factories* factories, Player* player,
						  int factoryNumber, char tile, int destPatternLine) {
	bool retValue = false;
	if (playerTileCheck(player, tile, destPatternLine)) {
		char* tempTiles = takeTilesFromFactory(factories, factoryNumber, tile);
		for (int i = 0; i < FACTORY_SIZE; ++i) {
			if (!(player->getPlayerBoard()->getPatternLine(destPatternLine)->
				  addTile(tempTiles[i]))) {
				player->getPlayerBoard()->addBrokenTile(tempTiles[i]);
			}
		}
		delete tempTiles;
		tempTiles = nullptr;
		retValue = true;
	}
	return retValue;
}

char* GameLogic::takeTilesFromFactory(Factories* factories, int factoryNumber,
									  char tile) {
	char* retValue = nullptr;
	if (factoryNumber >= 1 && factoryNumber <= NUM_FACTORIES) {
		retValue = factories->takeTilesFactory(factoryNumber - 1, tile);
	} else if (factoryNumber == 0) {
		retValue = factories->takeTilesCenterFactory(tile);
	}
	if (retValue == nullptr) {
		retValue[0] = '\0';
	}
	return retValue;
}

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