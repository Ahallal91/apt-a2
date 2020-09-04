#include <iostream>

#include "../Player.h"

void testPlayer();

// Helper function to print the player details
void printPlayerDetails(Player* player);

int main() {
    testPlayer();

    return EXIT_SUCCESS;
}

void testPlayer() {
    Player* player1 = new Player();
    Player* player2 = new Player("Thomas");

    player2->setPoints(500);

    printPlayerDetails(player1);
    printPlayerDetails(player2);

    delete player1;
    delete player2;
}

void printPlayerDetails(Player* player) {
    std::cout << "Player Details:" << std::endl;
    std::cout << "name = " << player->getPlayerName() << std::endl;
    std::cout << "points = " << player->getPoints() << std::endl;
    std::cout << std::endl;
}