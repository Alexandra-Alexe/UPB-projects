#ifndef GUN
#define GUN

#include "components/simple_scene.h"
#include <string.h>


class Gun {
private:
    float x, y;
    glm::string color;
    bool occupied;
    float scale_start;
    float scale;
    bool disappear;

public:
    Gun(); 

    float getX();
    float getY();
    glm::string getColor();
    bool get();
    bool getOccupied();
    float getScale();
    float getScaleStart();
    bool getDisappear();

    void setX(float x);
    void setY(float y);
    void setColor(glm::string s);
    void setOccupied(bool s);
    void setScale(float s);
    void setDisappear(bool s);
};

#endif