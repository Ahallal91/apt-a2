#include <iostream>

#define LOG(x) std::cout << x std::endl;

#include "../GameManager.h"

int main() {
    GameManager* gm = new GameManager();
    //gm->playGame();

    gm->importGame("export.txt");

    //gm->exportGame(nullptr, "export.txt");

    return 0;
}

// g++ tests\MiscTest.cpp GameManager.cpp Player.cpp PlayerBoard.cpp Input.cpp Output.cpp FileHandler.cpp PatternLine.cpp TileBag.cpp Factories.cpp GameLogic.cpp LinkedList.cpp