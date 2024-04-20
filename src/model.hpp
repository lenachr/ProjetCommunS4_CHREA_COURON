#pragma once
#include <iostream>
#include <vector>
#include "glimac/common.hpp"
#include "p6/p6.h"
#include "tiny_obj_loader.h"

class Model {
public:
    void                             load_model(const char* filename);
    int                              vertexCount;
    std::vector<glimac::ShapeVertex> vertices;

private:
};