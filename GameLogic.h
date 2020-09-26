#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

class Factories;
class TileBag;
class Player;
class Input;
class Output;
class PlayerBoard;

class GameLogic {
public:
	GameLogic();
	~GameLogic();

	void initFactoryTiles(Factories* factories, TileBag* tileBag);
	bool takeTiles(Factories* factories, Player* player, int factoryNumber,
				   char tile, int destPatternLine, TileBag* tileBag);
	bool roundOver(Factories* factories);
	void resetBoard(Player* player, TileBag* tileBag);
	void addToWall(Player* player);

private:
	// takes tiles that match tile passed in from Center factory, return true if tiles
	// were added to player board.
	bool addTilesFromCenterFact(Factories* factories, Player* player,
								int factoryNumber, char tile, int destPatternLine,
								TileBag* tileBag);

	// takes tiles that match tile passed in from factory, return true if tiles
	// were added to player board.
	bool addTilesFromFact(Factories* factories, Player* player, int factoryNumber,
						  char tile, int destPatternLine, TileBag* tileBag);

	// checks if tile matches patternLine or doesn't have tiles yet.
	bool playerTileCheck(Player* player, char tile, int destPatternLine);

	// calculate the points of the player
	void calculatePoints(Player* player, int x, int y);

	// checks if tile being placed on line is already in wall
	bool playerWallCheck(Player* player, char tile, int destPatternLine);

	// gets the horizontal location of the tile on the wall
	int tileLocation(int destPatternLine, char tile);

	/*
Calculates the points for 1 tile location,
parameters: {start} is the start location where you want to iterate, (x or y)
			{tileLoc} is the opposite axis for the start location, (x or y)
			{sign} pass POSITIVE to iterate right or down, NEGATIVE to iterate
				left or up.
			{pointsToAdd} is where the players points are added
			{combo} checks whether the player gets combo points for row or column
			{playerboard} is the players board
			{horizontal} pass true here if you are iterating left or right. False
				for iterating up or down.
*/
	void countTiles(int start, int tileLoc, char sign, int& pointsToAdd,
					bool& combo, PlayerBoard* playerBoard, bool horizontal);
};

#endif // GAME_LOGIC_H