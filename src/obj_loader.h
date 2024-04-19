#pragma once
#include <iostream>
#include <vector>
#include "p6/p6.h"

class Model {
public:
    std::vector<float> load_model(const char* filename, glm::mat4 preTransform);
    GLuint             bind3D(const Model object);
    GLuint             VAO;
    GLuint             VBO;

private:
    std::vector<float> vertices;
    int                vertexCount;
};