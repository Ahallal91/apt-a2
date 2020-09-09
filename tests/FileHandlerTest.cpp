#include <iostream>

#include "../FileHandler.h"

void testFileExists();
void testIsAzulGame();

int main() {
    testFileExists();
    testIsAzulGame();

    return EXIT_SUCCESS;
}

void testFileExists() {
    FileHandler* fileHandler = new FileHandler();

    std::string fileName = "main1.cpp";

    if(fileHandler->fileExists(fileName)) {
        std::cout << "Exists!" << std::endl;
    } else {
        std::cout << "Does not exist!" << std::endl;
    }

    delete fileHandler;
}

void testIsAzulGame() {
    // TODO
}