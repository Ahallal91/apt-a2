#include "Factories.h"
#include "Types.h"
#include "SingleFactory.h"

Factories::Factories() {
	// creates 5 factories of size 4
	this->factories = new SingleFactory*[NUM_FACTORIES];
	for (int i = 0; i < NUM_FACTORIES; ++i) {
		factories[i] = new SingleFactory();
	}
	// creates centre factory
	this->centerFactory = new std::vector<char>;
	this->resetFactories();
}

Factories::~Factories() {
	clearFactories();
}

SingleFactory* Factories::getFactory(int factoryNumber) {
	SingleFactory* retValue = nullptr;
	if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
		retValue = factories[factoryNumber];
	}
	return retValue;
}

char Factories::getCenterFactoryTile(unsigned int index) {
	char tile = '\0';

	if (index >= 0 && index < centerFactory->size()) {
		tile = centerFactory->at(index);
	}

	return tile;
}

unsigned int Factories::getCenterFactorySize() {
	return centerFactory->size();
}

bool Factories::addToFactory(int factoryNumber, char tile) {
	bool retValue = false;
	if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
		retValue = factories[factoryNumber]->add(tile);
	}
	return retValue;
}

bool Factories::isTileInFactories(int factoryNumber, char tile) {
	bool retValue = false;
	// checks normal factories
	if (factoryNumber > 0 && factoryNumber <= NUM_FACTORIES) {
		for (int i = 0; i < FACTORY_SIZE; ++i) {
			retValue = factories[factoryNumber - 1]->contains(tile);
		}
	} else if (factoryNumber == 0) {
		// checks center factory
		std::vector<char>::iterator iter = centerFactory->begin();
		int tileAt = 0;
		while (iter != centerFactory->end() && !retValue) {
			if (centerFactory->at(tileAt) == tile) {
				retValue = true;
			} else {
				iter++;
				tileAt++;
			}
		}
	}
	return retValue;
}

char* Factories::takeTilesFactory(int factoryNumber, char tile) {
	char* retValue = new char[FACTORY_SIZE];
	for (int i = 0; i < FACTORY_SIZE; ++i) {
		retValue[i] = '\0';
	}

	// takes matching tiles from selected factory
	if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
		int tilesAdded = 0;
		for (int i = 0; i < FACTORY_SIZE; ++i) {
			if (factories[factoryNumber]->contains(tile)) {
				retValue[tilesAdded] = factories[factoryNumber]->get(tile);
				factories[factoryNumber]->remove(tile);
				tilesAdded++;
			} else {
				// add left over tiles to center factory
				if(factories[factoryNumber]->getRemaining() != '\0') {
					char toRemove = factories[factoryNumber]->getRemaining();
					factories[factoryNumber]->remove(toRemove);
					centerFactory->push_back(toRemove);
				}
			}
		}
		// resets factory.
		resetSingleFactory(factoryNumber);

	}
	return retValue;
}

std::vector<char>* Factories::takeTilesCenterFactory(char tile) {
	std::vector<char>* retValue = new std::vector<char>;

	// removes all tiles that matched.
	std::vector<char>::iterator iter = centerFactory->begin();
	int tileAt = 0;
	while (iter != centerFactory->end()) {
		if (centerFactory->at(tileAt) == tile ||
			centerFactory->at(tileAt) == FIRST) {
			retValue->push_back(centerFactory->at(tileAt));
			iter = centerFactory->erase(iter);
		} else {
			iter++;
			tileAt++;
		}
	}
	return retValue;
}

void Factories::clearFactories() {
	// Delete the 5 factories of size 4
	for (int i = 0; i < NUM_FACTORIES; i++) {
		delete factories[i];
	}
	delete[] factories;
	factories = nullptr;

	// Cleans up centre factory
	centerFactory->clear();
	delete centerFactory;
	centerFactory = nullptr;
}

void Factories::resetFactories() {
	// re-initialises factories
	for (int i = 0; i < NUM_FACTORIES; ++i) {
		resetSingleFactory(i);
	}

	// clears center factory and adds first
	centerFactory->clear();
	centerFactory->push_back(FIRST);
}

void Factories::resetSingleFactory(int factoryNumber) {
	factories[factoryNumber]->clear();
}

bool Factories::areFactoriesEmpty() {
	bool retValue = false;
	bool factoryEmpty = true;
	for (int i = 0; i < NUM_FACTORIES && factoryEmpty; i++) {
		if(!factories[i]->empty() && factoryEmpty) {
			factoryEmpty = false;
		}
	}

	if (centerFactory->empty() && factoryEmpty) {
		retValue = true;
	
	// set factories empty if just the first tile is in the center (used for new games)
	} else if (centerFactory->size() == 1 &&
	centerFactory->front() == FIRST && factoryEmpty) {
		retValue = true;
	}
	return retValue;
}

std::map<int, int> Factories::getMatchingFactories(char matchingTile) {
	std::map<int, int> retValue;
	for(int i = 0; i < NUM_FACTORIES; ++i) {
		if(!factories[i]->empty()) {
			if(factories[i]->contains(matchingTile)) {
				retValue.insert(std::pair<int, int>(i+1, 
					factories[i]->getTileCount(matchingTile)));
			}
		}
	}
	int matchingTileNumber = 0;
	if(!centerFactory->empty()) {
		for(unsigned int i = 0; i < centerFactory->size(); ++i) {
			if(centerFactory->at(i) == matchingTile) {
				matchingTileNumber++;
			}
		}
		retValue.insert(std::pair<int, int>(0, matchingTileNumber));
	}
	return retValue;
}

std::pair<int, char> Factories::getAnyMatching() {
	std::pair<int, char> retValue;
	bool picked = false;
	for(int i = 0; i < NUM_FACTORIES; ++i) {
		if(!factories[i]->empty()) {
			retValue = std::make_pair(i+1, factories[i]->getRemaining());
			picked = true;
		}
	}
	if (!centerFactory->empty() && !picked) {
		retValue = std::make_pair(0, centerFactory->front());
	}
	return retValue;
}	