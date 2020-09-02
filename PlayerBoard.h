#ifndef PLAYER_BOARD_H
#define PLAYER_BOARD_H

class PlayerBoard {
public:
	PlayerBoard();
	~PlayerBoard();

    // Sets the tile at wall position x, y to the corresponding pattern tile
    void setWallTile(int x, int y);

	// Removes the tile at wall position x, y and sets it back to empty
	void removeWallTile(int x, int y);
    
    // Returns the tile at wall position x, y
    char getWallTile(int x, int y);

private:
	// The Wall (2D 5x5 char array)
	char** wall;

	// Pattern Lines


	// Broken Line

};

#endif