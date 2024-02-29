#ifndef SHOT
#define SHOT

#include "components/simple_scene.h"
#include <string.h>


class Shot {
private:
    float x, y, angular_step;
    int row, col, enemy_y;
    glm::string color;
    float spawn_timer;


public:
    Shot(float x, float y, glm::string c, int row, int col, int enemy_y, float angularStep, float spawnTimer); 

    float getX();
    float getY();
    glm::string getColor();
    float getAngularStep();
    float getSpawnTimer();
    int getRow();
    int getCol();
    int getEnemyY();


    void setX(float x);
    void setY(float y);
    void setColor(glm::string s);
    void setAngularStep(float y);
    void setSpawnTimer(float x);
    void setYEnemy(int x);
};

#endif