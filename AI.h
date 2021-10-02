#ifndef AI_H
#define AI_H

#include <string>
#include <map>
#include <tuple>

class Player;
class Factories;
class PatternLine;
class AI {
public:
    AI();
    // copy constructor
    AI(AI& other);
    // move constructor
    AI(AI&& other);
    ~AI();

    // sets the player type of the AI;
    void setPlayer(Player* player);

    /* Returns a string of the AI's move.
	*/
    std::string makeMove();
    /* Calculates the turn for the AI using the available factories,
     * the player's patternline and their wall.
	*/
    void calculateTurn(Factories* factories);

private:
    /* This method finds the minimum distance line out of all the 
     * available pattern and returns a pair of the pattern line number
     * and the amount of tiles it can be filled by.
	*/
    std::pair<int, int> minLine(std::map<int, int>& patternLine);

    /* This method passes in the patternLines and minimum line to set the
     * tileType to check for. If the pattern line is empty it searches the
     * wall for a valid tile, it tries to aim for combo points.
	*/
    void findTileType(std::pair<int, int>& min, std::map<int, int>& patternLines,
                        char& tileType);
    /* This Method returns the factory which has matching tiles for the chosen
     * pattern line and also is the closest matching in tiles, for example
     * a pattern line of size 4 will try to get a factory with 4 tiles.
	*/
    std::pair<int, int> minFact(std::map<int, int>& fact, std::pair<int, int> min);

    /* This method erases the previous minimum pattern line and sets a new minimum.
	*/
    void erasePreviousPatternLine(std::pair<int, int>& min, std::map<int, int>& patternLines);

    Player* player;
    int wallSize;
    std::string moveType;
    int factoryChoice;
    int patternChoice;
    char tileChoice;
};

#endif // AI_H
