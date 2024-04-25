#include "cube_vertices.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace glimac {

std::vector<ShapeVertex> cube_vertices(float sizeX, float sizeY, float sizeZ)
{
    // Sommets du cube
    std::vector<ShapeVertex> vertices{
        // Face avant
        {{sizeX, -sizeY, sizeZ}, {0.f, 0.f, 1.f}, {0.f, 1.f}},
        {{sizeX, sizeY, sizeZ}, {0.f, 0.f, 1.f}, {0.0f, 0.0f}},
        {{-sizeX, sizeY, sizeZ}, {0.f, 0.f, 1.f}, {1.f, 0.f}},
        {{-sizeX, sizeY, sizeZ}, {0.f, 0.f, 1.f}, {1.f, 0.f}},
        {{-sizeX, -sizeY, sizeZ}, {0.f, 0.f, 1.f}, {1.f, 1.0f}},
        {{sizeX, -sizeY, sizeZ}, {0.f, 0.f, 1.f}, {0.f, 1.f}},

        // Face arrière
        {{sizeX, -sizeY, -sizeZ}, {0.f, 0.f, -1.f}, {0.f, 1.f}},
        {{sizeX, sizeY, -sizeZ}, {0.f, 0.f, -1.f}, {0.f, 0.f}},
        {{-sizeX, sizeY, -sizeZ}, {0.f, 0.f, -1.f}, {1.f, 0.f}},
        {{-sizeX, sizeY, -sizeZ}, {0.f, 0.f, -1.f}, {1.f, 0.f}},
        {{-sizeX, -sizeY, -sizeZ}, {0.f, 0.f, -1.f}, {1.f, 1.f}},
        {{sizeX, -sizeY, -sizeZ}, {0.f, 0.f, -1.f}, {0.0f, 1.f}},

        // Face haut
        {{sizeX, sizeY, -sizeZ}, {1.f, 0.f, 0.f}, {1.f, 0.0f}},
        {{sizeX, sizeY, sizeZ}, {1.f, 0.f, 0.f}, {1.f, 1.f}},
        {{-sizeX, sizeY, sizeZ}, {1.f, 0.f, 0.f}, {0.f, 1.f}},
        {{-sizeX, sizeY, sizeZ}, {1.f, 0.f, 0.f}, {0.f, 1.f}},
        {{-sizeX, sizeY, -sizeZ}, {1.f, 0.f, 0.f}, {0.f, 0.f}},
        {{sizeX, sizeY, -sizeZ}, {1.f, 0.f, 0.f}, {1.f, 0.f}},

        // Face bas
        {{sizeX, -sizeY, sizeZ}, {-1.f, 0.f, 0.f}, {1.f, 1.f}},
        {{sizeX, -sizeY, -sizeZ}, {-1.f, 0.f, 0.f}, {1.f, 0.f}},
        {{-sizeX, -sizeY, -sizeZ}, {-1.f, 0.f, 0.f}, {0.f, 0.f}},
        {{-sizeX, -sizeY, -sizeZ}, {-1.f, 0.f, 0.f}, {0.f, 0.f}},
        {{-sizeX, -sizeY, sizeZ}, {-1.f, 0.f, 0.f}, {0.f, 1.f}},
        {{sizeX, -sizeY, sizeZ}, {-1.f, 0.f, 0.f}, {1.f, 1.f}},

        // Face Gauche
        {{sizeX, -sizeY, sizeZ}, {0.f, 1.f, 0.f}, {1.f, 1.0f}},
        {{sizeX, -sizeY, -sizeZ}, {0.f, 1.f, 0.f}, {0.0f, 1.0f}},
        {{sizeX, sizeY, -sizeZ}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
        {{sizeX, sizeY, -sizeZ}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
        {{sizeX, sizeY, sizeZ}, {0.f, 1.f, 0.f}, {1.f, 0.f}},
        {{sizeX, -sizeY, sizeZ}, {0.f, 1.f, 0.f}, {1.f, 1.f}},

        // Face droite
        {{-sizeX, -sizeY, sizeZ}, {0.f, -1.f, 0.f}, {1.f, 1.f}},
        {{-sizeX, -sizeY, -sizeZ}, {0.f, -1.f, 0.f}, {0.f, 1.f}},
        {{-sizeX, sizeY, -sizeZ}, {0.f, -1.f, 0.f}, {0.f, 0.f}},
        {{-sizeX, sizeY, -sizeZ}, {0.f, -1.f, 0.f}, {0.f, 0.f}},
        {{-sizeX, sizeY, sizeZ}, {0.f, -1.f, 0.f}, {1.f, 0.f}},
        {{-sizeX, -sizeY, sizeZ}, {0.f, -1.f, 0.f}, {1.f, 1.f}}
    };

    return vertices;
}
} // namespace glimac