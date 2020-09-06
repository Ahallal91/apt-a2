#include "GameLogic.h"
#include "Factories.h"
#include "TileBag.h"
#include "Types.h"

GameLogic::GameLogic() {}

GameLogic::~GameLogic() {}

// Do I need to pass by refernece
void GameLogic::addFactoryTiles(Factories* factories, TileBag* tileBag) {
	// may not even need this method call but will leave for now
	factories->resetFactories();

	// add to center
	char center[] {FIRST};
	factories->addToCenterFactory(center, 1);

	// add the tiles from the tile bag onto the factory
	for (int factoryNum = 0; factoryNum < NUM_FACTORIES; factoryNum++) {
		for (int numToAdd = 0; numToAdd < FACTORY_SIZE; numToAdd++) {
			factories->addToFactory(factoryNum, tileBag->removeFrontTile());
		}
	}
}