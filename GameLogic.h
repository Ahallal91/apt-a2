#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

class Factories;
class TileBag;

class GameLogic {
public:
	GameLogic();
	~GameLogic();
	void initFactoryTiles(Factories* factories, TileBag* tileBag);
	char* takeTilesFromFactory(Factories* factories, int factoryNumber, char tile);

private:

};

#endif // GAME_LOGIC_H