#include "Player.h"

Player::Player():
	Player(DEFAULT_NAME) {}

Player::Player(Player& other) {
	this->name = other.name;
	this->points = other.points;
	this->playerBoard = other.playerBoard;
}

Player::Player(Player&& other) {
	this->name = other.name;
	this->points = other.points;
	this->playerBoard = other.playerBoard;
}

Player::Player(std::string name) :
	name(name),
	points(INITIAL_POINTS) {
	this->playerBoard = new PlayerBoard();
}

Player::Player(std::string name, bool advancedMode, bool greyBoard) :
	name(name),
	points(INITIAL_POINTS) {
	this->playerBoard = new PlayerBoard(advancedMode, greyBoard);
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