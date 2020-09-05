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
    this->centreFactory = new std::vector<char>;
}

Factories::~Factories() {
    clearFactories();
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
        centreFactory->push_back(tile[i]);
        retValue = true;
    }
    return retValue;
}

std::vector<char> Factories::takeTilesCenterFactory(char tile) {
    std::vector<char> retValue;
    for(int i = 0; i < (int) centreFactory->size(); ++i) {
        if (centreFactory->at(i) == tile) {
            retValue.push_back(centreFactory->at(i));
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
    centreFactory->clear();
    delete centreFactory;
    centreFactory = nullptr;
}

void Factories::resetFactories() {
    clearFactories();
    // creates 5 factories of size 4
    factories = new char*[NUM_FACTORIES];
    for(int i = 0; i < NUM_FACTORIES; ++i) {
        factories[i] = new char[FACTORY_SIZE];
        for(int j = 0; j < FACTORY_SIZE; ++j) {
            factories[i][j] = '\0';
        }
    }

    // creates centre factory
    centreFactory = new std::vector<char>;
}