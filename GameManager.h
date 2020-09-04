#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class Player;
class Output;
class Input;
class GameLogic;

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
	int currentRound;

	Player* enterPlayerName(int playerNum);
};

#endif // GAME_MANAGER_H