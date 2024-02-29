#include "Enemy.h"
#include <string.h>

using namespace std;


Enemy::Enemy() : x(52), y(0), start_point(52), counter(3), scale_start(3), scale(3), disappear(false) {}

// getteri
float Enemy::getX() {
    return x;
}
float Enemy::getY() {
    return y;
}
int Enemy::getStartPoint() {
    return start_point;
}
bool Enemy::getOccupied() {
    return occupied;
}
const char * Enemy::getColor() {
    return color;
}
int Enemy::getCounter() {
    return counter;
}
float Enemy::getScale() {
    return scale;
}
float Enemy::getScaleStart() {
    return scale_start;
}
bool Enemy::getDisappear() {
    return disappear;
}


// setteri
void Enemy::setX(float x)
{
    this->x = x;
}
void Enemy::setY(float y)
{
    this->y = y;
}
void Enemy::setStartPoint(float s)
{
    this->start_point = s;
}
void Enemy::setOccupied(bool s)
{
    this->occupied = s;
}
void Enemy::setColor(const char * s)
{
    this->color = s;
}
void Enemy::setCounter(int s) {
    this->counter = s;
}
void Enemy::setScale(float s)
{
    this->scale = s;
}
void Enemy::setDisappear(bool s)
{
    this->disappear = s;
}