#include <iostream>

#include "../Player.h"
#include "../Types.h"
#include "../Input.h"

void testGameplayInput();

// Helper function to print the string vector returned after gameplay input
void printGameplayVector(std::vector<std::string> arguments);

int main() {
    testGameplayInput();
    
    return EXIT_SUCCESS;
}

void testGameplayInput() {
    Input* input = new Input();

    std::vector<std::string> arguments;

    bool done = false;
    while(!done) {
        std::cout << "> ";
        arguments = input->getGameplayInput();
        printGameplayVector(arguments);

        if(arguments[0] == "quit") {
            done = true;
        }
    }
}

void printGameplayVector(std::vector<std::string> arguments) {
    std::cout << std::endl;
    std::cout << "=== Vector Output ===" << std::endl;
    std::cout << "Arguments: " << arguments.size() << std::endl;
    std::cout << std::endl;
    for(int i = 0; i < arguments.size(); i++) {
        std::cout << i << ": " << arguments[i] << std::endl;
    }
    std::cout << std::endl;
    if(arguments.size() > 0) {
        std::cout << "Valid!" << std::endl;
    } else {
        std::cout << "Invalid!" << std::endl;
    }
}