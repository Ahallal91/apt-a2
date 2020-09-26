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

#define NUM_TILES			5
const char validTile[] = {DARK_BLUE, YELLOW, RED, BLACK, LIGHT_BLUE};

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

<<<<<<< HEAD
=======
// amount of points lost where the index is the amount of broken line tiles
constexpr int brokenLinePoints[] = {0, -1, -2, -4, -6, -8, -11, -14};

// Misc
#define NUM_ROUNDS			 5
#define FACTORY_SIZE		 4	
#define BROKEN_LINE			 5

// Broken Line config
#define NUM_BROKEN_TILES	7 

>>>>>>> cbdafe1e13b07831b93a90bec6f4f84624aa6330
// Factory Config
#define NUM_FACTORIES 		5
#define FACTORY_SIZE		 4	

#endif // TYPES_H