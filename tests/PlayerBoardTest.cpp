#include <iostream>

#include "../Player.h"
#include "../Types.h"

void testWall();
void testBrokenLine();

// Helper function to print the wall
void printWall(Player* player);
// Helper function to print the broken tiles
void printBrokenTiles(Player* player);

int main() {
    testWall();
    testBrokenLine();
    
    return EXIT_SUCCESS;
}

void testWall() {
    Player* player = new Player();

    printWall(player);

    player->getPlayerBoard()->setWallTile(4, 1);
    player->getPlayerBoard()->setWallTile(2, 3);
    printWall(player);

    player->getPlayerBoard()->removeWallTile(4, 1);
    printWall(player);

    delete player;
}

void testBrokenLine() {
    Player* player = new Player();

    printBrokenTiles(player);

    player->getPlayerBoard()->addBrokenTile(FIRST);
    player->getPlayerBoard()->addBrokenTile(RED);
    player->getPlayerBoard()->addBrokenTile(DARK_BLUE);
    printBrokenTiles(player);

    player->getPlayerBoard()->clearBrokenLine();
    printBrokenTiles(player);

    delete player;
}

void printWall(Player* player) {
    std::cout << "wall:" << std::endl;
    for(int y = 0; y < WALL_DIM; y++) {
        for(int x = 0; x < WALL_DIM; x++) {
            std::cout << player->getPlayerBoard()->getWallTile(x, y);
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

void printBrokenTiles(Player* player) {
    std::cout << "broken: ";
    for(int i = 0; i < player->getPlayerBoard()->getBrokenSize(); i++) {
        std::cout << player->getPlayerBoard()->getBrokenTile(i) << " ";
    }

    std::cout << std::endl;
}