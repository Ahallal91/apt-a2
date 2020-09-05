#include <iostream>

#include "../Player.h"
#include "../Types.h"
#include "../Output.h"

void testBoardOutput();

int main() {
    testBoardOutput();
    
    return EXIT_SUCCESS;
}

void testBoardOutput() {
    Player* player = new Player("Mark");
    Output* output = new Output();

    output->outputBoard(player);

    // wall output
    player->getPlayerBoard()->setWallTile(1, 1);
    player->getPlayerBoard()->setWallTile(2, 1);
    player->getPlayerBoard()->setWallTile(3, 1);
    player->getPlayerBoard()->setWallTile(3, 2);
    player->getPlayerBoard()->setWallTile(3, 3);

    // pattern lines output
    player->getPlayerBoard()->getPatternLine(1)->addTile(RED);
    player->getPlayerBoard()->getPatternLine(3)->addTile(DARK_BLUE);
    player->getPlayerBoard()->getPatternLine(3)->addTile(BLACK);

    // broken line output
    player->getPlayerBoard()->addBrokenTile(FIRST);
    player->getPlayerBoard()->addBrokenTile(RED);
    player->getPlayerBoard()->addBrokenTile(LIGHT_BLUE);

    output->outputBoard(player);

    // Modify the board
    player->getPlayerBoard()->removeWallTile(1, 1);
    player->getPlayerBoard()->removeWallTile(2, 1);
    player->getPlayerBoard()->setWallTile(3, 4);
    player->getPlayerBoard()->setWallTile(4, 4);

    player->getPlayerBoard()->getPatternLine(1)->removeTile(0);
    player->getPlayerBoard()->getPatternLine(3)->removeTile(1);
    player->getPlayerBoard()->getPatternLine(0)->addTile(LIGHT_BLUE);
    player->getPlayerBoard()->getPatternLine(2)->addTile(YELLOW);

    player->getPlayerBoard()->addBrokenTile(YELLOW);
    player->getPlayerBoard()->addBrokenTile(BLACK);

    output->outputBoard(player);

    delete output;
    delete player;
}