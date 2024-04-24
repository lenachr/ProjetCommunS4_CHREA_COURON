#pragma once
#include <glimac/common.hpp>
#include "ObjectProgram.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

GLuint bindVBO(const std::vector<glimac::ShapeVertex> object);
GLuint bindVAO(GLuint vbo);
void   bindTexture(std::vector<GLuint> textureID, int i, img::Image& texture);
void   drawObject(GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, float coefLight);

void renderObject(GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID, float coefLight);