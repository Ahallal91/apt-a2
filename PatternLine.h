#ifndef PATTERN_H
#define PATTERN_H

class PatternLine {
public:
	PatternLine(int size);
	~PatternLine();

	void setTileType(char tile);
	char getTileType();

	// Adds a tile to the end of the pattern line if not full
	bool addTile(char tile);
	
	// Removes a tile at specific index
	// void removeTile(int index);

	int getSize();
	int getCurrentSize();

	// Checks if the pattern line is full
	bool isFull();
	// clears the patternline
	void clear();

	void clear();

private:
	// the current colour of this pattern line
	char tile;

	// size of the array
	int size;

	// current number of tiles
	int currentSize;

	// 1d array of tiles
	char* tiles;
};


#endif // PATTERN_H