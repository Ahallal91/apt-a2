#ifndef FACTORIES_H
#define FACTORIES_H

#include <vector>

class Factories {
public:
	Factories();
	~Factories();

	char* getFactory(int factoryNumber);
	std::vector<char>* getCenterFactory();

	bool addToFactory(int factoryNumber, char tile);
	char* takeTilesFactory(int factoryNumber, char tile);

	// returns true if the tile is in any of the factories chosen.
	bool isTileInFactories(int factoryNumber, char tile);
		
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
	std::vector<char>* centerFactory;

};

#endif // FACTORIES_H