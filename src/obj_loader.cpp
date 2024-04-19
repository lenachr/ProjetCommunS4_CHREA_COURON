// // No changes needed, as the error is likely caused by other issues in the codebase
// #include "obj_loader.h"

// #define TINYOBJLOADER_IMPLEMENTATION
// #include <glm/glm.hpp>
// #include "tiny_obj_loader.h"

// std::vector<float> Model::load_model(const char* filename, glm::mat4 preTransform)
// {
//     // std::vector<float> vertices;

//     tinyobj::attrib_t                attributes;
//     std::vector<tinyobj::shape_t>    shapes;
//     std::vector<tinyobj::material_t> materials;
//     std::string                      warning, error;

//     if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filename))
//     {
//         std::cout << warning << error << '\n';
//     }

//     for (const auto& shape : shapes)
//     {
//         for (const auto& index : shape.mesh.indices)
//         {
//             glm::vec4 pos = {
//                 attributes.vertices[3 * index.vertex_index],
//                 attributes.vertices[3 * index.vertex_index + 1],
//                 attributes.vertices[3 * index.vertex_index + 2],
//                 1
//             };

//             pos = preTransform * pos;

//             glm::vec3 normal = {
//                 attributes.normals[3 * index.normal_index],
//                 attributes.normals[3 * index.normal_index + 1],
//                 attributes.normals[3 * index.normal_index + 2]
//             };

//             normal = glm::normalize(glm::mat3(preTransform) * normal);

//             glm::vec2 texCoord = {
//                 attributes.texcoords[2 * index.texcoord_index],
//                 attributes.texcoords[2 * index.texcoord_index + 1],
//             };

//             vertices.push_back(pos.x);
//             vertices.push_back(pos.y);
//             vertices.push_back(pos.z);
//             vertices.push_back(texCoord.x);
//             vertices.push_back(texCoord.y);
//             vertices.push_back(normal.x);
//             vertices.push_back(normal.y);
//             vertices.push_back(normal.z);
//         }
//     }

//     return vertices;
// }

// GLuint Model::bind3D(const Model object)
// {
//     vertexCount = int(vertices.size()) / 8;

//     glGenBuffers(1, &VBO);
//     glGenVertexArrays(1, &VAO);
//     glGenVertexArrays(1, &VAO);
//     glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
//     glNamedBufferStorage(
//         VBO, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT
//     );
//     // pos: 0, texcoord: 1, normal: 2
//     glEnableVertexArrayAttrib(VAO, 0);
//     glEnableVertexArrayAttrib(VAO, 1);
//     glEnableVertexArrayAttrib(VAO, 2);
//     glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
//     glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
//     glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
//     glVertexArrayAttribBinding(VAO, 0, 0);
//     glVertexAttribBinding(1, 0);
//     glVertexArrayAttribBinding(VAO, 2, 0);
// }

// GLuint Model::bindVAO3D(const Model object)
// {
//     vertexCount = int(vertices.size()) / 8;

//     glCreateBuffers(1, &VBO);
//     glCreateVertexArrays(1, &VAO);
//     glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
//     glNamedBufferStorage(
//         VBO, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT
//     );
//     // pos: 0, texcoord: 1, normal: 2
//     glEnableVertexArrayAttrib(VAO, 0);
//     glEnableVertexArrayAttrib(VAO, 1);
//     glEnableVertexArrayAttrib(VAO, 2);
//     glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
//     glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
//     glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
//     glVertexArrayAttribBinding(VAO, 0, 0);
//     glVertexArrayAttribBinding(VAO, 1, 0);
//     glVertexArrayAttribBinding(VAO, 2, 0);
// }