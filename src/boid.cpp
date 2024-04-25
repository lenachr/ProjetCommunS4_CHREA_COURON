#include "boid.hpp"

// Dessin des boids
void Boid::draw(GLuint vao, GLsizei vertexCount, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID, float coefLight, int typeLight)
{
    renderObject(vao, vertexCount, position, scale, rotation, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID, coefLight, typeLight);
}

// Destructeur
Boid::~Boid()
{
}

// Methode qui gère les mouvements et les collisions du cube
void Boid::apply_speed(std::vector<Boid>& allBoids)
{
    if (falling == true)
    {
        position.y -= 1.f;
    }
    else
    {
        position.x += speed.x;
        position.y += speed.y;
        position.z += speed.z;

        for (auto& Boid : allBoids)
        {
            // Si contact mur haut
            if (Boid.position.y > 100.f)
            {
                Boid.position.y = 30.f;
            }
            // Si contact mur bas
            if (Boid.position.y < 30.0f)
            {
                Boid.position.y = 99.f;
            }

            // Si contact mur gauche
            if (Boid.position.x < -95.f)
            {
                Boid.position.x = 95.f;
            }

            // Si contact mur droit
            if (Boid.position.x > 95.f)
            {
                Boid.position.x = -95.f;
            }

            // Si contact mur profondeur gauche
            if (Boid.position.z < -95.f) //-1.1f
            {
                Boid.position.z = 95.f;
            }

            // Si contact mur profondeur droit
            if (Boid.position.z > 95.f)
            {
                Boid.position.z = -95.f;
            }
        }
    }
}

// Calcule la distance qui sépare 2 boids
float Boid::distance(const Boid& boid1, const Boid& boid2)
{
    return std::sqrt((boid2.position.x - boid1.position.x) * (boid2.position.x - boid1.position.x) + (boid2.position.y - boid1.position.y) * (boid2.position.y - boid1.position.y) + (boid2.position.z - boid1.position.z) * (boid2.position.z - boid1.position.z));
}

// Règle d'alignement
void Boid::alignement(const std::vector<Boid>& allBoids, double alignmentDistance)
{
    glm::vec3 averageAngle(0.0f, 0.0f, 0.0f);
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

// Règle de cohésion
void Boid::cohesion(const std::vector<Boid>& allBoids, double cohesionDistance, double cohesionFactor)
{
    glm::vec3 centerOfMass(0.0f, 0.0f, 0.0f);
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
        glm::vec3 cohesionDirection = centerOfMass - position;

        // Ajuster la vitesse du boid pour se diriger vers le centre de masse
        this->speed += static_cast<float>(cohesionFactor) * cohesionDirection;
    }
}

// Règle de séparation
void Boid::separation(const std::vector<Boid>& allBoids, float separationDistance, float separationFactor)
{
    glm::vec3 separation(0.0f, 0.0f, 0.0f);
    int       neighborCount = 0;

    for (const Boid& otherBoid : allBoids)
    {
        if (this != &otherBoid)
        {
            float dist = distance(*this, otherBoid);

            if (dist < separationDistance)
            {
                // Calculer le vecteur différence entre les positions
                glm::vec3 diff;
                diff.x = position.x - otherBoid.position.x;
                diff.z = position.z - otherBoid.position.z;
                diff.x /= dist;
                diff.z /= dist;

                // Ajouter le vecteur différence au vecteur de direction de l'évitement
                separation.x += diff.x;
                separation.z += diff.z;
                neighborCount++;
            }
        }
    }

    // Si des voisins ont été trouvés
    if (neighborCount > 0)
    {
        // Ajuster la position du boid pour se déplacer dans la direction opposée à celle des voisins proches
        this->position.x += separationFactor * separation.x;
        this->position.z += separationFactor * separation.z;
    }
}

// Rendu des boids ajouté dans le main.cpp
void Boid::update(std::vector<Boid>& allBoids, float alignement_coeff, float cohesion_coeff, float separation_coeff)
{
    apply_speed(allBoids);
    alignement(allBoids, alignement_coeff);
    cohesion(allBoids, cohesion_coeff, 0.01);
    separation(allBoids, separation_coeff, 0.1f);
}