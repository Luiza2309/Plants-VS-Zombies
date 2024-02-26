#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <chrono>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "lab_m1/Tema1/Fighter.h"
#include "lab_m1/Tema1/Enemy.h"
#include "lab_m1/Tema1/Star.h"

using namespace std::chrono;
using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
    grid.resize(9);
    //std::fill(grid.begin(), grid.end(), NULL);

    squareSide = 120;

    // fighter parameters
    fighterSmallDiagonal = 60;
    fighterBigDiagonal = 110;
    fighterRectangleWidth = 40;
    fighterRectangleHeight = 30;

    // enemy parameters
    enemyBigLength = 60;
    enemySmallLength = 40;

    // calculate center of fighter
    fighterCenterX = fighterSmallDiagonal / 4;
    fighterCenterY = fighterBigDiagonal / 2;

    // calculate center of enemy
    enemyCenterX = 0;
    enemyCenterY = enemyBigLength;

    // calculate center of heart
    heartCenterX = 0;
    heartCenterY = 5;

    // calculate center of star
    starCenterX = -11;
    starCenterY = -(8.0 / 3 + 5);

    // enemy rotation
    enemyRotation = 60;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    // animation parameters
    moveProjectileRight = 60;
    projectileRotation = 0;

    // functionality parameters
    positionBox1 = glm::vec2(10, 580);
    positionBox2 = glm::vec2(140, 580);
    positionBox3 = glm::vec2(270, 580);
    positionBox4 = glm::vec2(400, 580);

    choseFighter1 = false;
    choseFighter2 = false;
    choseFighter3 = false;
    choseFighter4 = false;

    selectedFighter = NULL;
    spawningEnemyTime = time(0) + (rand() % 3) + 3;
    spawningResources = time(0) + (rand() % 6) + 10;

    numberOfLifes = 3;

    radiusFighter = 55;
    radiusEnemy = 60;
    radiusStar = 20;

    numberOfResources = 10;
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    // stars rectangle parameters
    float starsRectangleWidth = 200;
    float starsRectangleHeight = 170;

    // danger rectangle parameters
    float dangerRectangleWidth = 200;
    float dangerRectangleHeight = resolution.y;

    // hit rectangle parameters
    float hitRectangleWidth = 50;
    float hitRectangleHeight = 420;

    // separator parameters
    float separatorWidth = 200;
    float separatorHeight = 10;

    // calculate center of square
    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // square for grid
    Mesh* gridSquare = object2D::CreateSquare("gridSquare", corner, squareSide, glm::vec3(0.82, 0.4, 0.553), true);
    AddMeshToList(gridSquare);


    // square for resting fighters
    Mesh* restSquare = object2D::CreateSquare("restSquare", corner, squareSide, glm::vec3(0.82, 0.4, 0.553), false);
    AddMeshToList(restSquare);


    // hit rectangle
    Mesh* hitRectangle = object2D::CreateRectangle("hitRectangle", corner, hitRectangleWidth, hitRectangleHeight, glm::vec3(0.831, 0.063, 0.345), true);
    AddMeshToList(hitRectangle);


    // danger rectangle
    Mesh* dangerRectangle = object2D::CreateRectangle("dangerRectangle", corner, dangerRectangleWidth, dangerRectangleHeight, glm::vec3(0.82, 0.4, 0.553), true);
    AddMeshToList(dangerRectangle);


    // rectangle for stars
    Mesh* starsRectangle = object2D::CreateRectangle("starsRectangle", corner, starsRectangleWidth, starsRectangleHeight, glm::vec3(0.82, 0.4, 0.553), true);
    AddMeshToList(starsRectangle);


    // strip
    Mesh* strip = object2D::CreateStrip("strip", glm::vec3(0.831, 0.063, 0.345), true);
    AddMeshToList(strip);


    // separator
    Mesh* separator = object2D::CreateRectangle("separator", corner, separatorWidth, separatorHeight, glm::vec3(0.831, 0.063, 0.345), true);
    AddMeshToList(separator);


    // first fighter
    Mesh* fighter1 = object2D::CreateFighter("fighter1", corner, fighterSmallDiagonal, fighterBigDiagonal, fighterRectangleWidth, fighterRectangleHeight, glm::vec3(0.145, 0.318, 0.388), true);
    AddMeshToList(fighter1);

    // second fighter
    Mesh* fighter2 = object2D::CreateFighter("fighter2", corner, fighterSmallDiagonal, fighterBigDiagonal, fighterRectangleWidth, fighterRectangleHeight, glm::vec3(0.612, 0.043, 0.251), true);
    AddMeshToList(fighter2);

    // third fighter
    Mesh* fighter3 = object2D::CreateFighter("fighter3", corner, fighterSmallDiagonal, fighterBigDiagonal, fighterRectangleWidth, fighterRectangleHeight, glm::vec3(0.439, 0.133, 0.357), true);
    AddMeshToList(fighter3);

    // fourth fighter
    Mesh* fighter4 = object2D::CreateFighter("fighter4", corner, fighterSmallDiagonal, fighterBigDiagonal, fighterRectangleWidth, fighterRectangleHeight, glm::vec3(0.263, 0.176, 0.451), true);
    AddMeshToList(fighter4);


    // first enemy
    Mesh* bigEnemy1 = object2D::CreateHexagon("bigEnemy1", corner, enemyBigLength, glm::vec3(0.145, 0.318, 0.388), true);
    AddMeshToList(bigEnemy1);
    Mesh* smallEnemy1 = object2D::CreateHexagon("smallEnemy1", corner, enemySmallLength, glm::vec3(0.506, 0.682, 0.749), true);
    AddMeshToList(smallEnemy1);

    // second enemy
    Mesh* bigEnemy2 = object2D::CreateHexagon("bigEnemy2", corner, enemyBigLength, glm::vec3(0.612, 0.043, 0.251), true);
    AddMeshToList(bigEnemy2);
    Mesh* smallEnemy2 = object2D::CreateHexagon("smallEnemy2", corner, enemySmallLength, glm::vec3(0.831, 0.482, 0.608), true);
    AddMeshToList(smallEnemy2);

    // third enemy
    Mesh* bigEnemy3 = object2D::CreateHexagon("bigEnemy3", corner, enemyBigLength, glm::vec3(0.439, 0.133, 0.357), true);
    AddMeshToList(bigEnemy3);
    Mesh* smallEnemy3 = object2D::CreateHexagon("smallEnemy3", corner, enemySmallLength, glm::vec3(0.71, 0.498, 0.655), true);
    AddMeshToList(smallEnemy3);

    // fourth enemy
    Mesh* bigEnemy4 = object2D::CreateHexagon("bigEnemy4", corner, enemyBigLength, glm::vec3(0.263, 0.176, 0.451), true);
    AddMeshToList(bigEnemy4);
    Mesh* smallEnemy4 = object2D::CreateHexagon("smallEnemy4", corner, enemySmallLength, glm::vec3(0.565, 0.506, 0.69), true);
    AddMeshToList(smallEnemy4);


    // star
    Mesh* star = object2D::CreateStar("star", glm::vec3(1, 1, 1), true);
    AddMeshToList(star);

    // first star
    Mesh* star1 = object2D::CreateStar("star1", glm::vec3(0.145, 0.318, 0.388), true);
    AddMeshToList(star1);

    // second star
    Mesh* star2 = object2D::CreateStar("star2", glm::vec3(0.612, 0.043, 0.251), true);
    AddMeshToList(star2);

    // third star
    Mesh* star3 = object2D::CreateStar("star3", glm::vec3(0.439, 0.133, 0.357), true);
    AddMeshToList(star3);

    // fourth star
    Mesh* star4 = object2D::CreateStar("star4", glm::vec3(0.263, 0.176, 0.451), true);
    AddMeshToList(star4);


    // heart
    Mesh* heart = object2D::CreateHeart("heart", glm::vec3(0.831, 0.063, 0.345), true);
    AddMeshToList(heart);

    // broken heart
    Mesh* brokenHeart = object2D::CreateHeart("brokenHeart", glm::vec3(0.902, 0.651, 0.741), true);
    AddMeshToList(brokenHeart);

    // danger
    Mesh* danger = object2D::CreateDanger("danger", glm::vec3(1, 1, 1), true);
    AddMeshToList(danger);


    // Create the text renderer object
    glm::ivec2 resolution = window->GetResolution();
    textRenderer = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);

    textRenderer->Load(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::FONTS, "Hack-Bold.ttf"), 72);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.682, 0.714, 0.812, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

// SCENES

void Tema1::UpperScene()
{
    // squares for resting fighters
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 580);
    RenderMesh2D(meshes["restSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(140, 580);
    RenderMesh2D(meshes["restSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(270, 580);
    RenderMesh2D(meshes["restSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 580);
    RenderMesh2D(meshes["restSquare"], shaders["VertexColor"], modelMatrix);


    // one star life
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(15 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    // two stars life
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(145 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(175 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    // two stars life
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(275 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(305 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    // three stars life
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(405 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(435 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(465 - starCenterX, 555);
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);


    // first fighter
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(60, 585);
    RenderMesh2D(meshes["fighter1"], shaders["VertexColor"], modelMatrix);

    // second fighter
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(190, 585);
    RenderMesh2D(meshes["fighter2"], shaders["VertexColor"], modelMatrix);

    // third fighter
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(320, 585);
    RenderMesh2D(meshes["fighter3"], shaders["VertexColor"], modelMatrix);

    // fourth fighter
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(450, 585);
    RenderMesh2D(meshes["fighter4"], shaders["VertexColor"], modelMatrix);


    // first heart
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 540);
    modelMatrix *= transform2D::Scale(22, 22);
    modelMatrix *= transform2D::Translate(heartCenterX, heartCenterY);
    RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

    // second heart
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(850, 540);
    modelMatrix *= transform2D::Scale(22, 22);
    modelMatrix *= transform2D::Translate(heartCenterX, heartCenterY);
    RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

    // third heart
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 540);
    modelMatrix *= transform2D::Scale(22, 22);
    modelMatrix *= transform2D::Translate(heartCenterX, heartCenterY);
    RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

    TakeLife();

    int i = numberOfResources;
    for (int star = 0; star < 5; star++) {
        for (int y = 700; y > 580; y -= 30) {
            for (int x = 1090; x < 1290; x += 40) {
                if (i > 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(x - starCenterX, y);
                    modelMatrix *= transform2D::Scale(4, 4);
                    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
                    RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
                }
                i--;
            }
        }
    }
}

void Tema1::RightScene() {
    // stars rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, 580);
    RenderMesh2D(meshes["starsRectangle"], shaders["VertexColor"], modelMatrix);


    // separator
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, 570);
    RenderMesh2D(meshes["separator"], shaders["VertexColor"], modelMatrix);


    // strips
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, 170);
    modelMatrix *= transform2D::Scale(100, 100);
    RenderMesh2D(meshes["strip"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, 0);
    modelMatrix *= transform2D::Scale(100, 100);
    RenderMesh2D(meshes["strip"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, -170);
    modelMatrix *= transform2D::Scale(100, 100);
    RenderMesh2D(meshes["strip"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, -340);
    modelMatrix *= transform2D::Scale(100, 100);
    RenderMesh2D(meshes["strip"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, 340);
    modelMatrix *= transform2D::Scale(100, 100);
    RenderMesh2D(meshes["strip"], shaders["VertexColor"], modelMatrix);


    // danger rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 200, 0);
    RenderMesh2D(meshes["dangerRectangle"], shaders["VertexColor"], modelMatrix);


    // danger
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1230, 20);
    modelMatrix *= transform2D::Rotate(RADIANS(90));
    modelMatrix *= transform2D::Scale(25, 25);
    RenderMesh2D(meshes["danger"], shaders["VertexColor"], modelMatrix);
}

void Tema1::CenterScene() {
    // hit rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 20);
    RenderMesh2D(meshes["hitRectangle"], shaders["VertexColor"], modelMatrix);


    // first row of squares
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 20);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 20);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 20);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);


    // second row of squares
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 170);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 170);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 170);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);


    // third row of squares
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 320);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(250, 320);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 320);
    RenderMesh2D(meshes["gridSquare"], shaders["VertexColor"], modelMatrix);
}

// RENDERING

void Tema1::RenderFigher(float deltaTimeSeconds) {
    int i = 0;

    for (Fighter* f : fighters) {
        if (f != NULL && f->getIsAlive()) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(f->getPosition().x + 50, f->getPosition().y + 5);
            RenderMesh2D(meshes[f->getType()], shaders["VertexColor"], modelMatrix);
        }
        else {
            DisappearingFighter(deltaTimeSeconds, f, i);
        }

        i++;
    }

    if (choseFighter1 || choseFighter2 || choseFighter3 || choseFighter4) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(selectedFighter->getMoveWithMouse().x - fighterCenterX, selectedFighter->getMoveWithMouse().y - fighterCenterY);
        RenderMesh2D(meshes[selectedFighter->getType()], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderEnemy(float deltaTimeSeconds) {
    int i = 0;
    for (Enemy* e : enemies) {
        if (e != NULL && e->getLifes() > 0) {
            MovingEnemy(deltaTimeSeconds, e, i);
        }
        else if (e->getLifes() <= 0) {
            DisappearingEnemy(deltaTimeSeconds, e, i, false); 
            i--;
        }
        i++;
    }

}

void Tema1::RenderStar(float deltaTimeSeconds) {
    for (Fighter* f : fighters) {
        if (f != NULL && f->getStars().size() > 0) {
            for (Star* s : f->getStars()) {
                if (s != NULL) {
                    StarProjectile(deltaTimeSeconds, s);
                }
            }
        }
    }
}

void Tema1::RenderResources(float deltaTimeSeconds) {
    for (Star* s : resources) {
        if (s != NULL) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(s->getPosition().x, s->getPosition().y);
            modelMatrix *= transform2D::Scale(10, 10);
            modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
            RenderMesh2D(meshes[s->getType()], shaders["VertexColor"], modelMatrix);
        }
    }
}

// ANIMATIONS

void Tema1::StarProjectile(float deltaTimeSeconds, Star* star) {
    star->setMoveStarRight(star->getMoveStarRight() + deltaTimeSeconds * 150);
    star->setProjectileRotation(star->getProjectileRotation() - deltaTimeSeconds * 5);
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(star->getMoveStarRight(), star->getPosition().y);
    modelMatrix *= transform2D::Rotate(star->getProjectileRotation());
    modelMatrix *= transform2D::Scale(4, 4);
    modelMatrix *= transform2D::Translate(starCenterX, starCenterY);
    RenderMesh2D(meshes[star->getType()], shaders["VertexColor"], modelMatrix);
}

void Tema1::MovingEnemy(float deltaTimeSeconds, Enemy* enemy, int iterator) {
    if (enemy->getMoveEnemyLeft() <= 70) {
        DisappearingEnemy(deltaTimeSeconds, enemy, iterator, true);
    } else {
        enemy->setMoveEnemyLeft(enemy->getMoveEnemyLeft() - deltaTimeSeconds * 70);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemy->getMoveEnemyLeft(), enemy->getPosition().y);
        modelMatrix *= transform2D::Rotate(enemyRotation);
        modelMatrix *= transform2D::Translate(0, -enemySmallLength);
        RenderMesh2D(meshes[enemy->getSmallType()], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemy->getMoveEnemyLeft(), enemy->getPosition().y);
        modelMatrix *= transform2D::Rotate(enemyRotation);
        modelMatrix *= transform2D::Translate(0, -enemyBigLength);
        RenderMesh2D(meshes[enemy->getBigType()], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::DisappearingFighter(float deltaTimeSeconds, Fighter* fighter, int iterator) {
    if (fighter->getFighterSmallerX() > 0 && fighter->getFighterSmallerY() > 0) {
        fighter->setFighterSmallerX(fighter->getFighterSmallerX() - deltaTimeSeconds);
        fighter->setFighterSmallerY(fighter->getFighterSmallerY() - deltaTimeSeconds);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(fighter->getPosition().x + 65, fighter->getPosition().y + 60);
        modelMatrix *= transform2D::Scale(fighter->getFighterSmallerX(), fighter->getFighterSmallerY());
        modelMatrix *= transform2D::Translate(-fighterCenterX, -fighterCenterY);
        RenderMesh2D(meshes[fighter->getType()], shaders["VertexColor"], modelMatrix);
    }
    else {
        fighters.erase(fighters.begin() + iterator);
    }

}

void Tema1::DisappearingEnemy(float deltaTimeSeconds, Enemy* enemy, int iterator, bool takeLife) {
    if (enemy->getEnemySmallerX() > 0 && enemy->getEnemySmallerY() > 0) {
        enemy->setEnemySmallerX(enemy->getEnemySmallerX() - deltaTimeSeconds);
        enemy->setEnemySmallerY(enemy->getEnemySmallerY() - deltaTimeSeconds);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemy->getMoveEnemyLeft(), enemy->getPosition().y);
        modelMatrix *= transform2D::Rotate(enemyRotation);
        modelMatrix *= transform2D::Scale(enemy->getEnemySmallerX(), enemy->getEnemySmallerY());
        modelMatrix *= transform2D::Translate(0, -enemySmallLength);
        RenderMesh2D(meshes[enemy->getSmallType()], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemy->getMoveEnemyLeft(), enemy->getPosition().y);
        modelMatrix *= transform2D::Rotate(enemyRotation);
        modelMatrix *= transform2D::Scale(enemy->getEnemySmallerX(), enemy->getEnemySmallerY());
        modelMatrix *= transform2D::Translate(0, -enemyBigLength);
        RenderMesh2D(meshes[enemy->getBigType()], shaders["VertexColor"], modelMatrix);
    } else {
        enemies.erase(enemies.begin() + iterator);
        if (takeLife) numberOfLifes--;
    }
}

// FUNCTIONALITY

void Tema1::TakeLife() {
    switch (numberOfLifes) {
    case 0:
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1000, 548);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Translate(heartCenterX, heartCenterY);
        RenderMesh2D(meshes["brokenHeart"], shaders["VertexColor"], modelMatrix);
    case 1:
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(850, 548);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Translate(heartCenterX, heartCenterY);
        RenderMesh2D(meshes["brokenHeart"], shaders["VertexColor"], modelMatrix);
    case 2:
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(700, 548);
        modelMatrix *= transform2D::Scale(20, 20);
        modelMatrix *= transform2D::Translate(heartCenterX, heartCenterY);
        RenderMesh2D(meshes["brokenHeart"], shaders["VertexColor"], modelMatrix);
    default: break;
    }
}

bool Tema1::fighterEnemyOnSameLine(int yf, int ye) {
    if (yf == 20 && ye == 80) return true;
    if (yf == 170 && ye == 230) return true;
    if (yf == 320 && ye == 380) return true;

    return false;
}

bool Tema1::SameColor(std::string f, std::string e) {
    if (f == "fighter1" && e == "bigEnemy1") return true;
    if (f == "fighter2" && e == "bigEnemy2") return true;
    if (f == "fighter3" && e == "bigEnemy3") return true;
    if (f == "fighter4" && e == "bigEnemy4") return true;

    return false;
}

void Tema1::HitFighter(float deltaTimeSeconds) {
    for (Fighter* f : fighters) {
        if (f != NULL) {
            for (Enemy* e : enemies) {
                if (e != NULL) {
                    if (glm::distance(glm::vec2(f->getPosition().x + cx, f->getPosition().y + cy), glm::vec2(e->getMoveEnemyLeft(), e->getPosition().y)) < radiusFighter + radiusEnemy) {
                        f->setIsAlive(false);
                        grid[f->getGrid()] = NULL;
                    }
                }
            }
        }
    }
}

void Tema1::HitEnemy(float deltaTimeSeconds) {
    int i = 0;
    for (Fighter* f : fighters) {
        if (f != NULL) {
            for (Enemy* e : enemies) {
                if (e != NULL) {
                    if (fighterEnemyOnSameLine(f->getPosition().y, e->getPosition().y) && SameColor(f->getType(), e->getBigType()) && e->getLifes() != 0) {
                        for (Star* s : f->getStars()) {
                            if (glm::distance(glm::vec2(s->getMoveStarRight(), s->getPosition().y), glm::vec2(e->getMoveEnemyLeft(), e->getPosition().y)) < radiusStar + radiusEnemy) {
                                f->removeStar(i);
                                e->setLifes();
                            }
                            i++;
                        }
                        i = 0;
                    }
                }
            }
        }
    }
}

string Tema1::ColoredStar(string f) {
    if (f == "fighter1") return "star1";
    if (f == "fighter2") return "star2";
    if (f == "fighter3") return "star3";
    if (f == "fighter4") return "star4";
}

void Tema1::Shoot() {
    for (Fighter* f : fighters) {
        if (f != NULL) {
            for (Enemy* e : enemies) {
                if (e != NULL) {
                    if (fighterEnemyOnSameLine(f->getPosition().y, e->getPosition().y) && SameColor(f->getType(), e->getBigType()) && e->getLifes() > 0 && e->getMoveEnemyLeft() < resolution.x - 100) {
                        // start shooting
                        uint64_t ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                        if (f->getFirstStar()) {
                            Star* star = new Star(ColoredStar(f->getType()), glm::vec2(f->getPosition().x + 5 * fighterCenterX, f->getPosition().y + fighterCenterY), f->getPosition().x + 5 * fighterCenterX);
                            f->addStar(star);
                            f->setNextStar(ms + f->getPeriodOfTime());
                            f->setFirstStar(false);
                        }
                        else if (ms >= f->getNextStar()) {
                            Star* star = new Star(ColoredStar(f->getType()), glm::vec2(f->getPosition().x + 5 * fighterCenterX, f->getPosition().y + fighterCenterY), f->getPosition().x + 5 * fighterCenterX);
                            f->addStar(star);
                            f->setNextStar(ms + f->getPeriodOfTime());
                        }
                    }
                }
            }
        }
    }
}

// RANDOM

vector<string> Tema1::RandomTypeOfEnemy(int rand) {
    vector<string> ret;
    switch (rand) {
    case 1:
        ret.push_back("bigEnemy1");
        ret.push_back("smallEnemy1");
        break;
    case 2:
        ret.push_back("bigEnemy2");
        ret.push_back("smallEnemy2");
        break;
    case 3:
        ret.push_back("bigEnemy3");
        ret.push_back("smallEnemy3");
        break;
    case 4:
        ret.push_back("bigEnemy4");
        ret.push_back("smallEnemy4");
        break;
    default: break;
    }

    return ret;
}

int Tema1::RandomLine(int rand) {
    switch (rand) {
    case 1: return 80;
    case 2: return 230;
    case 3: return 380;
    default: break;
    }
}

void Tema1::RandomTime() {
    if (time(0) == spawningEnemyTime) {
        int random = rand() % 4 + 1;
        vector<string> types = RandomTypeOfEnemy(random);
        random = rand() % 3 + 1;
        int y = RandomLine(random);

        Enemy* enemy = new Enemy(types[0], types[1], glm::vec2(resolution.x - 300, y));
        enemies.push_back(enemy);
        spawningEnemyTime = time(0) + (rand() % 3) + 3;
    }
}

void Tema1::RandomResources() {
    if (time(0) == spawningResources) {
        for (int i = 0; i < 3; i++) {
            int x = rand() % resolution.x;
            int y = rand() % resolution.y;
            Star* star = new Star("star", glm::vec2(x, y), 0);
            resources.push_back(star);
        }
        spawningResources = time(0) + (rand() % 6) + 10;
    }
}

// UPDATE

void Tema1::Update(float deltaTimeSeconds)
{
    if (numberOfLifes == 0) {
        return;
    }

    RandomResources();
    RenderResources(deltaTimeSeconds);
    RandomTime();
    HitFighter(deltaTimeSeconds);
    HitEnemy(deltaTimeSeconds);
    RightScene();
    RenderEnemy(deltaTimeSeconds);
    TakeLife();
    RenderFigher(deltaTimeSeconds);
    Shoot();
    RenderStar(deltaTimeSeconds);
    CenterScene();
    UpperScene();
}

void Tema1::FrameEnd()
{
    if (numberOfLifes <= 0) {
        glClearColor(0.82, 0.4, 0.553, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        textRenderer->RenderText("Game over </3", resolution.x / 2 - 250, resolution.y / 2 - 50, 1.0f, glm::vec3(0.831, 0.063, 0.345));
    }
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

// DRAG & DROP

void Tema1::SelectFighter(int mouseX, int y_scene) {
    // check if mouse coordonates are between resting box's coordonates

    if (mouseX > positionBox1.x && mouseX < positionBox1.x + squareSide && y_scene > positionBox1.y && y_scene < positionBox1.y + squareSide) {
        choseFighter1 = true;
        choseFighter2 = false;
        choseFighter3 = false;
        choseFighter4 = false;

        selectedFighter = new Fighter("fighter1", positionBox1, -1);
    }

    if (mouseX > positionBox2.x && mouseX < positionBox2.x + squareSide && y_scene > positionBox2.y && y_scene < positionBox2.y + squareSide) {
        choseFighter2 = true;
        choseFighter1 = false;
        choseFighter3 = false;
        choseFighter4 = false;

        selectedFighter = new Fighter("fighter2", positionBox2, -1);
    }

    if (mouseX > positionBox3.x && mouseX < positionBox3.x + squareSide && y_scene > positionBox3.y && y_scene < positionBox3.y + squareSide) {
        choseFighter3 = true;
        choseFighter2 = false;
        choseFighter1 = false;
        choseFighter4 = false;

        selectedFighter = new Fighter("fighter3", positionBox3, -1);
    }

    if (mouseX > positionBox4.x && mouseX < positionBox4.x + squareSide && y_scene > positionBox4.y && y_scene < positionBox4.y + squareSide) {
        choseFighter4 = true;
        choseFighter2 = false;
        choseFighter3 = false;
        choseFighter1 = false;

        selectedFighter = new Fighter("fighter4", positionBox4, -1);
    }
}

void Tema1::SelectGridBoxForFighter(int mouseX, int y_scene) {
    int i = 0, j = 0;
    for (int x = 100; x <= 400; x += 150) {
        for (int y = 20; y <= 320; y += 150) {
            if (mouseX > x && mouseX < x + squareSide && y_scene > y && y_scene < y + squareSide && grid[i * 3 + j] == NULL) {
                if (choseFighter1 && numberOfResources - 1 >= 0) {
                    Fighter* f = new Fighter("fighter1", glm::vec2(x, y), i * 3 + j);
                    fighters.push_back(f);
                    grid[i * 3 + j] = f;
                    numberOfResources--;
                }

                if (choseFighter2 && numberOfResources - 2 >= 0) {
                    Fighter* f = new Fighter("fighter2", glm::vec2(x, y), i * 3 + j);
                    fighters.push_back(f);
                    grid[i * 3 + j] = f;
                    numberOfResources -= 2;
                }

                if (choseFighter3 && numberOfResources - 2 >= 0) {
                    Fighter* f = new Fighter("fighter3", glm::vec2(x, y), i * 3 + j);
                    fighters.push_back(f);
                    grid[i * 3 + j] = f;
                    numberOfResources -= 2;
                }

                if (choseFighter4 && numberOfResources - 3 >= 0) {
                    Fighter* f = new Fighter("fighter4", glm::vec2(x, y), i * 3 + j);
                    fighters.push_back(f);
                    grid[i * 3 + j] = f;
                    numberOfResources -= 3;
                }
            }
            
            j++;
        }
        
        i++;
        j = 0;
    }
}

void Tema1::SelectGridBoxToDelete(int mouseX, int y_scene) {
    int i = 0, j = 0;
    for (int x = 100; x <= 400; x += 150) {
        for (int y = 20; y <= 320; y += 150) {
            if (mouseX > x && mouseX < x + squareSide && y_scene > y && y_scene < y + squareSide && grid[i * 3 + j] != NULL) {
                grid[i * 3 + j]->setIsAlive(false);
                grid[i * 3 + j] = NULL;
            }

            j++;
        }

        i++;
       j = 0;
    }
}

// CLICK RESOURCES
void Tema1::CheckResourceBorders(int mouseX, int y_scene) {
    int i = 0;
    for (Star* s : resources) {
        float x = s->getPosition().x + starCenterX;
        float y = s->getPosition().y + starCenterY;
        if (mouseX > x - 30 && mouseX < x + 30 && y_scene > y - 30 && y_scene < y + 30) {
            resources.erase(resources.begin() + i);
            if (numberOfResources < 20) numberOfResources++;
            i--;
        }
        i++;
    }
}

// MOUSE ACTIONS

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    // change mouse coordonates in scene coordonates
    int y_scene = resolution.y - mouseY;

    if (choseFighter1 || choseFighter2 || choseFighter3 || choseFighter4) {
        selectedFighter->setMoveWithMouse(glm::vec2(mouseX, y_scene));
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    
    // change mouse coordonates in scene coordonates
    int y_scene = resolution.y - mouseY;

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        // if i want to take a fighter from the resting boxes
        SelectFighter(mouseX, y_scene);
        CheckResourceBorders(mouseX, y_scene);
    }

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        SelectGridBoxToDelete(mouseX, y_scene);
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // change mouse coordonates in scene coordonates
    int y_scene = resolution.y - mouseY;

    // check where the fighter is placed
    SelectGridBoxForFighter(mouseX, y_scene);

    // Add mouse button release event
    choseFighter1 = false;
    choseFighter2 = false;
    choseFighter3 = false;
    choseFighter4 = false;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

// KEYBOARD ACTIONS

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema1::OnWindowResize(int width, int height)
{
}
