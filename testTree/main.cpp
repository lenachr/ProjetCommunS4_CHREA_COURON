// #include <glimac/>
#include <FreeflyCamera.hpp>
#include <glimac/common.hpp>
#include <glimac/cone_vertices.hpp>
#include <glimac/default_shader.hpp>
#include <glimac/object_vertices.hpp>
#include <glimac/sphere_vertices.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "p6/p6.h"

// Structure représentant le programme GPU pour dessiner les arbres
struct TreeProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTreeTexture;

    TreeProgram()
        : m_Program{p6::load_shader("shaders/3D.vs.glsl", "shaders/tex3D.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uTreeTexture  = glGetUniformLocation(m_Program.id(), "uTexture");
    }
};

// Structure représentant le programme GPU pour dessiner le cube
struct CubeProgram {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTreeTexture;

    CubeProgram()
        : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/normals.fs.glsl"))

    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uTreeTexture  = glGetUniformLocation(m_Program.id(), "uTexture");
    }
};

GLuint bindVBO(const std::vector<glimac::ShapeVertex> object)
{
    // Création d'un seul VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding d'un VBO sur sa cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glimac::ShapeVertex) * object.size(), object.data(), GL_STATIC_DRAW);

    // Débinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

GLuint bindVAO(GLuint vbo)
{
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

    return vao;
}

// bind texture
void bindTexture(std::vector<GLuint> textureID, int i, img::Image& texture)
{
    glBindTexture(GL_TEXTURE_2D, textureID[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data());
    // Configurations des filtres de texture et débindage de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

// Function to draw each object with translation
void drawObject(GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, TreeProgram& TreeProgram)
{
    // Calculate model matrix with translation
    glm::mat4 MVMatrix = viewMatrix * glm::translate(glm::mat4(1.0f), translation);
    NormalMatrix       = glm::transpose(glm::inverse(MVMatrix));

    // Set shader uniforms
    glUniformMatrix4fv(TreeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(TreeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(TreeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // Bind VAO and draw
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

int main()
{
    auto ctx = p6::Context{{1280, 720, "Test objects"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // const p6::Shader shader = p6::load_shader(
    //     // shaders exo01
    //     "shaders/3D.vs.glsl",
    //     "shaders/normals.fs.glsl"
    // );
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

    std::vector<GLuint> textureID(50);
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

    // Initialisation caméra
    FreeflyCamera freeflyCamera;

    const std::vector<glimac::ShapeVertex> tree      = glimac::tree_vertices(2.f);
    const std::vector<glimac::ShapeVertex> bench     = glimac::bench_vertices(1.f);
    const std::vector<glimac::ShapeVertex> boid      = glimac::boids_vertices(1.f);
    const std::vector<glimac::ShapeVertex> character = glimac::character_vertices(4.f);
    const std::vector<glimac::ShapeVertex> house     = glimac::house_vertices(3.f);
    const std::vector<glimac::ShapeVertex> floor     = glimac::floor_vertices(50.f);
    const std::vector<glimac::ShapeVertex> cube      = glimac::cube_vertices(50.f, 50.f, 50.f);

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
    glm::vec3 boidTranslation(0.0f, 15.0f, 0.0f);
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
        TreeProgram.m_Program.use();

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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);

        drawObject(vaoBoid, static_cast<GLsizei>(boid.size()), boidTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);

        // boucle qui affiche 10 boids
        for (int i = 0; i < 10; ++i)
        {
            // Translation vector for the current tree
            // glm::vec3 treeTranslation(randX, randY, randZ);
            drawObject(vaoTree, static_cast<GLsizei>(tree.size()), treeTranslation[i], viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID[1]);
        drawObject(vaoCube, static_cast<GLsizei>(cube.size()), glm::vec3{0.f, 25.f, 0.f}, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID[2]);
        drawObject(vaoBench, static_cast<GLsizei>(bench.size()), benchTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID[3]);
        drawObject(vaoHouse, static_cast<GLsizei>(house.size()), houseTranslation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID[4]);
        // Mettre à jour la position du personnage en fonction des mouvements de la caméra
        glm::vec3 characterPosition = freeflyCamera.getPosition() + characterDistance * freeflyCamera.getFrontVector();
        // Pour être légèrement au dessus du personnage
        characterPosition.y -= characterPosition.y;
        drawObject(vaoCharacter, static_cast<GLsizei>(character.size()), characterPosition, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID[5]);
        drawObject(vaoFloor, static_cast<GLsizei>(floor.size()), glm::vec3{0}, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
        glBindTexture(GL_TEXTURE_2D, 0);

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