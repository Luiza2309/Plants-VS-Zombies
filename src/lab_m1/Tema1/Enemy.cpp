#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(std::string bigType, std::string smallType, glm::vec2 position) {
	this->bigType = bigType;
	this->smallType = smallType;
	this->position = position;
	this->moveEnemyLeft = 1200;
	this->enemySmallerX = 1;
	this->enemySmallerY = 1;
	lifes = 3;
}

Enemy::~Enemy() {}

glm::vec2 Enemy::getPosition() {
	return position;
}

std::string Enemy::getBigType() {
	return bigType;
}

std::string Enemy::getSmallType() {
	return smallType;
}

float Enemy::getMoveEnemyLeft() {
	return moveEnemyLeft;
}

float Enemy::getEnemySmallerX() {
	return this->enemySmallerX;
}

float Enemy::getEnemySmallerY() {
	return this->enemySmallerY;
}

void Enemy::setEnemySmallerX(float value) {
	this->enemySmallerX = value;
}

void Enemy::setEnemySmallerY(float value) {
	this->enemySmallerY = value;
}

void Enemy::setMoveEnemyLeft(float value) {
	this->moveEnemyLeft = value;
}

int Enemy::getLifes() {
	return lifes;
}

void Enemy::setLifes() {
	this->lifes--;
}