#ifndef ENEMY
#define ENEMY

#include "components/simple_scene.h"
#include <string.h>


class Enemy {
private:
    float x, y, start_point;
    bool occupied;
    const char * color;
    int counter;
    float scale_start, scale;
    bool disappear;

public:
    Enemy(); 

    float getX();
    float getY();
    int getStartPoint();
    bool getOccupied();
    const char * getColor();
    int getCounter();
    float getScale();
    float getScaleStart();
    bool getDisappear();

    void setX(float x);
    void setY(float y);
    void setStartPoint(float s);
    void setOccupied(bool s);
    void setColor(const char * s);
    void setCounter(int s);
    void setScale(float s);
    void setDisappear(bool s);

};

#endif