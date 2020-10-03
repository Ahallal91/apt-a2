#include "Player.h"

Player::Player():
	Player(DEFAULT_NAME) {}


Player::Player(std::string name) :
	name(name),
	points(INITIAL_POINTS) {
	this->playerBoard = new PlayerBoard();
}

Player::~Player() {
	delete this->playerBoard;
}

std::string Player::getPlayerName() {
	return this->name;
}

// points cannot be below 0
void Player::setPoints(int points) {
	this->points = points < 0 ? 0 : points;
}

int Player::getPoints() {
	return this->points;
}

PlayerBoard* Player::getPlayerBoard() {
	return this->playerBoard;
}