// #include <glimac/>
#include <imgui.h>
#include <FreeflyCamera.hpp>
#include <glimac/common.hpp>
#include <glimac/cone_vertices.hpp>
#include <glimac/default_shader.hpp>
#include <glimac/object_vertices.hpp>
#include <glimac/sphere_vertices.hpp>
#include <iostream>
#include <vector>
#include "boid.hpp"
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "ObjectProgram.hpp"
#include "RandomGenerator.hpp"
#include "doctest/doctest.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "model.hpp"
#include "p6/p6.h"
#include "renderObject.hpp"

// double lastMouseX        = 0.0;
// double lastMouseY        = 0.0;
bool mousePressed           = false;
bool collisionDetectedUp    = false;
bool collisionDetectedDown  = false;
bool collisionDetectedLeft  = false;
bool collisionDetectedRight = false;

void collisions(const auto& ctx, FreeflyCamera& freeflyCamera, bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, float move)
{
    if (upPressed)
    {
        collisionDetectedUp = true;
        if (ctx->key_is_pressed(GLFW_KEY_W))
        {
            freeflyCamera.moveFront(-move);
        }
    }
    else
    {
        collisionDetectedUp = false;
    }
    if (downPressed)
    {
        collisionDetectedDown = true;
        if (ctx->key_is_pressed(GLFW_KEY_S))
        {
            freeflyCamera.moveFront(move);
        }
    }
    else
    {
        collisionDetectedDown = false;
    }
    if (leftPressed)
    {
        collisionDetectedLeft = true;
        if (ctx->key_is_pressed(GLFW_KEY_A))
        {
            freeflyCamera.moveLeft(-move);
        }
    }
    else
    {
        collisionDetectedLeft = false;
    }
    if (rightPressed)
    {
        collisionDetectedRight = true;
        if (ctx->key_is_pressed(GLFW_KEY_D))
        {
            freeflyCamera.moveLeft(move);
        }
    }
    else
    {
        collisionDetectedRight = false;
    }
}

float timeStart = static_cast<int>(glfwGetTime() * 1000.0);

// Fonction pour détecter la collision entre le personnage et un arbre
bool detectCollision(const glm::vec3& characterPosition, const glm::vec3& treeTranslation, float characterRadius, float treeRadius)
{
    // Calculer la distance entre le personnage et l'arbre
    float distance = glm::length(characterPosition - treeTranslation);
    // Si la distance est inférieure à la somme des rayons du personnage et de l'arbre, il y a collision
    return distance < (characterRadius + treeRadius);
}

int main()
{
    // Initialisation de GLFW
    if (!glfwInit())
    {
        std::cerr << "Erreur lors de l'initialisation de GLFW" << std::endl;
        return -1;
    }

    auto ctx = p6::Context{{1280, 720, "Test objects"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // le temps actuel

    // Initialisation du générateur de nombres aléatoires
    srand(static_cast<unsigned>(time(nullptr)));

    // Nombre d'arbres
    int trees_number = 50;

    // Initialisation des boids
    std::cout << "1\n";
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // initialisation des boids et des coefficients des règles de base
    std::vector<Boid> boids{};
    int               boids_number     = 20;
    float             alignement_coeff = 5.f;
    float             cohesion_coeff   = 5.f;
    float             separation_coeff = 5.f;
    int               lod              = 1;

    std::string textures[100]; // Déclaration du tableau de textures

    // Remplissage du tableau avec les sorties de chooseBoidTexture()
    for (int i = 0; i < 100; ++i)
    {
        textures[i] = chooseBoidTexture();
    }
    // Ajout dans le vector des position aléatoire pour les boids
    float bas  = 0.0f;
    float haut = 0.0f;
    // for (int i = 0; i < 50; i++)
    for (int i = 0; i < 100; i++)
    {
        double verticalSpeed = chooseVerticalBoidSpeed();
        if (verticalSpeed < 0)
        {
            bas++;
        }
        else
        {
            haut++;
        }
        boids.push_back(Boid{
            // /*position = */ glm::vec3{p6::random::number(-100.f, 100.0f), p6::random::number(70.f, 100.f), p6::random::number(-100.f, 100.0f)},
            /*position = */ glm::vec3{p6::random::number(-45.f, 45.0f), p6::random::number(50.f, 90.f), p6::random::number(-90.f, 90.0f)},
            // /*speed = */ glm::vec3(p6::random::number(-0.5f, 0.5f), p6::random::number(-0.5f, 0.5f), p6::random::number(-0.5f, 0.5f)),
            /*speed = */ glm::vec3(p6::random::number(-0.5f, 0.5f), p6::random::number(-0.5f, 0.5f), verticalSpeed),
        });
    }
    // Print des statistiques direction verticale
    // std::cout << "Bas : " << bas / 50 * 100 << "%"
    //   << "\n";
    // std::cout << "Haut : " << haut / 50 * 100 << "%"
    //   << "\n";

    ObjectProgram ObjectProgram{};

    img::Image textureTree      = p6::load_image_buffer("assets/textures/tree.jpg");
    img::Image textureSky       = p6::load_image_buffer("assets/textures/sky.jpg");
    img::Image textureWood      = p6::load_image_buffer("assets/textures/wood.jpg");
    img::Image textureHouse     = p6::load_image_buffer("assets/textures/house.jpg");
    img::Image textureCharacter = p6::load_image_buffer("assets/textures/character.jpg");
    img::Image textureFloor     = p6::load_image_buffer("assets/textures/floor02.jpg");
    // img::Image textureDress     = p6::load_image_buffer("assets/textures/dress.jpg");
    // img::Image textureHead      = p6::load_image_buffer("assets/textures/tete.jpg");
    // img::Image textureLegs      = p6::load_image_buffer("assets/textures/jambes.jpg");
    img::Image textureBoid01   = p6::load_image_buffer("assets/textures/boid.jpg");
    img::Image textureBoid02   = p6::load_image_buffer("assets/textures/boid1.png");
    img::Image textureModels3D = p6::load_image_buffer("assets/textures/Colors.png");

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
    // bindTexture(textureID, 6, textureDress);
    // bindTexture(textureID, 7, textureHead);
    // bindTexture(textureID, 8, textureLegs);
    bindTexture(textureID, 9, textureBoid01);
    bindTexture(textureID, 10, textureBoid02);
    bindTexture(textureID, 11, textureModels3D);

    // Initialisation caméra
    FreeflyCamera freeflyCamera;

    const std::vector<glimac::ShapeVertex> tree      = glimac::tree_vertices(2.f);
    const std::vector<glimac::ShapeVertex> bench     = glimac::bench_vertices(1.f);
    const std::vector<glimac::ShapeVertex> boid      = glimac::boids_vertices(3.f);
    const std::vector<glimac::ShapeVertex> character = glimac::character_vertices(4.f);
    const std::vector<glimac::ShapeVertex> house     = glimac::house_vertices(3.f);
    const std::vector<glimac::ShapeVertex> floor     = glimac::floor_vertices(100.f);
    const std::vector<glimac::ShapeVertex> cube      = glimac::cube_vertices(100.f, 100.f, 100.f);
    const std::vector<glimac::ShapeVertex> boidCube  = glimac::cube_vertices(2.f, 2.f, 0.5f);

    // Import modèles 3D
    Model Carl;
    Carl.load_model("assets/models/carl_doug.obj");

    Model clouds;
    clouds.load_model("assets/models/clouds2.obj");

    Model House;
    House.load_model("assets/models/house.obj");

    Model rocks;
    rocks.load_model("assets/models/rocks.obj");

    Model tree1;
    tree1.load_model("assets/models/tree1.obj");

    Model tree2;
    tree2.load_model("assets/models/tree2.obj");

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

    GLuint vboBoidCube = bindVBO(boidCube);
    GLuint vaoBoidCube = bindVAO(vboBoidCube);

    GLuint vboCarl = bindVBO(Carl.vertices);
    GLuint vaoCarl = bindVAO(vboCarl);

    GLuint vboClouds = bindVBO(clouds.vertices);
    GLuint vaoClouds = bindVAO(vboClouds);

    GLuint vboHouse3D = bindVBO(House.vertices);
    GLuint vaoHouse3D = bindVAO(vboHouse3D);

    GLuint vboRocks = bindVBO(rocks.vertices);
    GLuint vaoRocks = bindVAO(vboRocks);

    GLuint vboTree1 = bindVBO(tree1.vertices);
    GLuint vaoTree1 = bindVAO(vboTree1);

    GLuint vboTree2 = bindVBO(tree2.vertices);
    GLuint vaoTree2 = bindVAO(vboTree2);

    // Activer le test de profondeur du GPU
    glEnable(GL_DEPTH_TEST);

    // Activer le blending pour permettre la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialiser les déplacements
    // Translation pour chaque objet
    glm::vec3 benchTranslation(-40.0f, 1.0f, -80.0f);
    glm::vec3 cloudsTranslation(30.0f, 70.f, 0.);

    const int              nbHouses = 3; // Nombre de maisons à placer
    std::vector<glm::vec3> houseTranslation;
    for (int i = 0; i < nbHouses; i++)
    {
        double houseTranslationX = placeHouses();
        double houseTranslationZ = placeHouses();
        houseTranslation.push_back(glm::vec3(houseTranslationX, 0.0f, houseTranslationZ));
    }

    std::vector<glm::vec3> treeTranslation;
    std::vector<int>       selectedTree;

    for (int i = 0; i < trees_number; i++)
    {
        float randXTree = generateRandomPositionTree();

        float randZTree = generateRandomPositionTree();

        treeTranslation.push_back(glm::vec3(randXTree, 0.0f, randZTree));

        selectedTree.push_back(selectTree());
    }

    const int numRocks = 10;
    for (int i = 0; i < numRocks; ++i)
    {
        double color = chooseRockColor();
        // std::cout << "Rocher " << i + 1 << " : Couleur -> " << color << std::endl;
    }
    constexpr float characterDistance = 10.0f;

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // Interactions clavier/souris
        bool upPressed    = false;
        bool downPressed  = false;
        bool leftPressed  = false;
        bool rightPressed = false;

        if (ctx.key_is_pressed(GLFW_KEY_W))
        {
            if (collisionDetectedUp)
            {
                return;
            }
            freeflyCamera.moveFront(0.5);
            upPressed = true;
        }
        else
        {
            upPressed = false;
        }
        if (ctx.key_is_pressed(GLFW_KEY_S))
        {
            if (collisionDetectedDown)
            {
                return;
            }
            freeflyCamera.moveFront(-0.5);
            downPressed = true;
        }
        else
        {
            downPressed = false;
        }
        if (ctx.key_is_pressed(GLFW_KEY_A))
        {
            if (collisionDetectedLeft)
            {
                return;
            }
            freeflyCamera.moveLeft(0.5);
            leftPressed = true;
            // }
        }
        else
        {
            leftPressed = false;
        }
        if (ctx.key_is_pressed(GLFW_KEY_D))
        {
            if (collisionDetectedRight)
            {
                return;
            }
            if (!collisionDetectedRight)
            {
                freeflyCamera.moveLeft(-0.5);
                rightPressed = true;
            }
        }
        else
        {
            rightPressed = false;
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
        // }

        ctx.mouse_pressed = [&](p6::MouseButton button) {
            mousePressed = true;

            ctx.mouse_dragged = [&](p6::MouseDrag drag) {
                freeflyCamera.rotateLeft(drag.delta.x * -5000.f);
                freeflyCamera.rotateUp(drag.delta.y * 5000.f);
            };

            ctx.mouse_released = [&](p6::MouseButton button) {
                mousePressed       = false;
                ctx.mouse_dragged  = nullptr;
                ctx.mouse_released = nullptr;
            };
        };

        glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ObjectProgram.m_Program.use();

        // Gestion des boids
        // Show a simple window
        ImGui::Begin("Choice of parameters");
        ImGui::SliderInt("Number of boids", &boids_number, 1, 100);
        ImGui::SliderFloat("Alignement distance", &alignement_coeff, 0, 10);
        ImGui::SliderFloat("Cohesion distance", &cohesion_coeff, 0, 10);
        ImGui::SliderFloat("Separation distance", &separation_coeff, 0, 50);
        // Choix entre 3 LOD's
        ImGui::SliderInt("LOD", &lod, 0, 2);
        ImGui::End();

        // Mise à jour position personnage
        glm::vec3 characterPosition = freeflyCamera.getPosition() + characterDistance * freeflyCamera.getFrontVector();

        // Pour être légèrement au dessus du personnage
        characterPosition.y -= characterPosition.y;

        // Calcul viewMatrix

        glm::mat4 viewMatrix   = freeflyCamera.getViewMatrix();
        glm::mat3 TailleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(-0.25f, 0.f, -0.25f));
        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 500.f);
        glm::mat4 MVMatrix     = viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -5.f));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        MVMatrix = glm::rotate(MVMatrix, -1.57f, {0.f, 1.f, 0.f});

        // boucle qui affiche les boids
        float n = 0.f;
        float m = 0.f;
        for (int i = 0; i < boids_number; i++)
        {
            if (lod == 0)
            {
                if (textures[i] == "Texture 1")
                {
                    boids[i].draw(vaoBoidCube, static_cast<GLsizei>(boid.size()), glm::vec3{1.f}, 1.57f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[9]);
                }
                else
                {
                    boids[i].draw(vaoBoidCube, static_cast<GLsizei>(boid.size()), glm::vec3{1.f}, 1.57f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[10]);
                }
            }
            if (lod == 1)
            {
                if (textures[i] == "Texture 1")
                {
                    boids[i].draw(vaoBoid, static_cast<GLsizei>(boid.size()), glm::vec3{1.f}, 1.57f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[9]);
                }
                else
                {
                    boids[i].draw(vaoBoid, static_cast<GLsizei>(boid.size()), glm::vec3{1.f}, 1.57f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[10]);
                }
            }
            if (lod == 2)
            {
                if (textures[i] == "Texture 1")
                {
                    boids[i].draw(vaoBoid, static_cast<GLsizei>(boid.size()), glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[9]);
                }
                else
                {
                    boids[i].draw(vaoBoid, static_cast<GLsizei>(boid.size()), glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[10]);
                }
            }

            if (boidFalling(timeStart))
            {
                boids[i].falling = true;
                if (boid[i].position.y <= 0.f)
                {
                    // Supprimer ce boid
                    // boids.erase(boids.begin() + i);
                    // boids_number--;
                    // i--;
                }
            }

            boids[i].update(boids, alignement_coeff, cohesion_coeff, separation_coeff);
        }

        // Boucle pour les arbres
        for (int i = 0; i < trees_number; ++i)
        {
            // renderObject(vaoTree, static_cast<GLsizei>(tree.size()), treeTranslation[i], viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[0]);
            if (selectedTree[i] == 1)
            {
                renderObject(vaoTree2, static_cast<GLsizei>(tree2.vertices.size()), treeTranslation[i], glm::vec3{18.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[11]);
            }
            else
            {
                renderObject(vaoTree1, static_cast<GLsizei>(tree1.vertices.size()), treeTranslation[i], glm::vec3{18.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[11]);
            }
        }

        renderObject(vaoCube, static_cast<GLsizei>(cube.size()), glm::vec3{0.f, 25.f, 0.f}, glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[1]);

        // std::cout << "Placements des maisons sur la carte : " << std::endl;
        // for (int i = 0; i < nbHouses; ++i)
        // {
        //     // renderObject(
        //     //     vaoHouse, static_cast<GLsizei>(house.size()), houseTranslation[i], viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[3]
        //     // );
        //     renderObject(
        //         vaoHouse3D, static_cast<GLsizei>(House.vertices.size()), houseTranslation[i], glm::vec3{4.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[11]
        //     );
        //     // cout << "Maison " << i + 1 << " : Position -> " << houseTranslation << endl;
        // }

        // Vérifier la collision avec chaque maison
        for (int i = 0; i < nbHouses; ++i)
        {
            for (int j = 0; j < nbHouses; ++j)
            {
                if (detectCollision(characterPosition, houseTranslation[j] + 3.f, 2, 12))
                {
                    collisions(&ctx, freeflyCamera, upPressed, downPressed, leftPressed, rightPressed, 0.3f);
                }
                else
                {
                    collisionDetectedUp    = false;
                    collisionDetectedDown  = false;
                    collisionDetectedLeft  = false;
                    collisionDetectedRight = false;
                }
            }
        }

        // Collisions arbre
        for (int i = 0; i < trees_number; i++)
        {
            // Vérifier la collision avec chaque arbre
            for (int j = 0; j < trees_number; ++j)
            {
                if (detectCollision(characterPosition, treeTranslation[j], 2, 3))
                {
                    collisions(&ctx, freeflyCamera, upPressed, downPressed, leftPressed, rightPressed, 0.03f);
                }
                else
                {
                    collisionDetectedUp    = false;
                    collisionDetectedDown  = false;
                    collisionDetectedLeft  = false;
                    collisionDetectedRight = false;
                }
            }
        }

        renderObject(vaoCarl, static_cast<GLsizei>(Carl.vertices.size()), characterPosition, glm::vec3{2.5f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[11]);

        renderObject(vaoFloor, static_cast<GLsizei>(floor.size()), glm::vec3{0}, glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[5]);

        renderObject(vaoBench, static_cast<GLsizei>(bench.size()), benchTranslation, glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[2]);

        if (detectCollision(characterPosition, benchTranslation, 2, 2))
        {
            collisions(&ctx, freeflyCamera, upPressed, downPressed, leftPressed, rightPressed, 0.3f);
        }
        else
        {
            collisionDetectedUp    = false;
            collisionDetectedDown  = false;
            collisionDetectedLeft  = false;
            collisionDetectedRight = false;
        }

        renderObject(vaoClouds, static_cast<GLsizei>(clouds.vertices.size()), cloudsTranslation, glm::vec3{10.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[11]);

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
    glDeleteVertexArrays(1, &vaoTree1);
    glDeleteVertexArrays(1, &vaoTree2);
    glDeleteVertexArrays(1, &vaoCarl);
    glDeleteVertexArrays(1, &vaoClouds);
    glDeleteVertexArrays(1, &vaoRocks);
    glDeleteVertexArrays(1, &vaoHouse3D);

    glDeleteTextures(static_cast<GLsizei>(textureID.size()), textureID.data());
}