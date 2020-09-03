#ifndef TYPES_H
#define TYPES_H

// Player Config
#define DEFAULT_NAME     	"Player"
#define INITIAL_POINTS   	0

// colours of the tiles
enum Colour {
	RED,
	YELLOW,
	DARK_BLUE,
	LIGHT_BLUE,
	BLACK,
	NO_COLOUR
};

// Player Board Config
#define WALL_DIM        	5

// Tiles
#define RED					'R'
#define YELLOW         		'Y'
#define DARK_BLUE      		'B'
#define LIGHT_BLUE     		'L'
#define BLACK          		'U'

#define FIRST          		'F'
#define EMPTY           	'.'

// The default Azul Wall Pattern
constexpr char pattern[WALL_DIM][WALL_DIM] = {
	{   DARK_BLUE,		YELLOW, 		RED, 			BLACK, 			LIGHT_BLUE	},
	{   LIGHT_BLUE, 	DARK_BLUE, 		YELLOW, 		RED, 			BLACK		},
	{   BLACK,			LIGHT_BLUE, 	DARK_BLUE, 		YELLOW, 		RED			},
	{   RED, 			BLACK, 			LIGHT_BLUE, 	DARK_BLUE,		YELLOW		},
	{   YELLOW, 		RED, 			BLACK, 			LIGHT_BLUE, 	DARK_BLUE 	}
};

// Broken Line config
#define NUM_BROKEN_TILES	7 

#endif // TYPES_H