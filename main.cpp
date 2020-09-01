#include <iostream>

void runMenu();
void menuText();

int main(int argc, char** argv) {
    runMenu();
    return EXIT_SUCCESS;
}

void runMenu() {
    bool exitMenu = false;
    const std::string choice1 = "1";
    const std::string choice2 = "2";
    const std::string choice3 = "3";
    const std::string choice4 = "4";
    const std::string endOfFile = "^D";

    while(!exitMenu) {
        menuText();
        std::string choice;
        std::cin >> choice;
        if(choice == choice1) {

        } else if (choice == choice2) {

        } else if (choice == choice3) {

        } else if (std::cin.eof() || 
                    choice == choice4 || 
                    choice == endOfFile) {
            exitMenu = true;
        } else {
            std::cout << "Please select a valid option" << std::endl;
        }    
    }
}

void menuText() {
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;
}