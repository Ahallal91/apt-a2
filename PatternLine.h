#ifndef PATTERN_H
#define PATTERN_H

class PatternLine {
public:
	PatternLine(int size);
	PatternLine(PatternLine& other);
	PatternLine(PatternLine&& other);
	~PatternLine();

	// set the tile type of this pattern line
	void setTileType(char tile);
	char getTileType();

	// Adds a tile to the end of the pattern line if not full
	bool addTile(char tile);
	
	// gets the total size of the pattern line
	int getSize();

	// gets the actual size of the pattern line
	int getCurrentSize();

	// returns the difference in size between current and expected size.
	// 0 means currentSize = size, higher numbers mean patternLine is smaller then
	// its real size.
	int sizeDifference();

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