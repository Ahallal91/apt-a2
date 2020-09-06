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

private:
	char* takeTilesFromFactory(Factories* factories, int factoryNumber, char tile);
	bool playerTileCheck(Player* player, char tile, int destPatternLine);
};

#endif // GAME_LOGIC_H