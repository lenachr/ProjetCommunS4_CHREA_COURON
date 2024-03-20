#include "boid.hpp"
#include <cmath>
#include "glm/fwd.hpp"

void Boid::draw(p6::Context* ctx)
{
    ctx->triangle(
        p6::Point2D{-0.05f, 0.035f}, p6::Point2D{-0.05f, -0.035f}, p6::Point2D{0.05f, 0.f}, p6::Center{position}, p6::Rotation{speed}

        // p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.25f, 0.2f}, p6::Point2D{0.2f, 0.25f}, p6::Center{position}
    );
}

// destructeur
Boid::~Boid()
{
}

// Methode qui gère les mouvements
void Boid::apply_speed()
{
    position.x += speed.x;
    position.y += speed.y;

    // // Si contact mur haut
    if (position.y > 1.f) // 0.75f
    {
        position.y = -1.1f;
    }
    // // Si contact mur bas
    if (position.y < -1.1f) //-1.1f
    {
        position.y = 0.75f;
    }
    // // Si contact mur gauche
    if (position.x < -0.9f) //-1.1f
    {
        position.x = 0.75f;
    }
    // // Si contact mur droit
    if (position.x > 0.75f) // 0.75f
    {
        position.x = -0.9f;
    }
}

float Boid::distance(const Boid& boid1, const Boid& boid2)
{
    return std::sqrt((boid2.position.x - boid1.position.x) * (boid2.position.x - boid1.position.x) + (boid2.position.y - boid1.position.y) * (boid2.position.y - boid1.position.y));
}

void Boid::separation(const std::vector<Boid>& allBoid, double separationDistance)
{
    glm::vec2 totalSeparation{0.f};

    for (const Boid& otherBoid : allBoid)
    {
        if (this != &otherBoid)
        {
            float dist = distance(*this, otherBoid);

            if (dist < separationDistance)
            {
                // Calculer la contribution à la séparation
                float separationForce = 1.0f / dist;

                // Ajouter à la somme totale
                totalSeparation += (position - otherBoid.position) * separationForce;
            }
        }
    }

    // Appliquer la séparation aux coordonnées du boid
    position += totalSeparation;
}

void Boid::alignement(const std::vector<Boid>& allBoid, double alignmentDistance)
{
    glm::vec2 averageAngle(0.0, 0.0);
    int       neighborCount = 0;

    for (const Boid& otherBoid : allBoid)
    {
        if (this != &otherBoid)
        {
            float dist = distance(*this, otherBoid);

            if (dist < alignmentDistance)
            {
                // Ajouter à la somme totale des angles
                averageAngle += otherBoid.speed;
                neighborCount++;
            }
        }
    }

    // Si des voisins ont été trouvés, ajuster l'angle moyen du boid actuel
    if (neighborCount > 0)
    {
        averageAngle /= neighborCount;
        this->speed = averageAngle;
    }
}

void Boid::cohesion(const std::vector<Boid>& allBoids, double cohesionDistance, double cohesionFactor)
{
    glm::vec2 centerOfMass(0.0, 0.0);
    int       neighborCount = 0;

    for (const Boid& otherBoid : allBoids)
    {
        if (this != &otherBoid)
        {
            float dist = distance(*this, otherBoid);

            if (dist < cohesionDistance)
            {
                // Ajouter à la somme totale des angles
                centerOfMass += otherBoid.position;
                neighborCount++;
            }
        }
    }

    // Si des voisins ont été trouvés, ajuster l'angle moyen du boid actuel
    if (neighborCount > 0)
    {
        centerOfMass /= neighborCount;
        glm::vec2 cohesionDirection = centerOfMass - position;

        // Ajuster la position du boid pour se diriger vers le centre de masse
        this->speed += static_cast<float>(cohesionFactor) * cohesionDirection;
    }
}

void Boid::update(const std::vector<Boid>& allBoids)
{
    apply_speed();
    separation(allBoids, 0.01);
    alignement(allBoids, 0.1);
    cohesion(allBoids, 0.1, 0.01);
}