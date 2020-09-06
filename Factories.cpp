#include "Factories.h"
#include "Types.h"

Factories::Factories() {
    // creates 5 factories of size 4
    this->factories = new char*[NUM_FACTORIES];
    for(int i = 0; i < NUM_FACTORIES; ++i) {
        factories[i] = new char[FACTORY_SIZE];
        for(int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = '\0';
        }
    }

    // creates centre factory
    this->centerFactory = new std::vector<char>;
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

std::vector<char> Factories::getCenterFactory() {
    return *centerFactory;
}

bool Factories::addToFactory(int factoryNumber, char tile) {
    bool retValue = false;
    if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
        for(int i = 0; i < FACTORY_SIZE; ++i) {
            if(factories[factoryNumber][i] == '\0' && !retValue) {
                factories[factoryNumber][i] = tile;
                retValue = true;
            }
        }
    }
    return retValue;
}

char* Factories::takeTilesFactory(int factoryNumber, char tile) {
    char retValue[FACTORY_SIZE] = {};
    int count = 0;
    if (factoryNumber >= 0 && factoryNumber < NUM_FACTORIES) {
        for(int i = 0; i < FACTORY_SIZE; ++i) {
            if(factories[factoryNumber][i] == tile) { 
                retValue[count] = factories[factoryNumber][i];
                factories[factoryNumber][i] = '\0';
                count++;
            }
        }
    }
    return retValue;
}

bool Factories::addToCenterFactory(char* tile, int numTiles) {
    bool retValue = false;
    for(int i = 0; i < numTiles; ++i) {
        centerFactory->push_back(tile[i]);
        retValue = true;
    }
    return retValue;
}

std::vector<char> Factories::takeTilesCenterFactory(char tile) {
    std::vector<char> retValue;
    for(int i = 0; i < (int) centerFactory->size(); ++i) {
        if (centerFactory->at(i) == tile) {
            retValue.push_back(centerFactory->at(i));
        }
    }
    return retValue;
}

void Factories::clearFactories() {
    // Delete the 5 factories of size 4
    for(int i = 0; i < NUM_FACTORIES; i++) {
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
    for(int i = 0; i < NUM_FACTORIES; ++i) {
        for(int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = '\0';
        }
    }

    // creates centre factory
    centerFactory->clear();
}
