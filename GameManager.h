#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class Player;
class Output;
class Input;
class GameLogic;
class Factories;
class TileBag;

class GameManager {
public:
	GameManager();
	~GameManager();

	// main game loop
	void playGame();

private:
	Player* player1;
	Player* player2;

	GameLogic* gameLogic;
	Input* input;
	Output* output;
	Factories* factories;
	TileBag* tileBag;

	bool validateMove(Player* currentPlayer);

	int currentRound;
};

#endif // GAME_MANAGER_H