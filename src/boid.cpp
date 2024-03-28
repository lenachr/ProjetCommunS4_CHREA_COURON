#include "boid.hpp"

void Boid::draw(p6::Context* ctx, GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, TreeProgram& TreeProgram, GLuint textureID)
{
    // ctx->triangle(
    // p6::Point2D{-0.05f, 0.035f}, p6::Point2D{-0.05f, -0.035f}, p6::Point2D{0.05f, 0.f}, p6::Center{position}, p6::Rotation{speed}
    // );
    renderObject(vao, vertexCount, translation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID);
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
    if (position.y > 0.95f) // 0.75f
    {
        position.y = -0.95f;
    }
    // // Si contact mur bas
    if (position.y < -0.95f) //-1.1f
    {
        position.y = 0.95f;
    }
    // // Si contact mur gauche
    if (position.x < -0.95f) //-1.1f
    {
        position.x = 0.95f;
    }
    // // Si contact mur droit
    if (position.x > 0.95f) // 0.75f
    {
        position.x = -0.95f;
    }
}

float Boid::distance(const Boid& boid1, const Boid& boid2)
{
    return std::sqrt((boid2.position.x - boid1.position.x) * (boid2.position.x - boid1.position.x) + (boid2.position.y - boid1.position.y) * (boid2.position.y - boid1.position.y));
}

void Boid::alignement(const std::vector<Boid>& allBoids, double alignmentDistance)
{
    glm::vec2 averageAngle(0.0, 0.0);
    int       neighborCount = 0;

    for (const Boid& otherBoid : allBoids)
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

    // Si des voisins ont été trouvés
    if (neighborCount > 0)
    {
        averageAngle /= neighborCount;
        // Ajuster l'angle moyen du boid actuel
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

    // Si des voisins ont été trouvés
    if (neighborCount > 0)
    {
        centerOfMass /= neighborCount;
        glm::vec2 cohesionDirection = centerOfMass - position;

        // Ajuster la vitesse du boid pour se diriger vers le centre de masse
        this->speed += static_cast<float>(cohesionFactor) * cohesionDirection;
    }
}

void Boid::separation(const std::vector<Boid>& allBoids, float separationDistance, float separationFactor)
{
    glm::vec2 separation(0.0f, 0.0f);
    int       neighborCount = 0;

    for (const Boid& otherBoid : allBoids)
    {
        if (this != &otherBoid)
        {
            float dist = distance(*this, otherBoid);

            if (dist < separationDistance)
            {
                // Calculer le vecteur différence entre les positions
                glm::vec2 diff;
                diff.x = position.x - otherBoid.position.x;
                diff.y = position.y - otherBoid.position.y;
                diff.x /= dist;
                diff.y /= dist;

                // Ajouter le vecteur différence au vecteur de direction de l'évitement
                separation.x += diff.x;
                separation.y += diff.y;
                neighborCount++;
            }
        }
    }

    // Si des voisins ont été trouvés
    if (neighborCount > 0)
    {
        // Ajuster la position du boid pour se déplacer dans la direction opposée à celle des voisins proches
        this->position.x += separationFactor * separation.x;
        this->position.y += separationFactor * separation.y;
    }
}

void Boid::update(const std::vector<Boid>& allBoids, float alignement_coeff, float cohesion_coeff, float separation_coeff)
{
    apply_speed();
    alignement(allBoids, alignement_coeff);
    cohesion(allBoids, cohesion_coeff, 0.01);
    separation(allBoids, separation_coeff, 0.1f);
}