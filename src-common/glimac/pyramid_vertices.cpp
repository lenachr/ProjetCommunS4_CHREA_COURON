#include "pyramid_vertices.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace glimac {
std::vector<ShapeVertex> pyramid_vertices(float sizeX, float sizeY, float sizeZ)
{
    // Sommets du toit
    std::vector<ShapeVertex> vertices{
        // Face avant
        {{-sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}}, // Bas gauche avant
        {{sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas droit avant
        {{0, sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},           // haut centre avant

        // Face arrière
        {{-sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}}, // bas gauche arrière
        {{sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas droit arrière
        {{0, sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},           // haut centre arrière

        // Côtés
        {{0, sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},          // haut centre avant
        {{0, sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},           // haut centre arrière
        {{sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas droit arrière
        {{sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas droit arrière
        {{sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}}, // bas droit avant
        {{0, sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},          // haut centre avant

        {{0, sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},           // haut centre avant
        {{0, sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},            // haut centre arrière
        {{-sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas gauche arrière
        {{-sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas gauche arrière
        {{-sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}}, // Bas gauche avant
        {{0, sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},           // haut centre avant

        {{-sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}}, // Bas gauche avant
        {{sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas droit avant
        {{sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},   // bas droit arrière
        {{sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},   // bas droit arrière
        {{-sizeX / 2, -sizeY / 2, -sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}}, // Bas gauche avant
        {{-sizeX / 2, -sizeY / 2, sizeZ / 2}, {0.f, 0.f, 1.f}, {0.f, 0.f}},  // bas gauche arrière

    };
    return vertices;
}
}; // namespace glimac