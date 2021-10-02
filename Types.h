#ifndef TYPES_H
#define TYPES_H

// Player Board Config
#define WALL_DIM        	5

// Tiles
#define RED					'R'
#define YELLOW         		'Y'
#define DARK_BLUE      		'B'
#define LIGHT_BLUE     		'L'
#define BLACK          		'U'

const char validTile[] = {DARK_BLUE, YELLOW, RED, BLACK, LIGHT_BLUE};

#define FIRST          		'F'
#define EMPTY           	'.'

#define TILE_BAG_SIZE		100

// The default Azul Wall Pattern
constexpr char pattern[WALL_DIM][WALL_DIM] = {
	{   DARK_BLUE,		YELLOW, 		RED, 			BLACK, 			LIGHT_BLUE	},
	{   LIGHT_BLUE, 	DARK_BLUE, 		YELLOW, 		RED, 			BLACK		},
	{   BLACK,			LIGHT_BLUE, 	DARK_BLUE, 		YELLOW, 		RED			},
	{   RED, 			BLACK, 			LIGHT_BLUE, 	DARK_BLUE,		YELLOW		},
	{   YELLOW, 		RED, 			BLACK, 			LIGHT_BLUE, 	DARK_BLUE 	}
};

// Factory Config
#define NUM_FACTORIES 		5
#define FACTORY_SIZE		 4	

// ADVANCED MODE OPTIONS

// player options
#define ADV_WALL_DIM        6

// Tiles
#define ORANGE				'O'
const char advValidTile[] = {DARK_BLUE, YELLOW, RED, BLACK, LIGHT_BLUE, ORANGE};
#define ADV_TILE_BAG_SIZE	120

// The advanced Azul Wall Pattern
constexpr char advPattern[ADV_WALL_DIM][ADV_WALL_DIM] = {
	{DARK_BLUE,		YELLOW, 		RED, 		BLACK, 			LIGHT_BLUE,	 	ORANGE},
	{ORANGE, 		DARK_BLUE,		YELLOW, 	RED, 			BLACK, 			LIGHT_BLUE},
	{LIGHT_BLUE, 	ORANGE,		 	DARK_BLUE,	YELLOW, 		RED, 			BLACK},
	{BLACK, 		LIGHT_BLUE, 	ORANGE, 	DARK_BLUE,		YELLOW, 		RED},
	{RED, 			BLACK, 			LIGHT_BLUE, ORANGE, 		DARK_BLUE,		YELLOW},
	{YELLOW, 		RED, 			BLACK, 		LIGHT_BLUE, 	ORANGE, 		DARK_BLUE}
};

#endif // TYPES_H