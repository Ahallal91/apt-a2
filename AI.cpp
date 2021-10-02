
#include "AI.h"
#include "Player.h"
#include "PatternLine.h"
#include "Factories.h"
#include "Types.h"
#include <iostream>
#define TURN_COMMAND "turn "
#define EMPTY_SPACE_RETURN " "

AI::AI() {
    this->player = player;
    this->factoryChoice = -1;
    this->patternChoice = -1;
    this->tileChoice = '\0';
    this->wallSize = WALL_DIM;
}

AI::AI(AI& other) {
    this->player = other.player;
    this->factoryChoice = other.factoryChoice;
    this->patternChoice = other.patternChoice;
    this->tileChoice = other.tileChoice;
    this->wallSize = other.wallSize;
}

AI::AI(AI&& other) {
    this->player = other.player;
    this->factoryChoice = other.factoryChoice;
    this->patternChoice = other.patternChoice;
    this->tileChoice = other.tileChoice;
    this->wallSize = other.wallSize;
}

AI::~AI() {
    delete player;
}
void AI::setPlayer(Player* player) {
    this->player = player;
}
std::string AI::makeMove() {
    return  TURN_COMMAND +
            std::to_string(factoryChoice) +
            EMPTY_SPACE_RETURN + 
            tileChoice +
            EMPTY_SPACE_RETURN +
            std::to_string(patternChoice);
}

void AI::calculateTurn(Factories* factories) {
    char tileType = '\0';
    bool factoryPicked = false;
    // gets smallest available pattern line and the tile type.
    std::map<int, int> patternLines = player->getPlayerBoard()->getAvailablePatternLines();
    std::pair<int, int> min = minLine(patternLines); 
    findTileType(min, patternLines, tileType);
    int wallCount = 0;
    while(!factoryPicked) {
        std::map<int, int> fact = factories->getMatchingFactories(tileType);
        std::pair<int, int> chosenFact = minFact(fact, min);
        // check to make sure tile is in factory
        if(factories->isTileInFactories(chosenFact.first, tileType)) {
            factoryChoice = chosenFact.first;
            factoryPicked = true;
            tileChoice = tileType;
            // increment patternline by 1 to adjust for real input number.
            patternChoice = min.first + 1;
         }
        
        if(!factoryPicked) {
            // if tile was not in factory chosen, delete current pattern line, find new minimum
            if(patternLines.size() >= 2) {
                erasePreviousPatternLine(min, patternLines);
                findTileType(min, patternLines, tileType);
            } else if (patternLines.size() == 1 && wallCount < wallSize && 
                player->getPlayerBoard()->getPatternLine(min.first)->getTileType() == EMPTY) {
                // if there is only 1 pattern line left and it's tileType is EMPTY find a new tileType from the wall.
                std::tuple<int, int, char> wall = player->getPlayerBoard()->getWallCombo(min.first, wallCount);
                tileType = std::get<2>(wall);
                wallCount++;
            } else if (wallCount >= wallSize || player->getPlayerBoard()->
                getPatternLine(min.first)->getTileType() != EMPTY) {
                // If there is no tiles to pick, take any tile and put it on the broken line.
                patternChoice = wallSize + 1;
                std::pair<int, int> remainingFact = factories->getAnyMatching();
                factoryChoice = remainingFact.first;
                tileChoice = remainingFact.second;
                factoryPicked = true;
            }
        }
    }
}

std::pair<int, int> AI::minLine(std::map<int, int>& patternLine) {
    std::pair<int, int> min;
    int minimumValue = wallSize+1;
    for (std::pair<int, int> element : patternLine) {
        if(element.second < minimumValue) {
            min = std::make_pair(element.first, element.second);
            minimumValue = element.second;
        }
    }
    return min;
}

std::pair<int, int> AI::minFact(std::map<int, int>& fact, std::pair<int, int> min) {
    std::pair<int, int> minValue;
    int previous = FACTORY_SIZE;
    for (std::pair<int, int> element : fact) {
        if(std::abs(min.second - element.second) < previous) {
            minValue = std::make_pair(element.first, element.second);
            previous = min.second - element.second;
        }
    }
    return minValue;
}

void AI::findTileType(std::pair<int, int>& min, std::map<int, int>& patternLines,
                        char& tileType) {

    tileType = player->getPlayerBoard()->getPatternLine(min.first)->getTileType();
    if (tileType == EMPTY || tileType == '\0') {
        std::tuple<int, int, char> wall = player->getPlayerBoard()->getWallCombo(min.first, -1);
        tileType = std::get<2>(wall);
    }
}

void AI::erasePreviousPatternLine(std::pair<int, int>& min, std::map<int, int>& patternLines) {
    for(auto it = patternLines.begin(); it != patternLines.end(); ) {
        if (it->first == min.first) {
            it = patternLines.erase(it);  
        } else {
            ++it;
        }
    }
    min = minLine(patternLines);
}