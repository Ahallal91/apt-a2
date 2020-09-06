#include "Factories.h"
#include "Types.h"

Factories::Factories() {
	// creates 5 factories of size 4
	this->factories = new char* [NUM_FACTORIES];
	for (int i = 0; i < NUM_FACTORIES; ++i) {
		factories[i] = new char[FACTORY_SIZE];
	}
	// creates centre factory
	this->centerFactory = new std::vector<char>;
	this->resetFactories();
}

Factories::~Factories() {
	clearFactories();
}

char* Factories::getFactory(int factoryNumber) {
	char* retValue = nullptr;
	if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
		retValue = factories[factoryNumber];
	}
	return retValue;
}

std::vector<char>* Factories::getCenterFactory() {
	return centerFactory;
}

bool Factories::addToFactory(int factoryNumber, char tile) {
	bool retValue = false;
	if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
		for (int i = 0; i < FACTORY_SIZE; ++i) {
			if (factories[factoryNumber][i] == '\0' && !retValue) {
				factories[factoryNumber][i] = tile;
				retValue = true;
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

	int count = 0;
	if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
		for (int i = 0; i < FACTORY_SIZE; ++i) {
			if (factories[factoryNumber][i] == tile) {
				retValue[count] = factories[factoryNumber][i];
				factories[factoryNumber][i] = '\0';
				count++;
			}
		}
        for (int i = 0; i < FACTORY_SIZE; ++i) {
            if (factories[factoryNumber][i] != '\0') {
				centerFactory->push_back(factories[factoryNumber][i]);
                factories[factoryNumber][i] = '\0';
			}
        }
	}
	return retValue;
}

bool Factories::addToCenterFactory(char* tiles, int numTiles) {
	bool retValue = false;
	for (int i = 0; i < numTiles; ++i) {
		centerFactory->push_back(tiles[i]);
		retValue = true;
	}
	return retValue;
}

char* Factories::takeTilesCenterFactory(char tile) {
	std::vector<char> tempTiles;
    if (centerFactory->at(0) == FIRST) {
        tempTiles.push_back(FIRST);
        centerFactory->erase(centerFactory->begin());
    }
	for (int i = 0; i < (int) centerFactory->size(); ++i) {
		if (centerFactory->at(i) == tile) {
			tempTiles.push_back(centerFactory->at(i));
			centerFactory->erase(centerFactory->begin() + i);
		}
	}

    char* retValue = new char[tempTiles.size()];
    for(int i = 0; i < (int)tempTiles.size(); ++i) {
        retValue[i] = tempTiles.at(i);
    }
	return retValue;
}

void Factories::clearFactories() {
	// Delete the 5 factories of size 4
	for (int i = 0; i < NUM_FACTORIES; i++) {
		delete[] factories[i];
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
		for (int j = 0; j < FACTORY_SIZE; ++j) {
			factories[i][j] = '\0';
		}
	}

	// clears center factory and adds first
	centerFactory->clear();
	centerFactory->push_back(FIRST);
}