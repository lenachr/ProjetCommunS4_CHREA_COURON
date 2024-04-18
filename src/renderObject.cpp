#include "renderObject.hpp"

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

    // Lumière ambiante
    glm::vec3 lightPosition = glm::vec3(0, 80, 0);
    lightPosition           = glm::vec3(viewMatrix * glm::vec4(lightPosition, 1.0f)); // Transformation de la position par la matrice de vue

    // Set shader uniforms
    glUniformMatrix4fv(TreeProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(TreeProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(TreeProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // glUseProgram(TreeProgram.m_Program.id());
    // glUniform3fv(TreeProgram.uLightPos_vs, 1, glm::value_ptr(lightPosition));
    // glUniform3f(TreeProgram.uLightIntensity, 100.0f, 100.0f, 100.0f); // Intensité de la lumière blanche
    // glUniform3f(TreeProgram.uKd, 10.f, 10.f, 10.f);                   // Coefficients de réflexion diffuse
    // glUniform3f(TreeProgram.uKs, 10.f, 10.f, 10.f);                   // Coefficients de réflexion spéculaire
    // glUniform1f(TreeProgram.uShininess, 32.0f);                       // Exposant de brillance

    glUseProgram(TreeProgram.m_Program.id());
    glUniform3fv(TreeProgram.uLightPos_vs, 1, glm::value_ptr(lightPosition));
    glUniform3f(TreeProgram.uLightIntensity, 1.0f, 0.8f, 0.8f); // Intensité de la lumière blanche
    glUniform3f(TreeProgram.uKd, 0.5f, 0.5f, 0.5f);             // Coefficients de réflexion diffuse
    glUniform3f(TreeProgram.uKs, 0.5f, 0.5f, 0.5f);             // Coefficients de réflexion spéculaire
    glUniform1f(TreeProgram.uShininess, 32.0f);                 // Exposant de brillance

    // Bind VAO and draw
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

void renderObject(GLuint vao, GLsizei vertexCount, glm::vec3 translation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, TreeProgram& TreeProgram, GLuint textureID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    drawObject(vao, vertexCount, translation, viewMatrix, ProjMatrix, NormalMatrix, TreeProgram);
    glBindTexture(GL_TEXTURE_2D, 0);
}