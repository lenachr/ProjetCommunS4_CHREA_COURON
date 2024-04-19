#pragma once
#include "p6/p6.h"

// Structure représentant le programme GPU pour dessiner les arbres
struct ObjectProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTreeTexture;
    // La lumière
    GLint uLightPos_vs;
    GLint uLightIntensity;
    GLint uKd;
    GLint uKs;
    GLint uShininess;

    ObjectProgram()
        // : m_Program{p6::load_shader("src/shaders/3D.vs.glsl", "src/shaders/tex3D.fs.glsl")}
        : m_Program{p6::load_shader("src/shaders/3D.vs.glsl", "src/shaders/directionalLight.fs.glsl")}
    // : m_Program{p6::load_shader("src/shaders/3D.vs.glsl", "src/shaders/pointLight.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uTreeTexture  = glGetUniformLocation(m_Program.id(), "uTexture");
        // La lumière
        // uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
        uKd             = glGetUniformLocation(m_Program.id(), "uKd");
        uKs             = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess      = glGetUniformLocation(m_Program.id(), "uShininess");
    }
};
