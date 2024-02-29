#include "Gun.h"
#include <string.h>

using namespace std;


Gun::Gun() : x(0), y(0), scale_start(2) {}

// getteri
float Gun::getX() {
    return x;
}
float Gun::getY() {
    return y;
}
glm::string Gun::getColor() {
    return color;
}
bool Gun::getOccupied() {
    return occupied;
}
float Gun::getScale() {
    return scale;
}
float Gun::getScaleStart() {
    return scale_start;
}
bool Gun::getDisappear() {
    return disappear;
}

// setteri
void Gun::setX(float x)
{
    this->x = x;
}
void Gun::setY(float y)
{
    this->y = y;
}
void Gun::setColor(glm::string s)
{
    this->color = s;
}
void Gun::setOccupied(bool s)
{
    this->occupied = s;
}
void Gun::setScale(float s)
{
    this->scale = s;
}
void Gun::setDisappear(bool s)
{
    this->disappear = s;
}
