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
            wall[y][x] = TILE_NONE;
        }
    }

}

PlayerBoard::~PlayerBoard() {
    // Delete the 5x5 wall char array
    for(int i = 0; i < WALL_DIM; i++) {
        delete wall[i];
    }
    delete[] wall;
}

void PlayerBoard::setWallTile(char tile, int x, int y) {
    //Check that x and y are in bounds of wall
    if(x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
        wall[y][x] = tile;
    }
}

char PlayerBoard::getWallTile(int x, int y) {
    //Check that x and y are in bounds of wall
    if(x >= 0 && x < WALL_DIM && y >= 0 && y < WALL_DIM) {
        return wall[y][x];
    } else {
        return '\0';
    }
}