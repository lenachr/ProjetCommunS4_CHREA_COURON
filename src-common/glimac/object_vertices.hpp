#pragma once
#include <vector>
#include "common.hpp"
#include "cube_vertices.hpp"

namespace glimac {
// Représente un cône ouvert discrétisé dont la base est centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
std::vector<ShapeVertex> tree_vertices(float size);
std::vector<ShapeVertex> bench_vertices(float size);
std::vector<ShapeVertex> boids_vertices(float size);
std::vector<ShapeVertex> character_vertices(float size);
std::vector<ShapeVertex> house_vertices(float size);
std::vector<ShapeVertex> floor_vertices(float size);

} // namespace glimac
