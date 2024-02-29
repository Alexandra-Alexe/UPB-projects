#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/tema1_object2D.h"
#include "Shot.h"

using namespace std;
using namespace m1;

void Tema1::MoveShot(Shot *shot, float deltaTimeSeconds) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(shot->getX() + 3, shot->getY());
    modelMatrix *= transform2D::Scale(7, 7);
    modelMatrix *= transform2D::Rotate(shot->getAngularStep());
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes[shot->getColor()], shaders["VertexColor"] ,modelMatrix);
}

int Tema1::CanShoot(Enemy e, Gun g) {
    if(e.getOccupied() && g.getOccupied() && 
    ((g.getColor().compare("romb_albastru") == 0 &&  (glm::string)e.getColor() == "hexagon_albastru") || 
    (g.getColor().compare("romb_galben") == 0 &&  (glm::string)e.getColor() == "hexagon_galben") ||
    (g.getColor().compare("romb_roz") == 0 &&  (glm::string)e.getColor() == "hexagon_roz") ||
    (g.getColor().compare("romb_portocaliu") == 0 &&  (glm::string)e.getColor() == "hexagon_portocaliu"))) {
        return 1;
    } else {
        return 0;
    }
}