#pragma once
#include "p6/p6.h"

// Structure représentant le programme GPU pour dessiner les arbres
struct TreeProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTreeTexture;

    TreeProgram()
        : m_Program{p6::load_shader("src/shaders/3D.vs.glsl", "src/shaders/tex3D.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uTreeTexture  = glGetUniformLocation(m_Program.id(), "uTexture");
    }
};
