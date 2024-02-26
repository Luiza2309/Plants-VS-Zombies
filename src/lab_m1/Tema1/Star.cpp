#include "Star.h"

Star::Star() {}

Star::Star(std::string type, glm::vec2 position, float moveStarRight) {
	this->type = type;
	this->position = position;
	this->moveStarRight = moveStarRight;
	this->projectileRotation = 0;
}

Star::~Star() {}

glm::vec2 Star::getPosition() {
	return position;
}

std::string Star::getType() {
	return type;
}

float Star::getMoveStarRight() {
	return moveStarRight;
}

void Star::setMoveStarRight(float value) {
	this->moveStarRight = value;
}

float Star::getProjectileRotation() {
	return projectileRotation;
}

void Star::setProjectileRotation(float value) {
	this->projectileRotation = value;
}