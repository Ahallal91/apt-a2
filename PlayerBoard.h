#ifndef PLAYER_BOARD_H
#define PLAYER_BOARD_H

#include <vector>

class PlayerBoard {
public:
	PlayerBoard();
	~PlayerBoard();

    // WALL METHODS
	
	// Sets the tile at wall position x, y to the corresponding pattern tile
    void setWallTile(int x, int y);

	// Removes the tile at wall position x, y and sets it back to empty
	void removeWallTile(int x, int y);
    
    // Returns the tile at wall position x, y
    char getWallTile(int x, int y);


	// BROKEN LINE METHODS

	// Adds a tile to the end of the broken line if not full
	bool addBrokenTile(char tile);

	// Returns the tile at an index of the broken line
	char getBrokenTile(int index);

	// Returns the amount of tiles in the broken line
	int getBrokenSize();

	// Clears the broken tiles
	void clearBrokenLine();

private:
	// The Wall (2D 5x5 char array)
	char** wall;

	// Pattern Lines


	// Broken Line
	std::vector<char> brokenLine;

};

#endif