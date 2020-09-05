#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

class Factories;
class TileBag;

class GameLogic {
public:
	GameLogic();
	~GameLogic();
	void addFactoryTiles(Factories* factories, TileBag* tileBag);

private:

};

#endif // GAME_LOGIC_H