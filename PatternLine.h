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
	
	// gets the total size of the pattern line
	int getSize();

	// gets the actual size of the pattern line
	int getCurrentSize();

	// Checks if the pattern line is full
	bool isFull();
	
	// clears the patternline
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