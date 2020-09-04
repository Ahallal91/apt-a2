#ifndef PATTERN_H
#define PATTERN_H

class PatternLine {
public:
	PatternLine(int size);
	~PatternLine();

	void setTile(char tile);
	char getTile();

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