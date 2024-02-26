#include "Fighter.h"

Fighter::Fighter() {}

Fighter::Fighter(std::string type, glm::vec2 position, int grid) {
	this->type = type;
	this->position = position;
	this->fighterSmallerX = 1;
	this->fighterSmallerY = 1;
	this->isAlive = true;
	this->grid = grid;
	this->periodOfTime = 1800;
	this->nextStar = 0;
	this->firstStar = true;
}

Fighter::~Fighter() {}

glm::vec2 Fighter::getPosition() {
	return position;
}

std::string Fighter::getType() {
	return type;
}

void Fighter::setMoveWithMouse(glm::vec2 moveWithMouse) {
	this->moveWithMouse = moveWithMouse;
}

glm::vec2 Fighter::getMoveWithMouse() {
	return moveWithMouse;
}

float Fighter::getFighterSmallerX() {
	return this->fighterSmallerX;
}

float Fighter::getFighterSmallerY() {
	return this->fighterSmallerY;
}

void Fighter::setFighterSmallerX(float value) {
	this->fighterSmallerX = value;
}

void Fighter::setFighterSmallerY(float value) {
	this->fighterSmallerY = value;
}

bool Fighter::getIsAlive() {
	return this->isAlive;
}

void Fighter::setIsAlive(bool no) {
	this->isAlive = no;
}

std::vector<Star*> Fighter::getStars() {
	return this->stars;
}

void Fighter::addStar(Star* star) {
	this->stars.push_back(star);
}

void Fighter::removeStar(int i) {
	this->stars.erase(stars.begin() + i);
}

int Fighter::getGrid() {
	return this->grid;
}

void Fighter::setGrid(int value) {
	this->grid = value;
}

time_t Fighter::getPeriodOfTime() {
	return periodOfTime;
}

time_t Fighter::getNextStar() {
	return nextStar;
}

void Fighter::setNextStar(time_t value) {
	this->nextStar = value;
}

bool Fighter::getFirstStar() {
	return firstStar;
}

void Fighter::setFirstStar(bool value) {
	firstStar = value;
}