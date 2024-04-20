#include "model.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "glimac/common.hpp"
#include "tiny_obj_loader.h"

void Model::load_model(const char* filename)
{
    tinyobj::attrib_t                attributes;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      warning, error;

    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filename))
    {
        std::cout << warning << error << '\n';
    }

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            glm::vec3 pos = {
                attributes.vertices[3 * index.vertex_index],
                attributes.vertices[3 * index.vertex_index + 1],
                attributes.vertices[3 * index.vertex_index + 2],
            };

            glm::vec3 normal = {
                attributes.normals[3 * index.normal_index],
                attributes.normals[3 * index.normal_index + 1],
                attributes.normals[3 * index.normal_index + 2]
            };

            glm::vec2 texCoord = {
                attributes.texcoords[2 * index.texcoord_index],
                attributes.texcoords[2 * index.texcoord_index + 1],
            };

            glimac::ShapeVertex vertex;
            vertex.position  = glm::vec3(pos);
            vertex.normal    = normal;
            vertex.texCoords = texCoord;

            vertices.push_back(vertex);
        }
    }

    vertexCount = int(vertices.size());
}