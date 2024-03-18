#include "boid.hpp"
#include <cmath>

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
    // // Si contact mur haut
    if (position.y > 0.75f) // 0.75f
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
    // On retourne la nouvelle position
    position.x += speed.x;
    position.y += speed.y;
}

float Boid::distance(const Boid& boid1, const Boid& boid2)
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

double Boid::angleDifference(const Boid& boid1, const Boid& boid2)
{
    double angle1 = std::atan2(boid1.rotation.y, boid1.rotation.x) * 180.0 / 3.14;
    double angle2 = std::atan2(boid2.rotation.y, boid2.rotation.x) * 180.0 / 3.14;

    // Assurez-vous que les angles sont dans la plage [0, 360)
    while (angle1 < 0)
        angle1 += 360.0;
    while (angle1 >= 360.0)
        angle1 -= 360.0;
    while (angle2 < 0)
        angle2 += 360.0;
    while (angle2 >= 360.0)
        angle2 -= 360.0;

    // Calcule la différence d'angle entre angle2 et angle1
    double diff = angle2 - angle1;

    // Assurez-vous que la différence d'angle est dans la plage [-180, 180)
    while (diff < -180.0)
        diff += 360.0;
    while (diff >= 180.0)
        diff -= 360.0;

    return diff;
}

void Boid::alignement(const std::vector<Boid>& allBoid, double alignmentDistance)
{
    double averageAngle  = 0.0;
    int    neighborCount = 0;

    for (const Boid& otherBoid : allBoid)
    {
        if (this != &otherBoid)
        {
            float dist = distance(*this, otherBoid);

            if (dist < alignmentDistance)
            {
                // Calculer la différence d'angle avec le boid voisin
                double angleDiff = angleDifference(*this, otherBoid);

                // Ajouter à la somme totale des angles
                averageAngle += angleDiff;
                neighborCount++;
            }
        }
    }

    // Si des voisins ont été trouvés, ajuster l'angle moyen du boid actuel
    if (neighborCount > 0)
    {
        averageAngle /= neighborCount;
        this->rotation += 2 * averageAngle; // someFactor est un coefficient d'ajustement
    }
}

void Boid::update(const std::vector<Boid>& allBoid)
{
    apply_speed();
    separation(allBoid, 0.01);
    alignement(allBoid, 0.01);
}