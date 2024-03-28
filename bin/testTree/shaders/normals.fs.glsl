#version 330 core

in vec3 vColor;
uniform float uAlpha; // pour la transparence
out vec4 fFragColor;

mat3 rotate(float a){
  return mat3(
        vec3(cos(a), sin(a), 0),
        vec3(-sin(a), cos(a), 0),
        vec3(0, 0, 1)
    );
}

void main()
{
    fFragColor = vec4(normalize(vColor), 1.);
    // fFragColor = vec4(vColor, uAlpha);
    // fFragColor = vec4(vColor, 0.5);

    // fFragColor = vec4(0.0, 1.0, 0.8, 1.);

}