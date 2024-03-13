#include "boid.hpp"

void Boid::draw(p6::Context* ctx)
{
    ctx->triangle(
        p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.25f, 0.2f}, p6::Point2D{0.2f, 0.25f}, p6::Center{position}, p6::Rotation{rotation}
    );
}

// destructeur
Boid::~Boid()
{
}

// Methode qui gère les mouvements
void Boid::apply_speed()
{
    // Si contact mur haut
    if (position.y > 0.75f)
    {
        position.y = -1.1f;
    }
    // Si contact mur bas
    if (position.y < -1.1f)
    {
        position.y = 0.75f;
    }
    // Si contact mur gauche
    if (position.x < -1.1f)
    {
        position.x = 0.75f;
    }
    // Si contact mur droit
    if (position.x > 0.75f)
    {
        position.x = -1.1f;
    }
    // On retourne la nouvelle position
    position.x += speed.x;
    position.y += speed.y;
}

double Boid::distance(const Boid& boid1, const Boid& boid2)
{
    return std::sqrt((boid2.position.x - boid1.position.x) * (boid2.position.x - boid1.position.x) + (boid2.position.y - boid1.position.y) * (boid2.position.y - boid1.position.y));
}

// #include <vector>

void Boid::separation(const std::vector<Boid>& allBoid, double separationDistance)
{
    glm::vec2 totalSeparation{0.f};

    for (const Boid& otherBoid : allBoid)
    {
        if (this != &otherBoid)
        {
            double dist = distance(*this, otherBoid);

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

void Boid::update(const std::vector<Boid>& allBoid)
{
    apply_speed();
    separation(allBoid, 0.1);
}