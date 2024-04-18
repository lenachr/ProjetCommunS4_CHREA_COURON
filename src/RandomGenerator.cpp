#include "RandomGenerator.hpp"

float generateRandomPositionTree()
{
    float u = static_cast<float>(rand()) / RAND_MAX;

    // Si u est inférieur à 0.8, générer un nombre entre 00 et 100
    if (u < 0.6f)
    {
        return 0.0f + u * 100.0f;
    }
    // Sinon u se trouve entre -100 et 0
    else
    {
        return 10 + u * -100.0f;
    }
}