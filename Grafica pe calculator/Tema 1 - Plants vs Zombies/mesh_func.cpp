#include "lab_m1/tema1/tema1.h"

#include <iostream>

using namespace std;
using namespace m1;


void Tema1::CreateMeshHexagons(float r, float g, float b, const char *s) {
    vector<VertexFormat> vertices
        {
            // hexagon mic
            VertexFormat(glm::vec3(0, 1, 0.2), glm::vec3(r, g, b)),  // sus si apoi la rand clockwise
            VertexFormat(glm::vec3(0.866, 0.5, 0.2), glm::vec3(r, g, b)), 
            VertexFormat(glm::vec3(0.866, -0.5, 0.2), glm::vec3(r, g, b)),   
            VertexFormat(glm::vec3(0, -1, 0.2), glm::vec3(r, g, b)), 
            VertexFormat(glm::vec3(-0.866, -0.5, 0.2), glm::vec3(r, g, b)),  
            VertexFormat(glm::vec3(-0.866, 0.5, 0.2), glm::vec3(r, g, b)),  
            VertexFormat(glm::vec3(0, 0, 0.2), glm::vec3(r, g, b)), // centru

            // hexagon mare
            VertexFormat(glm::vec3(0, 1.29, 0.1), glm::vec3(0.31, 0.29, 0.29)),  // sus si apoi la rand clockwise
            VertexFormat(glm::vec3(1.12, 0.64, 0.1), glm::vec3(0.31, 0.29, 0.29)), 
            VertexFormat(glm::vec3(1.12, -0.64, 0.1), glm::vec3(0.31, 0.29, 0.29)),  
            VertexFormat(glm::vec3(0, -1.29, 0.1), glm::vec3(0.31, 0.29, 0.29)),  
            VertexFormat(glm::vec3(-1.12, -0.64, 0.1), glm::vec3(0.31, 0.29, 0.29)),  
            VertexFormat(glm::vec3(-1.12, 0.64, 0.1), glm::vec3(0.31, 0.29, 0.29)), 
            VertexFormat(glm::vec3(0, -1, 0.1), glm::vec3(0.31, 0.29, 0.29)) // centru
        };
        vector<unsigned int> indices
        {
            0, 6, 1,
            1, 6, 2,
            2, 6, 3,
            3, 6, 4,
            4, 6, 5,
            5, 6, 0,
            13, 8, 7,
            13, 9, 8,
            13, 10, 9,
            13, 11, 10,
            13, 12, 11,
            13, 7, 12
        };
        CreateMesh(s, vertices, indices);
}

void Tema1::CreateMeshGuns(float r, float g, float b, const char *s) {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0.75, 0.5, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)), 
            VertexFormat(glm::vec3(1.93, 0.5, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)), 
            VertexFormat(glm::vec3(1.93, -0.5, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)), 
            VertexFormat(glm::vec3(0.75, -0.5, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, -2, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-1, 0, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 2, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0, 0.4), glm::vec3(r, g, b), glm::vec3(0.2, 0.8, 0.6))
        };
        vector<unsigned int> indices
        {
            7, 6, 4,
            4, 6, 5,
            3, 1, 0,
            3, 2, 1
        };
        CreateMesh(s, vertices, indices);
}

void Tema1::CreateMeshStars(float r, float g, float b, const char *s) {
    vector<VertexFormat> vertices
        {
            // Colțuri int  
            VertexFormat(glm::vec3(0.112, 0.154, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // dreapta sus 
            VertexFormat(glm::vec3(0.181, -0.059, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // dreapta jos 
            VertexFormat(glm::vec3(0, -0.191, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // jos 
            VertexFormat(glm::vec3(-0.181, -0.059, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // stanga jos 
            VertexFormat(glm::vec3(-0.112, 0.154, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // stanga sus 

            // Colțuri ext
            VertexFormat(glm::vec3(0, 0.5, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // sus 
            VertexFormat(glm::vec3(0.475, 0.154, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), //  dreapta sus 
            VertexFormat(glm::vec3(0.293, -0.404, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // dreapta jos 
            VertexFormat(glm::vec3(-0.293, -0.404, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)), // stanga jos 
            VertexFormat(glm::vec3(-0.475, 0.154, 0.25), glm::vec3(r, g, b), glm::vec3(0.8, 0.2, 0.6)) // stanga sus
        };

        vector<unsigned int> indices =
        {
            // triunghiurile din varfurile
            0, 5, 4,
            1, 6, 0,
            2, 7, 1,
            2, 3, 8,
            4, 9, 3,
            // cele 3 triunghiuri interioare cu varful in jos
            1, 0, 2,
            0, 4, 2,
            2, 4, 3
        };
        CreateMesh(s, vertices, indices);
}

void Tema1::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    GLuint VBO_ID;			
	glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    

    unsigned int IBO = 0;
    GLuint IBO_ID;
    glGenBuffers(1, &IBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}