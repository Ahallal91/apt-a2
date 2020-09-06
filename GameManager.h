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

	Player* getPlayer1();
	Player* getPlayer2();

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

	int currentRound;
};

#endif // GAME_MANAGER_H