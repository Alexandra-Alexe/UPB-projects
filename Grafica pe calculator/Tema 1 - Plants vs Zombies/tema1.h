#pragma once

#include "components/simple_scene.h"
#include "Enemy.h"
#include "Gun.h"
#include "Shot.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        float getMyLogicX(float x);
        float getMyLogicY(float y);
        void DrawEnemy(float deltaTimeSeconds,std::vector<std::vector<Enemy>> *matrix, int* lives, int rows, int cols);
        void MoveOrDisappearEnemy(Enemy *enemy, float deltaTimeSeconds);
        void CreateMeshStars(float r, float g, float b, const char *s);
        void CreateMeshGuns(float r, float g, float b, const char *s);
        void CreateMeshHexagons(float r, float g, float b, const char *s);
        void WhichGunToDrag( int *drag, float x, float y, glm::string *color, int btn, int * stars_no);
        void Drag(glm::string color, float x, float y);
        void WhichGreenSquare(float x, float y, std::vector<std::vector<Gun>> *matrix, glm::string color, int btn, int *stars_no);
        void BuildGunMatrix(std::vector<std::vector<Gun>> *matrix, int x, int y, glm::string color, int *stars_no, float ox);
        void DrawOrDisappearGun(Gun *gun, float x, float y, float deltaTimeSeconds);
        void BuildShotMatrix(Shot *shot, float x_transpose, int y_transpose, glm::string color, float x_enemy, float y_enemy);
        float getOxGun(float j);
        float getOyGun(float i);
        void MoveShot(Shot *shot, float deltaTimeSeconds);
        int CanShoot(Enemy e, Gun g);


        void DrawScene(glm::mat3 visMatrix);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
       

     protected:
        float length;
        LogicSpace logicSpace;
        glm::mat3 visMatrix;
        glm::mat3 modelMatrix;
        
        // diverse 
        int lives;

        // numar de linii si coloane ale matricei cu obiecte din clasa Enemy
        float spawnTimer_enemy, spawnInterval_enemy;
        int rows, cols, i, j;
        std::vector<std::vector<Enemy>> matrix_enemy;
        float random_line, random_color;


        // stelute - coins
        float spawnTimer_star, spawnInterval_star;
        int random_x, random_y;
        int realX_press, realY_press, realX_move, realY_move;
        int stars_no;
        struct Stele {
            int x, y;
        };
        std::vector<Stele> v_stele;

        // drag and drop
        std::vector<std::vector<Gun>> matrix_gun;
        int drag;
        glm::string color;
        float center_ox;

        // coliziuni
        int k;
        float raza_hexagon, raza_stea, raza_romb;

        // proiectile 
        float spawnInterval_shot;
        std::vector<Shot> v_shot;
        int foundIndex, index;
        int enemy_y;
        int counter;
        
    
    };
}   // namespace m1
