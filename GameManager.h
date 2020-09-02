#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class Player;

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
	int currentRound;
	// pass pointer to player object by reference
	void enterPlayerName(int playerNum, Player*& player);
};

#endif // GAME_MANAGER_H