#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class Player;
class Output;
class Factories;

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

	Output* output;
	int currentRound;

	Player* enterPlayerName(int playerNum);

	Factories* factories;
};

#endif // GAME_MANAGER_H