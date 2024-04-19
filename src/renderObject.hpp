#pragma once
#include <glimac/common.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "ObjectProgram.hpp"

GLuint bindVBO(const std::vector<glimac::ShapeVertex> object);
GLuint bindVAO(GLuint vbo);
void   bindTexture(std::vector<GLuint> textureID, int i, img::Image& texture);
void   drawObject(GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram);

void renderObject(GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID);