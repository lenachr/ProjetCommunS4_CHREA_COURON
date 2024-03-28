// #include <glimac/>
#include <FreeflyCamera.hpp>
#include <glimac/common.hpp>
#include <glimac/cone_vertices.hpp>
#include <glimac/cube_vertices.hpp>
#include <glimac/default_shader.hpp>
#include <glimac/sphere_vertices.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "p6/p6.h"

// https://julesfouchy.github.io/Learn--OpenGL/TP6/les-fonctions-sph%C3%A8re-et-cone

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP6 EX1"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    const p6::Shader shader = p6::load_shader(
        // shaders exo01
        "shaders/3D.vs.glsl",
        "shaders/normals.fs.glsl"
    );

    // Initialisation caméra
    FreeflyCamera freeflyCamera;

    const std::vector<glimac::ShapeVertex> cube = glimac::cube_vertices(2.f, 2.f, 2.f);

    // Création d'un seul VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding d'un VBO sur sa cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glimac::ShapeVertex) * cube.size(), cube.data(), GL_STATIC_DRAW);

    // Débinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Création d'un vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Binding du VAO
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Spécification des attributs de vertex
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Débinder le VAO
    glBindVertexArray(0);

    // Récupération des variables uniformes des shaders
    GLint uMVPMatrix     = glGetUniformLocation(shader.id(), "uMVPMatrix");
    GLint uMVMatrix      = glGetUniformLocation(shader.id(), "uMVMatrix");
    GLint uNormalMatrix  = glGetUniformLocation(shader.id(), "uNormalMatrix");
    GLint uAlphaLocation = glGetUniformLocation(shader.id(), "uAlpha");

    // Définir le niveau de transparence (par exemple, 0.5 pour une transparence à moitié)
    float transparency = 0.5f;

    // Activer le test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    // Activer le blending pour permettre la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // Interactions clavier
        if (ctx.key_is_pressed(GLFW_KEY_W))
        {
            freeflyCamera.moveFront(0.1);
        }
        if (ctx.key_is_pressed(GLFW_KEY_S))
        {
            freeflyCamera.moveFront(-0.1);
        }
        if (ctx.key_is_pressed(GLFW_KEY_A))
        {
            freeflyCamera.moveLeft(0.05);
        }
        if (ctx.key_is_pressed(GLFW_KEY_D))
        {
            freeflyCamera.moveLeft(-0.05);
        }
        if (ctx.key_is_pressed(GLFW_KEY_LEFT))
        {
            freeflyCamera.rotateLeft(20.f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_RIGHT))
        {
            freeflyCamera.rotateLeft(-20.f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_UP))
        {
            freeflyCamera.rotateUp(20.f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_DOWN))
        {
            freeflyCamera.rotateUp(-20.f);
        }

        glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        // Calcul viewMatrix

        glm::mat4 viewMatrix   = freeflyCamera.getViewMatrix();
        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix     = viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -5.f));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        // MVMatrix               = glm::rotate(MVMatrix, ctx.time(), {1.f, 1.f, 1.f});
        // MVMatrix = glm::rotate(MVMatrix, -1.57f, {0.f, 1.f, 0.f});
        MVMatrix = glm::scale(MVMatrix, {1.f, 1.5f, 1.f});

        glUniform1f(uAlphaLocation, transparency);
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(cube.size()));
        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}