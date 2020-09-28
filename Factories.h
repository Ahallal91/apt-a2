#ifndef FACTORIES_H
#define FACTORIES_H

#include <vector>

class Factories {
public:
	Factories();
	~Factories();

	// returns a single factory by factory number. Does not return center factory
	char* getFactory(int factoryNumber);

	// returns a tile from the center factory by index
	char getCenterFactoryTile(unsigned int index);

	// returns size of the center factory
	unsigned int getCenterFactorySize();

	bool addToFactory(int factoryNumber, char tile);
	char* takeTilesFactory(int factoryNumber, char tile);

	// returns true if the tile is in any of the factories chosen.
	bool isTileInFactories(int factoryNumber, char tile);

	/* removes tiles from center factory and returns a vector of tiles that match
	 * if first tile is in center factory is it always removed.	
	 */
	std::vector<char>* takeTilesCenterFactory(char tile);

	// checks if all factories are empty and returns true if they are;
	bool areFactoriesEmpty();

	// clears all factories then re-initialises them 
	void resetFactories();

private:
	// deletes / clears all factories
	void clearFactories();

	// reset one factory.
	void resetSingleFactory(int factoryNumber);

	// set of 5 factories of size 4
	char** factories;
	
	// vector for center factory
	std::vector<char>* centerFactory;
};

#endif // FACTORIES_H