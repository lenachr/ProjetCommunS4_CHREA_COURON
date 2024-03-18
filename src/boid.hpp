#pragma once
#include "glm/glm.hpp"
#include "p6/p6.h"

class Boid {
public:
    Boid(glm::vec2 position, glm::vec2 rotation, glm::vec2 speed)
        : position{position}, rotation{rotation}, speed{speed}
    {}

    void draw(p6::Context* ctx);
    void update(const std::vector<Boid>& allBoid);
    ~Boid();

private:
    void   apply_speed();
    void   separation(const std::vector<Boid>& allBoid, double separationDistance);
    void   alignement(const std::vector<Boid>& allBoid, double alignmentDistance);
    double angleDifference(const Boid& boid1, const Boid& boid2);

    float distance(const Boid& boid1, const Boid& boid2);

private:
    glm::vec2 position;
    glm::vec2 rotation;
    glm::vec2 speed;
};