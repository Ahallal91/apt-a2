#include "PlayerBoard.h"
#include "Types.h"

PlayerBoard::PlayerBoard() {
    // Create a 5x5 char array for the wall
    wall = new char*[WALL_DIM];
    for (int i = 0; i < WALL_DIM; i++) {
         wall[i] = new char[WALL_DIM];
    }

    // Initialise the 5x5 wall to empty tiles
    for(int y = 0; y < WALL_DIM; y++) {
        for(int x = 0; x < WALL_DIM; x++) {
            wall[y][x] = EMPTY;
        }
    }
}

PlayerBoard::~PlayerBoard() {
    // Delete the 5x5 wall char array
    for(int i = 0; i < WALL_DIM; i++) {
        delete wall[i];
    }
    delete[] wall;

    brokenLine.clear();
}

void PlayerBoard::setWallTile(int x, int y) {
    //Check that x and y are in bounds of wall
    if(x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
        wall[y][x] = pattern[y][x];
    }
}

void PlayerBoard::removeWallTile(int x, int y) {
    //Check that x and y are in bounds of wall
    if(x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
        wall[y][x] = EMPTY;
    }
}

char PlayerBoard::getWallTile(int x, int y) {
    char tile = '\0';
    
    //Check that x and y are in bounds of wall
    if(x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
        tile = wall[y][x];
    }

    return tile;
}

bool PlayerBoard::addBrokenTile(char tile) {
    bool success = false;
    
    if(brokenLine.size() < NUM_BROKEN_TILES) {
        brokenLine.push_back(tile);
        success = true;
    }

    return success;
}

char PlayerBoard::getBrokenTile(int index) {
    char tile = '\0';
    
    if(index >= 0 && index < NUM_BROKEN_TILES && index < brokenLine.size()) {
        tile = brokenLine[index];
    }

    return tile;
}

int PlayerBoard::getBrokenSize() {
    return brokenLine.size();
}

void PlayerBoard::clearBrokenLine() {
    brokenLine.clear();
}