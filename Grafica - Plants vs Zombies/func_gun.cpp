#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/tema1_object2D.h"
#include "Gun.h"

using namespace std;
using namespace m1;

// la press
void Tema1::WhichGunToDrag( int *drag, float x, float y, glm::string *color, int btn, int *stars_no) {
    if(y > 20 && y < 28 && btn == 1) {

        if(x > -40 && x < -33 && *stars_no >= 1 ) {
            *color = "romb_albastru";
            *drag = 1;
        } else if(x > -27 && x < -20 && *stars_no >= 2) {
            *color = "romb_roz";
            *drag = 1;
        } else if(x > -15 && x < -8 && *stars_no >= 2) {
            *color = "romb_galben";
            *drag = 1;
        } else if(x > -2 && x < 5 && *stars_no >= 3){
            *color = "romb_portocaliu";
            *drag = 1;
        }
    }
}

// apleata in update
void Tema1::Drag(glm::string color, float x, float y) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x,  y); 
    modelMatrix *= transform2D::Scale(2, 2);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes[color], shaders["VertexColor"], modelMatrix);
}

// la drop
void Tema1::WhichGreenSquare(float x, float y, std::vector<std::vector<Gun>> *matrix, glm::string color, int btn, int *stars_no) {

        // stg jos
        if(x > -42.5 && x < -32.5 && y > -25 && y < -15) {
            // daca arma exista si s-a dat click dreapta -> scalare la 0
            if(btn == 2) {
                (*matrix)[2][0].setDisappear(true);
            } else if((*matrix)[2][0].getOccupied() == false) {

                // altfel, arma nu exista si o cream acum in matrice
                center_ox = (- 42.5 - 32.5) / 2.0;
                BuildGunMatrix(matrix, 2, 0, color, stars_no, center_ox);
            }
        } 
        // stg mij
        if(x > -42.5 && x < -32.5 && y > -12.5 && y < -2.5) {
            if(btn == 2) {
                (*matrix)[1][0].setDisappear(true);
            } else if((*matrix)[1][0].getOccupied() == false) {
                center_ox = (- 42.5 - 32.5) / 2.0;
                BuildGunMatrix(matrix, 1, 0, color, stars_no, center_ox);
            }
        }
        // stg sus
        if(x > -42.5 && x < -32.5 && y > 0 && y < 10) {
            if(btn == 2) {
                (*matrix)[0][0].setDisappear(true);
            } else if((*matrix)[0][0].getOccupied() == false)  {
                center_ox = (- 42.5 - 32.5) / 2.0;
                BuildGunMatrix(matrix, 0, 0, color, stars_no, center_ox);
            }
        } 
        // centru jos
        if(x > -30 && x < -20 && y > -25 && y < -15) {
            if(btn == 2) {
                (*matrix)[2][1].setDisappear(true);
            } else if((*matrix)[2][1].getOccupied() == false)  {
                center_ox = (- 30 - 20) / 2.0;
                BuildGunMatrix(matrix, 2, 1, color, stars_no, center_ox);
            }
        } 
        // centru mij
        if(x > -30 && x < -20 && y > -12.5 && y < -2.5) {
            if(btn == 2) {
                (*matrix)[1][1].setDisappear(true);
            } else if((*matrix)[1][1].getOccupied() == false) {
                center_ox = (- 30 - 20) / 2.0;
                BuildGunMatrix(matrix, 1, 1, color, stars_no, center_ox);
            }
        } 
        // centru sus
        if(x > -30 && x < -20 && y > 0 && y < 10) {
            if(btn == 2) {
                (*matrix)[0][1].setDisappear(true);
            } else if((*matrix)[0][1].getOccupied() == false) {
                center_ox = (- 30 - 20) / 2.0;
                BuildGunMatrix(matrix, 0, 1, color, stars_no, center_ox);
            }
        } 
        // dr jos
        if(x > -17.5 && x < -7.5 && y > - 25 && y < -15) {
            if(btn == 2) {
                (*matrix)[2][2].setDisappear(true);
            } else if((*matrix)[2][2].getOccupied() == false) {
                center_ox = (- 17.5 - 7.5) / 2.0;
                BuildGunMatrix(matrix, 2, 2, color, stars_no, center_ox);
            }
        } 
        // dr mij
        if(x > -17.5 && x < -7.5 && y > -12.5 && y < -2.5) {
            if(btn == 2) {
                (*matrix)[1][2].setDisappear(true);
            } else if((*matrix)[1][2].getOccupied() == false) {
                center_ox = (- 17.5 - 7.5) / 2.0;
                BuildGunMatrix(matrix, 1, 2, color, stars_no, center_ox);
            }
        }
        // dr sus
        if(x > -17.5 && x < -7.5 && y > 0 && y < 10) {
            if(btn == 2) {
                (*matrix)[0][2].setDisappear(true);
            } else if((*matrix)[0][2].getOccupied() == false) {
                center_ox = (- 17.5 - 7.5) / 2.0;
                BuildGunMatrix(matrix, 0, 2, color, stars_no, center_ox);
            } else if ((*matrix)[0][2].getOccupied() == true) {
            }
        }
}

// fol la release pentru a construi matricea
void Tema1::BuildGunMatrix(std::vector<std::vector<Gun>> *matrix, int x, int y, glm::string color, int *stars_no, float ox) {
    if((*matrix)[x][y].getOccupied() == false) {
        (*matrix)[x][y].setOccupied(true);
        (*matrix)[x][y].setColor(color);
        (*matrix)[x][y].setScale((*matrix)[x][y].getScaleStart());
        (*matrix)[x][y].setX(ox);
        (*matrix)[x][y].setDisappear(false);

        // decrementez nr de stelute in mom plasarii
        if( color == "romb_albastru") {
            *stars_no -= 1;
        } else if(color == "romb_roz" || color == "romb_galben") {
            *stars_no -= 2;
        } else {
            *stars_no -= 3;
        }
    }
}

// afisarea armelor plasate - in update
void Tema1::DrawOrDisappearGun(Gun *gun, float x, float y, float deltaTimeSeconds) {
    if(gun->getDisappear() == false) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y); 
        modelMatrix *= transform2D::Scale(gun->getScaleStart(), gun->getScaleStart());
        modelMatrix *= transform2D::Translate(0, 0);
        RenderMesh2D(meshes[gun->getColor()], shaders["VertexColor"], modelMatrix);
    } else {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(x, y); 
        modelMatrix *= transform2D::Scale(gun->getScale(), gun->getScale());
        modelMatrix *= transform2D::Translate(0, 0);
        RenderMesh2D(meshes[gun->getColor()], shaders["VertexColor"], modelMatrix);
        if(gun->getScale() <= 0) {
            gun->setOccupied(false);
            gun->setDisappear(false);
        }

        gun->setScale(gun->getScale() - deltaTimeSeconds * 5);
    }
    
}