#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

class Factories;
class TileBag;
class Player;

class GameLogic {
public:
	GameLogic();
	~GameLogic();
	void initFactoryTiles(Factories* factories, TileBag* tileBag);
	bool takeTiles(Factories* factories, Player* player, int factoryNumber,
				   char tile, int destPatternLine);
	bool roundOver(Factories* factories);

private:
	// takes tiles that match tile passed in from factory, return array of tiles.
	char* takeTilesFromFactory(Factories* factories, int factoryNumber, char tile);

	// checks if tile matches patternLine or doesn't have tiles yet.
	bool playerTileCheck(Player* player, char tile, int destPatternLine);

	// checks if patternLine is has space for tiles.
	bool playerPatternLineSpace(Player* player, int destPatternLine);
};

#endif // GAME_LOGIC_H