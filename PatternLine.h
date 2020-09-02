#ifndef PATTERN_H
#define PATTERN_H

// colours of the tiles
enum Colour {
	RED,
	YELLOW,
	DARK_BLUE,
	LIGHT_BLUE,
	BLACK,
	NO_COLOUR
};

class PatternLine {
public:
	PatternLine(int size);
	~PatternLine();

	void setColour(Colour colour);
	Colour getColour();

private:
	// colour of this pattern line
	Colour colour;

	// size of the array
	int size;

	// 1d array of tiles
	char* tiles;
};


#endif // PATTERN_H