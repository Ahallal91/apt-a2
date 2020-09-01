#include <iostream>

void menu();

int main(int argc, char** argv) {
    bool exitLoop = false;
    while(!exitLoop) {
        menu();
        std::string choice;
        std::cin >> choice;
        if(choice == "1") {

        } else if (choice == "2") {

        } else if (choice == "3") {

        } else if (std::cin.eof() || 
                    choice == "4" || 
                    choice == "^D") {
            exitLoop = true;
        } else {
            std::cout << "Please select a valid option" << std::endl;
        }    
    }
    return EXIT_SUCCESS;
}


void menu() {
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