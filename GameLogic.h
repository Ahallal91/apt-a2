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

	// Resets factories and fills them from the tilebag 
	void initFactoryTiles(Factories* factories, TileBag* tileBag);

	/*Allows the player to select tiles from a specified factory and place those
 	* tiles into their patternLine/brokenLine. Players can only place tiles in
	* PatternLines that match the tile colour or are empty.
	* Returns true if the tiles are placed in the players patternLine/brokenLine
	*/
	bool takeTiles(Factories* factories, Player* player, int factoryNumber,
				   char tile, int destPatternLine, TileBag* tileBag);

	/* returns true if all factories and center are empty, false otherwise
	 * used for checking if a round is over.
	 */
	bool roundOver(Factories* factories);

	/*
 	 * This method resets a players board and adds remaing tiles back to the tile bag.
 	 * 
 	 * The order of traversal is the top pattern line to the bottom, then the broken line.
 	 * 	At each pattern line, takes the tiles starting from index 0, which would be visually
 	 * 	right-to-left on the console. The broken line is also removed the same way, right-to-left
 	 * (starting at largest index for broken line though)
	 */
	void resetBoard(Player* player, TileBag* tileBag);

	/*
	* Moves wall tiles and calculates points
	* Also subtracts points based on number of broken tiles
	*/
	void addToWall(Player* player);

private:
	/* Takes tiles from the center factory and places them in the players
 	 * patternLine or brokenLine, tiles not added to brokenline go back to tilebag
 	 * returns true if the amount of tiles added is greater than zero.
 	 */
	bool addTilesFromCenterFact(Factories* factories, Player* player,
								int factoryNumber, char tile, int destPatternLine,
								TileBag* tileBag);

	/* Takes tiles from factory and places them in the players
	 * patternLine or brokenLine, tiles which cannot be added to the brokenLine
	 * go back to the tilebag, returns true if any tile added was not empty.
	 */
	bool addTilesFromFact(Factories* factories, Player* player, int factoryNumber,
						  char tile, int destPatternLine, TileBag* tileBag);

	/* Checks if the tile passed in matches the type of tile in the players
 	 * patternLine. If the patternLine is empty or matching it will return true
 	 * if the destination is the brokenLine it will also return true.
 	 */
	bool playerTileCheck(Player* player, char tile, int destPatternLine);

	// calculate the points of the player
	void calculatePoints(Player* player, int x, int y);

	
	/* Checks if the location on the players wall has already been filled by
	 * the tile before. Returns false if the tile location is filled.
	 */
	bool playerWallCheck(Player* player, char tile, int destPatternLine);

	/* Directly finds the location of a specific tile on the wall without
 	 * iterating over the wall itself. This is a helper method for:
 	 * bool playerWallCheck(Player* player, char tile, int destPatternLine)
 	 */
	int tileLocation(int destPatternLine, char tile);

	/*
	 * Calculates the points for 1 tile location,
	 * parameters: {start} is the start location where you want to iterate, (x or y)
	 * 			{tileLoc} is the opposite axis for the start location, (x or y)
	 * 			{sign} pass POSITIVE to iterate right or down, NEGATIVE to iterate
	 * 				left or up.
	 * 			{pointsToAdd} is where the players points are added
	 * 			{combo} checks whether the player gets combo points for row or column
	 * 			{playerboard} is the players board
	 * 			{horizontal} pass true here if you are iterating left or right. False
	 * 				for iterating up or down.
	 */
	void countTiles(int start, int tileLoc, char sign, int& pointsToAdd,
					bool& combo, PlayerBoard* playerBoard, bool horizontal);
};

#endif // GAME_LOGIC_H