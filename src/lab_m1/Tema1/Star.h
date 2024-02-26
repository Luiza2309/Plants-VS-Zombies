#pragma once

#include "components/simple_scene.h"

class Star
{
public:
    Star();
    Star(std::string type, glm::vec2 position, float moveStarRight);
    ~Star();

    std::string getType();
    glm::vec2 getPosition();
    float getMoveStarRight();
    float getProjectileRotation();
    void setMoveStarRight(float value);
    void setProjectileRotation(float value);

private:
    std::string type;
    glm::vec2 position;
    float moveStarRight;
    float projectileRotation;

protected:
};