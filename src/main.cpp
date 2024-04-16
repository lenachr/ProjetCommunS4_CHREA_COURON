// #include <glimac/>
#include <imgui.h>
#include <FreeflyCamera.hpp>
#include <glimac/common.hpp>
#include <glimac/cone_vertices.hpp>
#include <glimac/default_shader.hpp>
#include <glimac/object_vertices.hpp>
#include <glimac/sphere_vertices.hpp>
#include <vector>
#include "boid.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "p6/p6.h"
#include "renderObject.hpp"
#include "treeProgram.hpp"

// double lastMouseX        = 0.0;
// double lastMouseY        = 0.0;
// bool   isMouseButtonDown = false;

int main()
{
    auto ctx = p6::Context{{1280, 720, "Test objects"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Initilaisation des boids
    std::cout << "1\n";
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // initialisation des boids et des coefficients des règles de base
    std::vector<Boid> boids{};
    int               boids_number     = 1;
    float             alignement_coeff = 0.1f;
    float             cohesion_coeff   = 0.1f;
    float             separation_coeff = 0.01f;
    // Ajout dans le vector des position aléatoire pour les boids
    for (int i = 0; i < 50; i++)
    {
        boids.push_back(Boid{
            /*position = */ glm::vec3{p6::random::number(-50.f, 50.0f), p6::random::number(70.f, 100.f), p6::random::number(-50.f, 50.0f)},
            /*speed = */
            glm::vec3(p6::random::number(-0.5f, 0.1f), p6::random::number(-0.5f, 0.1f), p6::random::number(-0.5f, 0.1f)),
        });
    }

    TreeProgram TreeProgram{};

    img::Image textureTree      = p6::load_image_buffer("assets/textures/tree.jpg");
    img::Image textureSky       = p6::load_image_buffer("assets/textures/sky.jpg");
    img::Image textureWood      = p6::load_image_buffer("assets/textures/wood.jpg");
    img::Image textureHouse     = p6::load_image_buffer("assets/textures/house.jpg");
    img::Image textureCharacter = p6::load_image_buffer("assets/textures/character.jpg");
    img::Image textureFloor     = p6::load_image_buffer("assets/textures/floor.jpg");
    img::Image textureDress     = p6::load_image_buffer("assets/textures/dress.jpg");
    img::Image textureHead      = p6::load_image_buffer("assets/textures/tete.jpg");
    img::Image textureLegs      = p6::load_image_buffer("assets/textures/jambes.jpg");
    img::Image textureBoid      = p6::load_image_buffer("assets/textures/boid.jpg");

    std::vector<GLuint> textureID(50);
    // std::vector<GLuint> textureID;
    // textureID.resize(50);
    glGenTextures(50, textureID.data());

    // Configuration des textures
    bindTexture(textureID, 0, textureTree);
    bindTexture(textureID, 1, textureSky);
    bindTexture(textureID, 2, textureWood);
    bindTexture(textureID, 3, textureHouse);
    bindTexture(textureID, 4, textureCharacter);
    bindTexture(textureID, 5, textureFloor);
    bindTexture(textureID, 6, textureDress);
    bindTexture(textureID, 7, textureHead);
    bindTexture(textureID, 8, textureLegs);
    bindTexture(textureID, 9, textureBoid);

    // Initialisation caméra
    FreeflyCamera freeflyCamera;

    const std::vector<glimac::ShapeVertex> tree      = glimac::tree_vertices(2.f);
    const std::vector<glimac::ShapeVertex> bench     = glimac::bench_vertices(1.f);
    const std::vector<glimac::ShapeVertex> boid      = glimac::boids_vertices(3.f);
    const std::vector<glimac::ShapeVertex> character = glimac::character_vertices(4.f);
    const std::vector<glimac::ShapeVertex> house     = glimac::house_vertices(3.f);
    const std::vector<glimac::ShapeVertex> floor     = glimac::floor_vertices(100.f);
    const std::vector<glimac::ShapeVertex> cube      = glimac::cube_vertices(100.f, 100.f, 100.f);

    // Créer vao et vbo

    GLuint vboTree = bindVBO(tree);
    GLuint vaoTree = bindVAO(vboTree);

    GLuint vboBench = bindVBO(bench);
    GLuint vaoBench = bindVAO(vboBench);

    GLuint vboBoid = bindVBO(boid);
    GLuint vaoBoid = bindVAO(vboBoid);

    GLuint vboCharacter = bindVBO(character);
    GLuint vaoCharacter = bindVAO(vboCharacter);

    GLuint vboHouse = bindVBO(house);
    GLuint vaoHouse = bindVAO(vboHouse);

    GLuint vboFloor = bindVBO(floor);
    GLuint vaoFloor = bindVAO(vboFloor);

    GLuint vboCube = bindVBO(cube);
    GLuint vaoCube = bindVAO(vboCube);

    // Activer le test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    // Activer le blending pour permettre la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialiser les déplacements
    // Translation pour chaque objet
    glm::vec3 benchTranslation(10.0f, 0.0f, -5.0f);
    glm::vec3 boidTranslation(30.0f, 15.0f, 0.0f);
    glm::vec3 characterTranslation(0.0f, 0.0f, -10.0f);
    glm::vec3 houseTranslation(0.0f, 0.0f, 10.0f);

    const float minXTree = -40.0f;
    const float maxXTree = 40.0f;
    const float minZTree = -40.0f;
    const float maxZTree = 40.0f;

    std::vector<glm::vec3> treeTranslation;
    for (int i = 0; i < 10; i++)
    {
        float randXTree = minXTree + static_cast<float>(rand()) / (RAND_MAX / (maxXTree - minXTree));
        float randZTree = minZTree + static_cast<float>(rand()) / (RAND_MAX / (maxZTree - minZTree));
        treeTranslation.push_back(glm::vec3(randXTree, 2.0f, randZTree));
    }

    constexpr float characterDistance = 12.0f;

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // Interactions clavier
        if (ctx.key_is_pressed(GLFW_KEY_W))
        {
            freeflyCamera.moveFront(0.5);
        }
        if (ctx.key_is_pressed(GLFW_KEY_S))
        {
            freeflyCamera.moveFront(-0.5);
        }
        if (ctx.key_is_pressed(GLFW_KEY_A))
        {
            freeflyCamera.moveLeft(0.5);
        }
        if (ctx.key_is_pressed(GLFW_KEY_D))
        {
            freeflyCamera.moveLeft(-0.5);
        }
        if (ctx.key_is_pressed(GLFW_KEY_LEFT))
        {
            freeflyCamera.rotateLeft(50.f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_RIGHT))
        {
            freeflyCamera.rotateLeft(-50.f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_UP))
        {
            freeflyCamera.rotateUp(50.f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_DOWN))
        {
            freeflyCamera.rotateUp(-50.f);
        }

        // if (ctx.mouse_button_is_pressed(p6::Button::Left))
        // {
        //     if(button.position.x <0)
        //     // on regarde où se situe la souris
        //     double mouseX, mouseY;
        //     glfwGetCursorPos(ctx.get_window(), &mouseX, &mouseY);
        //     isMouseButtonDown = true;
        //     // glfwGetCursorPos(ctx.get_window(), &lastMouseX, &lastMouseY);
        // }
        // // Détecter quand le bouton gauche de la souris est relâché
        // if (!ctx.mouse_button_is_pressed(p6::Button::Left))
        // {
        //     isMouseButtonDown = false;
        // }

        // // Si le bouton gauche de la souris est enfoncé, mettre à jour la rotation de la caméra
        // if (isMouseButtonDown)
        // {
        //     double mouseX, mouseY;
        //     // glfwGetCursorPos(ctx.get_window(), &mouseX, &mouseY);

        //     double deltaX = mouseX - lastMouseX;
        //     double deltaY = mouseY - lastMouseY;

        //     // Ajouter les deltas à la rotation de la caméra
        //     freeflyCamera.rotateLeft(deltaX);
        //     freeflyCamera.rotateUp(deltaY);

        //     // Mettre à jour les dernières positions de la souris
        //     lastMouseX = mouseX;
        //     lastMouseY = mouseY;
        // }
        // else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        // {
        //     isMouseButtonDown = false;
        //     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Réafficher le curseur lorsque le clic est relâché
        // }

        glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        TreeProgram.m_Program.use();

        // Gestion des boids
        // Show a simple window
        ImGui::Begin("Choice of parameters");
        ImGui::SliderInt("Number of boids", &boids_number, 1, 50);
        ImGui::SliderFloat("Alignement distance", &alignement_coeff, 0, 0.3);
        ImGui::SliderFloat("Cohesion distance", &cohesion_coeff, 0, 0.3);
        ImGui::SliderFloat("Separation distance", &separation_coeff, 0, 0.1);
        ImGui::End();

        // Calcul viewMatrix

        glm::mat4 viewMatrix   = freeflyCamera.getViewMatrix();
        glm::mat3 TailleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(-0.25f, 0.f, -0.25f));
        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix     = viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -5.f));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        // MVMatrix               = glm::rotate(MVMatrix, ctx.time(), {1.f, 1.f, 1.f});
        MVMatrix = glm::rotate(MVMatrix, -1.57f, {0.f, 1.f, 0.f});

        // glUniform1f(uAlphaLocation, transparency);
        glUniformMatrix4fv(TreeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(TreeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(TreeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        // boucle qui affiche les boids
        for (int i = 0; i < boids_number; i++)
        {
            boids[i].draw(&ctx, vaoBoid, static_cast<GLsizei>(boid.size()), boidTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[9]);

            // renderObject(vaoBoid, static_cast<GLsizei>(boid.size()), boidTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[2]);
            boids[i].update(boids, alignement_coeff, cohesion_coeff, separation_coeff);
        }

        // Boucle pour les arbres
        for (int i = 0; i < 10; ++i)
        {
            renderObject(vaoTree, static_cast<GLsizei>(tree.size()), treeTranslation[i], viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[0]);
        }

        renderObject(vaoCube, static_cast<GLsizei>(cube.size()), glm::vec3{0.f, 25.f, 0.f}, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[1]);

        renderObject(vaoHouse, static_cast<GLsizei>(house.size()), houseTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[3]);

        glm::vec3 characterPosition = freeflyCamera.getPosition() + characterDistance * freeflyCamera.getFrontVector();

        // Pour être légèrement au dessus du personnage
        characterPosition.y -= characterPosition.y;
        renderObject(vaoCharacter, static_cast<GLsizei>(character.size()), characterPosition, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[4]);

        renderObject(vaoFloor, static_cast<GLsizei>(floor.size()), glm::vec3{0}, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[5]);

        renderObject(vaoBench, static_cast<GLsizei>(bench.size()), glm::vec3{0}, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[2]);

        // renderObject(vaoBoid, static_cast<GLsizei>(boid.size()), boidTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram, textureID[9]);

        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    glDeleteBuffers(1, &vboBench);
    glDeleteBuffers(1, &vboHouse);
    // glDeleteBuffers(1, &vboBoid);
    glDeleteBuffers(1, &vboCharacter);
    // glDeleteBuffers(1, &vboTree);
    glDeleteVertexArrays(1, &vaoBench);
    glDeleteVertexArrays(1, &vaoCube);
    glDeleteVertexArrays(1, &vaoBoid);
    glDeleteVertexArrays(1, &vaoFloor);
    glDeleteVertexArrays(1, &vaoCharacter);
    glDeleteVertexArrays(1, &vaoTree);
    glDeleteTextures(static_cast<GLsizei>(textureID.size()), textureID.data());
}