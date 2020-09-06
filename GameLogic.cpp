#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
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

char* GameLogic::takeTilesFromFactory(Factories* factories, int factoryNumber, 
									char tile) {
	char* retValue = nullptr;
	if (factoryNumber >= 1 && factoryNumber <= NUM_FACTORIES) {
		retValue = factories->takeTilesFactory(factoryNumber, tile);
	} else if (factoryNumber == 0) {
		retValue = factories->takeTilesCenterFactory(tile);	
	}
	if (retValue == nullptr) {
		retValue[0] = '\0';
	}
	return retValue;
}