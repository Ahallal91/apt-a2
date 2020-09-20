#include <iostream>

#include "../GameManager.h"
#include "../GameState.h"

int main() {
    GameManager gm;

    GameState* gs;

    gs = gm.importGame("ttt.azul");

    if(gs != nullptr) {
        std:: cout << "GAME IS GOOD!" << std::endl;
        gm.playGame(gs);
    }
    
    return 0;
}