#pragma once

#include "components/simple_scene.h"

class Enemy
{
public:
    Enemy();
    Enemy(std::string bigType, std::string smallType, glm::vec2 position);
    ~Enemy();

    std::string getBigType();
    std::string getSmallType();
    glm::vec2 getPosition();
    float getMoveEnemyLeft();
    float getEnemySmallerX();
    float getEnemySmallerY();
    void setMoveEnemyLeft(float value);
    void setEnemySmallerX(float value);
    void setEnemySmallerY(float value);
    int getLifes();
    void setLifes();

private:
    std::string bigType;
    std::string smallType;
    glm::vec2 position;
    float moveEnemyLeft;
    float enemySmallerX;
    float enemySmallerY;
    int lifes;

protected:
};