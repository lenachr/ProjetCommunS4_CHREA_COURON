#pragma once
#include <cmath>
#include <glimac/object_vertices.hpp>
#include "ObjectProgram.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"
#include "renderObject.hpp"

class Boid {
public:
    Boid(glm::vec3 position, glm::vec3 speed)
        : position{position}, speed{speed}, falling(false)
    {}

    void draw(GLuint vao, GLsizei vertexCount, glm::vec3 Translation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID);
    void update(std::vector<Boid>& allBoid, float alignement_coeff, float cohesion_coeff, float separation_coeff);
    ~Boid();

private:
    void apply_speed(std::vector<Boid>& allBoids);
    // void  apply_speed(std::vector<Boid>& allBoids, GLuint vao, GLsizei vertexCount, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID);
    void  separation(const std::vector<Boid>& allBoid, float separationDistance, float separationFactor);
    void  alignement(const std::vector<Boid>& allBoid, double alignmentDistance);
    float distance(const Boid& boid1, const Boid& boid2);
    void  cohesion(const std::vector<Boid>& allBoids, double cohesionDistance, double cohesionFactor);

private:
    glm::vec3 position;
    glm::vec3 speed;

public:
    bool falling;
};