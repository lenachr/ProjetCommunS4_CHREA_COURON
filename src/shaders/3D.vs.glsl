#version 330 core

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position du sommet
layout(location = 1) in vec3 aVertexNormal; // Normale du sommet
layout(location = 2) in vec2 aVertexTexCoords; // Coordonnées de texture du sommet

// Matrices de transformation reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Sorties du shader
out vec3 vPosition_vs; // Position du sommet transformée dans l'espace View (vs)
out vec3 vNormal_vs; // Normale du sommet transformée dans l'espace View (vs)
out vec2 vTexCoords; // Coordonnées de texture du sommet
out vec3 vColor;

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1.);
    vec4 vertexNormal = vec4(aVertexNormal, 0.);

    vColor = (vertexNormal.xyz); 
    vTexCoords = aVertexTexCoords;
    vTexCoords = vec2(aVertexTexCoords.x, 1.0 - aVertexTexCoords.y);
    // vColor = (vertexNormal.xyz); 
    // vColor = vec3(1.f); 

    // Calcul des valeurs de sortie
    // vPosition_vs = vec3(uMVMatrix * vertexPosition);
    // vNormal_vs = vec3(uNormalMatrix * vertexNormal);
    vPosition_vs = vec3(uMVMatrix * vertexPosition);
    vNormal_vs = vec3(uNormalMatrix * vertexNormal);
    // vTexCoords = aVertexTexCoords;

    // Calcul de la position projetée
    // gl_Position = uMVPMatrix * vertexPosition;
    gl_Position = uMVPMatrix * vertexPosition;
}