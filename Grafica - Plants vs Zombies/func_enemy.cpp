#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/tema1_object2D.h"
#include "Enemy.h"

using namespace std;
using namespace m1;

void Tema1::DrawEnemy(float deltaTimeSeconds,std::vector<std::vector<Enemy>> *matrix, int *lives, int rows, int cols)
{
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            // pentru fiecare inamic ce trebuie desenat

            if((*matrix)[i][j].getOccupied() ==  true) {

                // cazul in care inamicul ajunge la banda rosie, nr de vieti scade si urm inamic isi reia poz de inceput
                if((*matrix)[i][j].getX() < - 40) {
                    *lives = *lives - 1;
                    (*matrix)[i][j].setX((*matrix)[i][j].getStartPoint());
                    (*matrix)[i][j].setOccupied(false);
                } else {
                    // altfel deplasez inamicul spre stanga
                    (*matrix)[i][j].setX((*matrix)[i][j].getX() - deltaTimeSeconds * 6);
                    (*matrix)[i][j].setY(5 - 12 * i);
                    MoveOrDisappearEnemy(&(*matrix)[i][j], deltaTimeSeconds);
                    
                }
            }
        }
    }
    
}

//  instr de desenare pt Translate() sau pentru disparitie prin scalare catre 0
void Tema1::MoveOrDisappearEnemy(Enemy *enemy, float deltaTimeSeconds) {
    if(enemy->getDisappear() == false) {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemy->getX(), enemy->getY());
        modelMatrix *= transform2D::Scale(3, 3);
        modelMatrix *= transform2D::Translate(0, 0);
        RenderMesh2D(meshes[enemy->getColor()], shaders["VertexColor"] ,modelMatrix);
    } else {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(enemy->getX(), enemy->getY()); 
        modelMatrix *= transform2D::Scale(enemy->getScale(), enemy->getScale());
        modelMatrix *= transform2D::Translate(0, 0);
        RenderMesh2D(meshes[enemy->getColor()], shaders["VertexColor"], modelMatrix);
        if(enemy->getScale() <= 0) {
            enemy->setOccupied(false);
            enemy->setDisappear(false);
            // pregatesc pozitia de inceput pt urm inamic
            enemy->setX(enemy->getStartPoint());
            // resetez counter ul
            enemy->setCounter(3);
        }

        enemy->setScale(enemy->getScale() - deltaTimeSeconds * 5);
    }
}