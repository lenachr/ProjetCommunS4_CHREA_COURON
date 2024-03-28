#version 330 core

in vec2 vTexCoords;

// out vec2 coord_textures;

out vec4 fFragColor;
uniform sampler2D uTexture;



void main()
{
    fFragColor = texture(uTexture, vTexCoords);
    // fFragColor = vec4(0.1f, 1.0f, 0.5f, 1.);

}