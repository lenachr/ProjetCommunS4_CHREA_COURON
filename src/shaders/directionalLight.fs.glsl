#version 330 core
in vec2 vTexCoords;
in vec3 vNormal_vs;
in vec3 vPosition_vs;

// out vec2 coord_textures;

out vec4 fFragColor;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
// uniform vec3 vPosition_vs;
uniform vec3 uLightDir_vs; // Notez le suffixe _vs sur la direction : cela indique que nous allons travailler dans le view space ; il faudra donc multiplier la direction de la lumière par la View Matrix avant de l'envoyer au shader.
uniform vec3 uLightIntensity;

vec3 blinnPhong(vec3 vNormal_vs, vec3 vPosition_vs, vec3 uLightIntensity, float uShininess, vec3 uKd, vec3 uKs){
    // Couleur=Li(Kd(wi ⋅ N) + Ks(halfVector ⋅ N) ^ shininess)
    vec3 N = normalize(vNormal_vs);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightDir_vs);
    vec3 Li = uLightIntensity;
    vec3 Kd = uKd;
    vec3 Ks = uKs;
    vec3 halfVector = (w0+wi)/2;
    float shininess = uShininess;
    //  vec3 color = Li * (Kd * max(dot(wi, N), 0.0) + Ks * pow(max(dot(halfVector, N), 0.0), shininess));
    vec3 color = Li * (Kd * max(dot(wi, N), 0.0) + Ks * pow(max(dot(halfVector, N), 0.0), shininess));
    // vec3 color = Li * (Kd * dot(wi, N) + pow(Ks * dot(halfVector, N), shininess));
    return color;

}


void main()
{
    // fFragColor = texture(uTexture, vTexCoords);
    vec3 color = blinnPhong(vNormal_vs, vPosition_vs, uLightIntensity, uShininess, uKd, uKs); 
    fFragColor= vec4 (color, 1.0f);
    // fFragColor = vec4(0.1f, 1.0f, 0.5f, 0.5f);
}