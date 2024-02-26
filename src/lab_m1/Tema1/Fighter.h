#pragma once

#include "components/simple_scene.h"
#include "Star.h"

class Fighter
{
public:
    Fighter();
    Fighter(std::string type, glm::vec2 position, int grid);
    ~Fighter();

    std::string getType();
    glm::vec2 getPosition();
    glm::vec2 getMoveWithMouse();
    bool getIsAlive();
    float getFighterSmallerX();
    float getFighterSmallerY();
    void setFighterSmallerX(float value);
    void setFighterSmallerY(float value);
    void setIsAlive(bool no);
    void setMoveWithMouse(glm::vec2 moveWithMouse);
    std::vector<Star*> getStars();
    void addStar(Star* star);
    void removeStar(int i);
    int getGrid();
    void setGrid(int value);
    time_t getPeriodOfTime();
    time_t getNextStar();
    void setNextStar(time_t value);
    bool getFirstStar();
    void setFirstStar(bool value);

private:
    std::string type;
    glm::vec2 position;
    glm::vec2 moveWithMouse;
    float fighterSmallerX;
    float fighterSmallerY;
    bool isAlive;
    std::vector<Star*> stars;
    bool firstStar;
    int grid;
    time_t periodOfTime;
    time_t nextStar;

protected:
};