#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/tema1_object2D.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // variabile diverse
    lives = 3;
    spawnTimer_star = 0;
    spawnInterval_star = 8;
    // consider ca jocul ofera la inceput 5 stelute
    stars_no = 5; 


    // implementari initiale inamici
    rows = 3;
    cols = 3;
    spawnTimer_enemy = 0;
    spawnInterval_enemy = 4;
    matrix_enemy.resize(rows, std::vector<Enemy>(cols));
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            // setez câmpul 'occupied' pe 'false' pentru ca initial nu vreau sa apara niciun inamic
            matrix_enemy[i][j] = Enemy();
            matrix_enemy[i][j].setOccupied(false); 
        }
    }

    // coliziuni
    raza_hexagon = 2.5;
    raza_romb = 3.5;
    raza_stea = 3.5;

    // implementari initiale drag & drop
    matrix_gun.resize(rows, std::vector<Gun>(cols));
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            // setez câmpul 'occupied' pe 'false' pentru ca initial nu s-a facut niciun drag
            matrix_gun[i][j] = Gun();
            matrix_gun[i][j].setOccupied(false);
            matrix_gun[i][j].setDisappear(false);
            matrix_gun[i][j].setColor("null");
        }
    }
    drag = 0;
     
    // implementari proiectile
    spawnInterval_shot = 2;


    // dreptunghi
    {
        vector<VertexFormat> vertices_dreptunghi
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0.5f, 3.5f, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 3.5f, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6))
        };
        vector<unsigned int> indices_dreptunghi =
        {
            0, 2, 3,   
            0, 1, 2,  
        };
        CreateMesh("dreptunghi", vertices_dreptunghi, indices_dreptunghi);
    }

    // patrat verde
    {
        vector<VertexFormat> vertices_patrat_v
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0.5), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0.5), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 0.5), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0.5), glm::vec3(0.2, 0.8, 0.6))

        };
        vector<unsigned int> indices_patrat_v
        {
            0, 2, 3,    
            0, 1, 2,   

        };
        CreateMesh("patrat_verde", vertices_patrat_v, indices_patrat_v);
    }

    // inimi rosii (vieti)
    {
        vector<VertexFormat> vertices_inima
        {
            VertexFormat(glm::vec3(0, -5, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)), //A 0
            VertexFormat(glm::vec3(-4, -1, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)),//B 1
            VertexFormat(glm::vec3(-4, 1, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)), //C 2
            VertexFormat(glm::vec3(-2, 2, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)), //G 3
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)), //D 4
            VertexFormat(glm::vec3(2, 2, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)), // H 5
            VertexFormat(glm::vec3(4, 1, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)), // E 6
            VertexFormat(glm::vec3(4, -1, 0), glm::vec3(1, 0.1, 0), glm::vec3(0.2, 0.8, 0.6)) //F 7
        };
        vector<unsigned int> indices_inima
        {
            0, 2, 1,
            0, 3, 2,
            0, 4, 3,
            0, 5, 4,
            0, 6, 5,
            0, 7, 6
        };
        CreateMesh("patrat_rosu", vertices_inima, indices_inima);
    }

    // stele
    CreateMeshStars(0.659f, 0, 0.541f, "steluta");
    CreateMeshStars(0, 0.6, 1, "stea_albastra");
    CreateMeshStars(1, 0.5, 0, "stea_portocalie");
    CreateMeshStars(0.9, 0.745, 0.98, "stea_roz");
    CreateMeshStars(1, 0.8, 0, "stea_galbena");

    // romburi
    CreateMeshGuns(0, 0.6, 1, "romb_albastru"); 
    CreateMeshGuns(1, 0.5, 0, "romb_portocaliu");
    CreateMeshGuns(0.9, 0.745, 0.98, "romb_roz");
    CreateMeshGuns(1, 0.8, 0, "romb_galben");

    // hexagoane 
    CreateMeshHexagons(0, 0.6, 1, "hexagon_albastru");
    CreateMeshHexagons(1, 0.5, 0, "hexagon_portocaliu");
    CreateMeshHexagons(0.9, 0.745, 0.98, "hexagon_roz");
    CreateMeshHexagons(1, 0.8, 0, "hexagon_galben");

    // patrate - cadrane
    glm::vec3 corner1 = glm::vec3(-42.5f, 17.5f, 0);
    glm::vec3 corner2 = glm::vec3(-30, 17.5f, 0);
    glm::vec3 corner3 = glm::vec3(-17.5f, 17.5f, 0);
    glm::vec3 corner4 = glm::vec3(-5, 17.5f, 0);
    float squareSide = 10;
    Mesh* square1 = tema1_object2D::CreateSquare("square1", corner1, squareSide, glm::vec3(0, 0, 0));
    Mesh* square2 = tema1_object2D::CreateSquare("square2", corner2, squareSide, glm::vec3(0, 0, 0));
    Mesh* square3 = tema1_object2D::CreateSquare("square3", corner3, squareSide, glm::vec3(0, 0, 0));
    Mesh* square4 = tema1_object2D::CreateSquare("square4", corner4, squareSide, glm::vec3(0, 0, 0));
    AddMeshToList(square1);
    AddMeshToList(square2);
    AddMeshToList(square3);
    AddMeshToList(square4);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.764f, 0.729f, 0.666f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution(); 

    // patrate verzi
    RenderMesh(meshes["dreptunghi"], shaders["VertexColor"], glm::vec3(-50, -25, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-42.5f, -25, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-42.5f, -12.5f, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-42.5f, 0, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-30, -25, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-30, -12.5f, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-30, 0, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-17.5f, -25, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-17.5f, -12.5f, 0), glm::vec3(10));
    RenderMesh(meshes["patrat_verde"], shaders["VertexColor"], glm::vec3(-17.5f, 0, 0), glm::vec3(10));

    // patrate rosii (vieti)
    if (lives > 2) {
        RenderMesh(meshes["patrat_rosu"], shaders["VertexColor"], glm::vec3(35, 25, 0));
    } 
    if( lives > 1) {
        RenderMesh(meshes["patrat_rosu"], shaders["VertexColor"], glm::vec3(25, 25, 0));
    }
    if(lives > 0) {
        RenderMesh(meshes["patrat_rosu"], shaders["VertexColor"], glm::vec3(15, 25, 0));
    }
    if(lives == 0) {
        Exit();
    }
    
    // cadrane
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

    // arme
    RenderMesh(meshes["romb_albastru"], shaders["VertexColor"], glm::vec3(-38, 22, 0), glm::vec3(2));
    RenderMesh(meshes["romb_portocaliu"], shaders["VertexColor"], glm::vec3(-1.5, 22, 0), glm::vec3(2));
    RenderMesh(meshes["romb_galben"], shaders["VertexColor"], glm::vec3(-13.5, 22, 0), glm::vec3(2));
    RenderMesh(meshes["romb_roz"], shaders["VertexColor"], glm::vec3(-25.5, 22, 0), glm::vec3(2));

    // stelute 3 x 4 seturi care ilustreaza pretul fiecarei arme
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(-40.5f, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(-28, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(-25, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(-15.5f, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(-12.5f, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(-3, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(0, 15, 0), glm::vec3(3));
    RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(3, 15, 0), glm::vec3(3));

    // aparitie stelute random dacă a trecut intervalul necesar pentru a genera un nou set
    spawnTimer_star += deltaTimeSeconds;
    if (spawnTimer_star >= spawnInterval_star) {
        spawnTimer_star = 0;

        // se genereaza cate 3 stelute odata
        for(i = 0; i < 3; i++) {
            random_x = std::rand() % 90; 
            random_y = std::rand() % 50;
            v_stele.push_back({random_x - 45, random_y - 25});
        }
    }

    // desenarea stelute random
    for (const auto& i : v_stele) {
        RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(i.x, i.y, 0), glm::vec3(8));
    }

    // desenare stelute - banii existenti
    for(i = 0 ; i < stars_no; i++) { // 11  + i * 3
        RenderMesh(meshes["steluta"], shaders["VertexColor"], glm::vec3(11 + i * 3, 17, 0), glm::vec3(3));
    }

    // Coliziune arma - inamic
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            for(k = 0; k < cols; k++) {
                if(matrix_enemy[i][j].getOccupied() && matrix_gun[i][k].getOccupied()) {
                    // coordonatele centrelor obiectelor vor fi pe  Ox: matrix_enemy[i][j].getX() , matrix_gun[i][j].getX()
                    // cercurile au aceeasi raza, stabilita la constructie
                    if(glm::distance(matrix_enemy[i][j].getX(), matrix_gun[i][k].getX()) < raza_hexagon + raza_stea) {
                        matrix_gun[i][k].setDisappear(true);
                        DrawOrDisappearGun(&matrix_gun[i][k], getOxGun(k), getOyGun(i), deltaTimeSeconds);
                    }
                }
            }
        }
    }

    // Aparitia proiectilelor la prezenta inamicilor
    for (i = 0; i < rows; i++) {  // pt fiecare rand
        for(j = 0; j < cols; j++) {  // pt fiecare coloana 
             
            // verific pentru care serie de inamici se poate trage
            enemy_y = -1;
            if( CanShoot(matrix_enemy[i][0], matrix_gun[i][j]) && getOxGun(j) + 1 <  matrix_enemy[i][0].getX()  ) {
                enemy_y = 0;
            }
            if( CanShoot(matrix_enemy[i][1], matrix_gun[i][j]) && getOxGun(j) + 1 <  matrix_enemy[i][1].getX()) {
                if(enemy_y == -1) {
                    enemy_y = 1;
                }
            }
            if( CanShoot(matrix_enemy[i][2], matrix_gun[i][j]) && getOxGun(j) + 1 <  matrix_enemy[i][2].getX()) {
                if(enemy_y == -1) {
                    enemy_y = 2;
                }
            }


            foundIndex = -1; // variabila prin care aflu daca trebuie un glont nou nout (ramane la valoarea initiala)
            for (index = 0; index < v_shot.size(); index++) {
                auto& shot = v_shot[index];
                if (shot.getRow() == i &&  shot.getCol() == j) {

                    foundIndex = index; // exista deja un glont si nu trebuie altul
                    if(v_shot[index].getSpawnTimer() >= spawnInterval_shot) {
                        v_shot[index].setSpawnTimer(0);
                        foundIndex = -2; //  mai trebuie un glont pt ca a trecut intervalul de timp
                    }
                }
            }

            
            // daca nu s-a mai generat glont pana acum pt acest inamic(nu exista intrare in vector) si e nou si distanta de inamic e suficienta
            if (foundIndex == -1 && enemy_y != -1) {
                if(getOxGun(j) + 20 <  matrix_enemy[i][enemy_y].getX()) {

                    Shot s = Shot(getOxGun(j), getOyGun(i), matrix_gun[i][j].getColor(), i , j, enemy_y, 0, 0);
                    v_shot.push_back(s);
                }
            }

            // daca s-a mai generat glontul dar e timpul pt unul nou
            if(foundIndex == -2 && enemy_y != -1) {
                
                Shot s = Shot(getOxGun(j), getOyGun(i), matrix_gun[i][j].getColor(), i , j, enemy_y, 0, 0);
                v_shot.push_back(s);
            }
        }
    }
    
   
    // pentru fiecare glont existent
    for (index = 0; index < v_shot.size(); index++) {
        
        auto& shot = v_shot[index];

        // modific campurile variabile
        v_shot[index].setX(v_shot[index].getX() + deltaTimeSeconds * 13);
        v_shot[index].setAngularStep(v_shot[index].getAngularStep() - deltaTimeSeconds * 3);
        v_shot[index].setSpawnTimer(v_shot[index].getSpawnTimer() + deltaTimeSeconds);

        // sterg glonturile care au iesit din scena
        if(v_shot[index].getX() > 55) {
            v_shot.erase(v_shot.begin() + index);
            // decrementez indexul pentru a compensa ștergerea elementului
            index--;
        }

        // Coliziune glont - inamic
        // coordonatele centrelor obiectelor 
        // pe Ox: v_shot[index].getX(), matrix_enemy[v_shot[index].getRow()][v_shot[index].getEnemyY()].getX()
        // razele raza_stea, raza_hexagon se cunosc de la constructie
        if(glm::distance(v_shot[index].getX(), matrix_enemy[v_shot[index].getRow()][v_shot[index].getEnemyY()].getX()) > raza_hexagon + raza_stea ) {
            MoveShot(&v_shot[index], deltaTimeSeconds);
        }  else {
            // decrementez variabila inamic
            counter = matrix_enemy[v_shot[index].getRow()][v_shot[index].getEnemyY()].getCounter() - 1;
            matrix_enemy[v_shot[index].getRow()][v_shot[index].getEnemyY()].setCounter(counter);

            if(counter <= 0) {
                // cand inamicul primescte 3 gloante, apelez functia care ii face scalare catre 0 (disparitie)
                matrix_enemy[v_shot[index].getRow()][v_shot[index].getEnemyY()].setDisappear(true);
            }

            // sterg glontul
            v_shot.erase(v_shot.begin() + index);  
            index--;
        }
    }


    // implementare arme - drag effect
    if(drag == 1) {
        Drag(color, getMyLogicX(realX_move), getMyLogicY(realY_move));
    }

    // desenare si disparitie arme deja plasate
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if(matrix_gun[i][j].getOccupied() == true) {
                DrawOrDisappearGun(&matrix_gun[i][j], getOxGun(j), getOyGun(i), deltaTimeSeconds);
            }
        }
    }   


    // implementare inamici, dacă a trecut intervalul necesar pentru a genera un nou inamic
    spawnTimer_enemy += deltaTimeSeconds;
    if (spawnTimer_enemy >= spawnInterval_enemy) {
        spawnTimer_enemy = 0;

        // generez random linia inamicului
        random_line = std::rand() % rows; 
        // generez random culoarea inamicului 
        random_color = std::rand() % 4;

        for (j = 0; j < cols; j++) {
            // generez inamicul doar daca nu exista deja pe acea coloana
            if (matrix_enemy[random_line][j].getOccupied() == false) {
                matrix_enemy[random_line][j].setOccupied(true);
                matrix_enemy[random_line][j].setCounter(3);
                matrix_enemy[random_line][j].setDisappear(false);
                matrix_enemy[random_line][j].setScale(3);
                if(random_color == 0) {
                    matrix_enemy[random_line][j].setColor("hexagon_albastru");
                } else if(random_color == 1) {
                    matrix_enemy[random_line][j].setColor("hexagon_roz");
                } else if(random_color == 2) {
                    matrix_enemy[random_line][j].setColor("hexagon_galben");
                } else {
                    matrix_enemy[random_line][j].setColor("hexagon_portocaliu");
                }
                break; 
            }
        }
    }

    // apelez functia de desenare a inamicilor existenti
    DrawEnemy(deltaTimeSeconds, &matrix_enemy, &lives, rows, cols);
}


void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    realX_move = mouseX;
    realY_move = 720 - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    realX_press = mouseX;
    realY_press = 720 - mouseY;

    //  disparitie prin scalare inversa
    if(button == 2) {
        WhichGreenSquare(getMyLogicX(realX_press),getMyLogicY(realY_press), &matrix_gun, color, button, &stars_no);
    }

    //  drag
    if ( button == 1) {
        WhichGunToDrag(&drag, getMyLogicX(realX_move), getMyLogicY(realY_move), &color, button, &stars_no);
    }

    // colectare stelute
    for (auto it = v_stele.begin(); it != v_stele.end(); ++it) {
        if(button == 1) {
            if (getMyLogicX(realX_press) < it->x + 5 && getMyLogicX(realX_press) > it->x - 5 && getMyLogicY(realY_press) < it->y + 5 && getMyLogicY(realY_press) > it->y - 2) {
                v_stele.erase(it);
                stars_no++;
                break; 
            }
        } 
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // apelez aceasta functie pt a vedea asupra carui patrat verde se face drop, daca anterior s-a facut drag
    if(drag == 1) {
        WhichGreenSquare(getMyLogicX(realX_move), getMyLogicY(realY_move), &matrix_gun, color, button, &stars_no);
        drag = 0;
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

// functie care calculeaza coordonata pe ox a scenei mele
float Tema1::getMyLogicX(float x) {
    return x / 12.8 - 50;
}

// functie care calculeaza coordonata pe oy a scenei mele
float Tema1::getMyLogicY(float y) {
    return y / 12.8 - 25;
}

// functii care calculeaza pozitia armei in functie de indicele din matrice
float Tema1::getOxGun(float j) {
    return -13 - (2 - j) * 12.5;
}
float Tema1::getOyGun(float i) {
    return 5 - i * 12.5;
}