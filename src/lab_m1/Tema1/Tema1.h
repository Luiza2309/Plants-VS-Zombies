#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema1/Enemy.h"
#include "lab_m1/Tema1/Fighter.h"
#include "lab_m1/Tema1/Star.h"
#include "components/text_renderer.h"

#include <vector>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void UpperScene();
        void RightScene();
        void CenterScene();
        void RenderFigher(float deltaTimeSeconds);
        void SelectFighter(int mouseX, int y_scene);
        void SelectGridBoxForFighter(int mouseX, int y_scene);
        void MovingEnemy(float deltaTimeSeconds, Enemy* enemy, int iterator);
        void StarProjectile(float deltaTimeSeconds, Star* star);
        void DisappearingFighter(float deltaTimeSeconds, Fighter* fighter, int iterator);
        void DisappearingEnemy(float deltaTimeSeconds, Enemy* enemy, int iterator, bool takeLife);
        void RenderEnemy(float deltaTimeSeconds);
        std::vector<std::string> RandomTypeOfEnemy(int rand);
        int RandomLine(int rand);
        void TakeLife();
        void HitFighter(float deltaTimeSeconds);
        bool fighterEnemyOnSameLine(int yf, int ye);
        void Shoot();
        void RandomTime();
        void RenderStar(float deltaTimeSeconds);
        void HitEnemy(float deltaTimeSeconds);
        bool SameColor(std::string f, std::string e);
        void SelectGridBoxToDelete(int mouseX, int y_scene);
        std::string ColoredStar(std::string f);
        void RandomResources();
        void RenderResources(float deltaTimeSeconds);
        void CheckResourceBorders(int mouseX, int y_scene);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float squareSide;
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // fighter parameters
        float fighterSmallDiagonal;
        float fighterBigDiagonal;
        float fighterRectangleWidth;
        float fighterRectangleHeight;
        float radiusFighter;

        float starCenterX;
        float starCenterY;
        float radiusStar;

        float enemyBigLength;
        float enemySmallLength;
        float radiusEnemy;

        float enemyCenterX;
        float enemyCenterY;

        float fighterCenterX;
        float fighterCenterY;

        float heartCenterX;
        float heartCenterY;

        glm::ivec2 resolution;

        // animations
        int spawningEnemyTime;
        time_t spawningResources;
        float enemyRotation;
        float moveEnemyLeft;
        float moveProjectileRight;
        float projectileRotation;
        float fighterSmallerX;
        float fighterSmallerY;

        // functionality
        glm::vec2 positionBox1;
        glm::vec2 positionBox2;
        glm::vec2 positionBox3;
        glm::vec2 positionBox4;

        bool choseFighter1;
        bool choseFighter2;
        bool choseFighter3;
        bool choseFighter4;

        std::vector<Fighter*> grid;
        std::vector<Fighter*> fighters;
        std::vector<Enemy*> enemies;
        std::vector<Star*> resources;
        Fighter* selectedFighter;

        int numberOfLifes;
        int numberOfResources;

        // text
        gfxc::TextRenderer* textRenderer;
    };
}   // namespace m1
