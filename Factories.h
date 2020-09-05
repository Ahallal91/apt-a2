#ifndef FACTORY_H
#define FACTORY_H
#include <vector>

class Factories {
public:
	Factories();
	~Factories();

	bool addToFactory(int factoryNumber, char tile);
	char* takeTilesFactory(int factoryNumber, char tile);

	bool addToCenterFactory(char* tile, int numTiles);
	std::vector<char> takeTilesCenterFactory(char tile);

	// clears all factories then re-initialises them 
	void resetFactories();

private:
	// deletes / clears all factories
	void clearFactories();

	// set of 5 factories of size 4
	char** factories;

	std::vector<char>* centreFactory;

};

#endif // FACTORY_H