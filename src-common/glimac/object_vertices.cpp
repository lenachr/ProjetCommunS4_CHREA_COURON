#include "object_vertices.hpp"
#include <glm/glm.hpp>
#include <vector>
#include "cone_vertices.hpp"
#include "cube_vertices.hpp"
#include "glm/gtx/transform.hpp"
#include "pyramid_vertices.hpp"
#include "sphere_vertices.hpp"

namespace glimac {

std::vector<ShapeVertex> tree_vertices(float size) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    // Vertices du rectangle
    std::vector<ShapeVertex> rectangle = cube_vertices(size, size * 4, size);

    // Vertices de la sphère
    std::vector<ShapeVertex> sphere = sphere_vertices(size * 6, 32, 16);

    // Déplacer la sphère vers le haut pour la placer au-dessus du rectangle
    for (auto& vertex : sphere)
    {
        vertex.position.y += 9.5f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    // Fusionner les vertices du rectangle et de la sphère
    rectangle.insert(rectangle.end(), sphere.begin(), sphere.end());

    // On met l'arbre au niveau du plan y=0
    for (auto& vertex : rectangle)
    {
        vertex.position.y += 2.f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    return rectangle;
}

std::vector<ShapeVertex> bench_vertices(float size) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    // Planche assise du banc
    std::vector<ShapeVertex> sit = cube_vertices(size * 3, size / 4, size);

    // Déplacer l'assise vers le bas
    for (auto& vertex : sit)
    {
        vertex.position.z -= size * -0.5f; // Déplacement vers le bas pour placer l'assise au niveau du plan y=0
    }

    // Planches du dossier
    std::vector<ShapeVertex> back01 = cube_vertices(size * 3.f, size / 3.f, size / 8.f);
    // Déplacer le dossier vers le haut
    for (auto& vertex : back01)
    {
        vertex.position.y += size * 1.7f; // Déplacement vers le haut pour placer le dossier au-dessus de l'assise
    }

    std::vector<ShapeVertex> back02 = cube_vertices(size * 3.f, size / 3.f, size / 8.f);
    // Déplacer le dossier vers le haut
    for (auto& vertex : back02)
    {
        vertex.position.y += size * 0.9; // Déplacement vers le haut pour placer le dossier au-dessus de l'assise
    }

    // Pieds du banc
    // Pied droit arrière
    std::vector<ShapeVertex> rightBackFoot = cube_vertices(size / 4.f, size * 2.f, size / 4.f);
    for (auto& vertex : rightBackFoot)
    {
        vertex.position.x += size * 2;   // Déplacement vers la droite pour placer le pied droit
        vertex.position.z -= size / 8.f; // Déplacement vers l'avant pour placer le pied droit
    }

    // Pied gauche arrière
    std::vector<ShapeVertex> leftBackFoot = cube_vertices(size / 4.f, size * 2.f, size / 4.f);
    for (auto& vertex : leftBackFoot)
    {
        vertex.position.x -= size * 2;   // Déplacement vers la gauche pour placer le pied gauche
        vertex.position.z -= size / 8.f; // Déplacement vers l'avant pour placer le pied gauche
    }

    // Pied droit avant
    std::vector<ShapeVertex> rightFrontFoot = cube_vertices(size / 4.f, size, size / 4.f);
    for (auto& vertex : rightFrontFoot)
    {
        vertex.position.x += size * 2;          // Déplacement vers la droite pour placer le pied droit
        vertex.position.z += size - size / 8.f; // Déplacement vers l'arrière pour placer le pied droit
        vertex.position.y -= size;              // Déplacement vers le bas pour placer le pied droit au niveau du plan y=0
    }

    // Pied gauche avant
    std::vector<ShapeVertex> leftFrontFoot = cube_vertices(size / 4.f, size, size / 4.f);
    for (auto& vertex : leftFrontFoot)
    {
        vertex.position.x -= size * 2;          // Déplacement vers la gauche pour placer le pied gauche
        vertex.position.z += size - size / 8.f; // Déplacement vers l'arrière pour placer le pied gauche
        vertex.position.y -= size;              // Déplacement vers le bas pour placer le pied gauche au niveau du plan y=0
    }

    // Fusionner les différentes parties du banc
    std::vector<ShapeVertex> bench;
    bench.insert(bench.end(), sit.begin(), sit.end());
    bench.insert(bench.end(), back01.begin(), back01.end());
    bench.insert(bench.end(), back02.begin(), back02.end());
    bench.insert(bench.end(), rightBackFoot.begin(), rightBackFoot.end());
    bench.insert(bench.end(), leftBackFoot.begin(), leftBackFoot.end());
    bench.insert(bench.end(), rightFrontFoot.begin(), rightFrontFoot.end());
    bench.insert(bench.end(), leftFrontFoot.begin(), leftFrontFoot.end());

    // On met le banc au niveau du plan y=0
    for (auto& vertex : bench)
    {
        vertex.position.y += 2.f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    return bench;
}

std::vector<ShapeVertex> boids_vertices(float size)
{
    // partie haute
    std::vector<ShapeVertex> boidHaut{
        // Triangle gauche
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // Triangle centre Gauche
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // Triangle centre Droit
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // Triangle droit
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},

    };
    // partie basse
    std::vector<ShapeVertex> boidBas{
        // Triangle gauche
        {{0.f, size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // Triangle centre Gauche
        {{0.f, size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // Triangle centre Droit
        {{0.f, size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // Triangle droit
        {{0.f, size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},

    };

    // partie entre les deux
    std::vector<ShapeVertex> boidFill{
        // extérieur gauche
        {{0.f, size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // extérieur centre gauche
        {{-size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},

        {{-0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},

        // extérieur centre droit
        {{size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},

        {{0.3f * size, -0.7f * size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.3f * size, -0.7f * size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        // extérieur droit
        {{0.f, size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, -0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{size, -size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{0.f, size, 0.2f * size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
    };

    std::vector<ShapeVertex>
        boid;
    boid.insert(boid.end(), boidHaut.begin(), boidHaut.end());
    boid.insert(boid.end(), boidBas.begin(), boidBas.end());
    boid.insert(boid.end(), boidFill.begin(), boidFill.end());

    return boid;
};

std::vector<ShapeVertex> character_vertices(float size)
{
    // Tête
    std::vector<ShapeVertex> head = sphere_vertices(size / 3.f, 32, 16);
    for (auto& vertex : head)
    {
        vertex.position.y += 0.8f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    // Corps
    std::vector<ShapeVertex> body = cone_vertices(size, size / 2.f, 32, 16);
    for (auto& vertex : head)
    {
        vertex.position.y += 0.3f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    // jambes
    std::vector<ShapeVertex> rightLeg = cube_vertices(0.07f * size, 0.3f * size, 0.07f * size);
    for (auto& vertex : rightLeg)
    {
        vertex.position.x += size * 0.15f; // décalage vertical pour placer la sphère au-dessus du rectangle
    }
    std::vector<ShapeVertex> leftLeg = cube_vertices(0.07f * size, 0.3f * size, 0.07f * size);
    for (auto& vertex : leftLeg)
    {
        vertex.position.x += size * -0.15f; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    // bras
    std::vector<ShapeVertex> rightArm = cube_vertices(0.3f * size, 0.07f * size, 0.07f * size);
    for (auto& vertex : rightArm)
    {
        vertex.position.x += size * 0.3f; // décalage vertical pour placer la sphère au-dessus du rectangle
        vertex.position.y += size * 0.6f; // décalage vertical pour placer la sphère au-dessus du rectangle
    }
    std::vector<ShapeVertex> leftArm = cube_vertices(0.3f * size, 0.07f * size, 0.07f * size);
    for (auto& vertex : leftArm)
    {
        vertex.position.x += size * -0.3f; // décalage vertical pour placer la sphère au-dessus du rectangle
        vertex.position.y += size * 0.6f;  // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    std::vector<ShapeVertex>
        character;
    character.insert(character.end(), head.begin(), head.end());
    character.insert(character.end(), body.begin(), body.end());
    character.insert(character.end(), rightLeg.begin(), rightLeg.end());
    character.insert(character.end(), leftLeg.begin(), leftLeg.end());
    character.insert(character.end(), rightArm.begin(), rightArm.end());
    character.insert(character.end(), leftArm.begin(), leftArm.end());

    // on met le personnage au niveau y=0
    for (auto& vertex : character)
    {
        // vertex.position.y += -2.3f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    return character;
};

std::vector<ShapeVertex> house_vertices(float size)
{
    // base
    std::vector<ShapeVertex> cube = cube_vertices(size, size, size / 1.5f);
    for (auto& vertex : cube)
    {
        // vertex.position.y += 0.8f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    // toit
    std::vector<ShapeVertex> roof = pyramid_vertices(size * 2.5f, size * 1.5f, size * 2.5f / 1.5f);
    for (auto& vertex : roof)
    {
        vertex.position.y += 1.5f * size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    std::vector<ShapeVertex> house;
    house.insert(house.end(), cube.begin(), cube.end());
    house.insert(house.end(), roof.begin(), roof.end());

    // on met la maison au niveau y=0
    for (auto& vertex : house)
    {
        vertex.position.y += size; // décalage vertical pour placer la sphère au-dessus du rectangle
    }

    return house;
};

std::vector<ShapeVertex> floor_vertices(float size)
{
    // base
    std::vector<ShapeVertex> floor{
        // Triangle gauche
        {{size, 0.f, size}, {0.f, 0.f, 1.f}, {1.f, 0.f}},
        {{-size, 0.f, size}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{-size, 0.f, -size}, {0.f, 0.f, 1.f}, {0.f, 1.f}},
        {{-size, 0.f, -size}, {0.f, 0.f, 1.f}, {0.f, 1.f}},
        {{size, 0.f, -size}, {0.f, 0.f, 1.f}, {1.f, 1.f}},
        {{size, 0.f, size}, {0.f, 0.f, 1.f}, {1.f, 0.f}},
    };

    return floor;
};

} // namespace glimac