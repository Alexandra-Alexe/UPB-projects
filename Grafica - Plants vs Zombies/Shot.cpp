#include "Shot.h"
#include <string.h>

using namespace std;


Shot::Shot(float x, float y, glm::string c, int row, int col, int enemy_y, float angularStep, float spawnTimer ) { 
    this->x = x;
    this->y = y;
    if(c == "romb_albastru") {  
        this->color = "stea_albastra";
    } else if (c == "romb_roz") {
        this->color = "stea_roz";
    } else if (c == "romb_galben") {
        this->color = "stea_galbena";
    } else if (c == "romb_portocaliu") {
         this->color = "stea_portocalie";
    }
    this->row = row;
    this->col = col;
    this->enemy_y = enemy_y;
    this->angular_step = angularStep;
    this->spawn_timer = spawnTimer;
}

// getteri
float Shot::getX() {
    return x;
}
float Shot::getY() {
    return y;
}
glm::string Shot::getColor() {
    return color;
}
float Shot::getAngularStep() {
    return angular_step;
}
float Shot::getSpawnTimer() {
    return spawn_timer;
}
int Shot::getRow() {
    return row;
}
int Shot::getCol() {
    return col;
}
int Shot::getEnemyY()  {
    return enemy_y;
}

// setteri
void Shot::setX(float x)
{
    this->x = x;
}
void Shot::setY(float y)
{
    this->y = y;
}
void Shot::setColor(glm::string s)
{
    this->color = s;
}
void Shot::setYEnemy(int x)
{
    this->enemy_y = x;
}
void Shot::setAngularStep(float y)
{
    this->angular_step = y;
}
void Shot::setSpawnTimer(float x)
{
    this->spawn_timer = x;
}
