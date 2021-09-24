#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;         // Wspolrzedne wierzcholka
in vec4 normal;         // Wektor normalny
in vec2 texCoord;       // Wspolrzedne teksturowania

out vec4 fViewDir;
out vec4 fVertex;
out vec4 fNormal;
out vec2 fTexCoord;

void main(void) {
    fViewDir    = normalize(vec4(0.0f, 0.0f, 0.0f, 1.0f) - V * M * vertex);       // Wektor do obserwatora (w przestrzeni oka)
    fVertex     = vertex;
    fNormal     = normal;
    fTexCoord   = texCoord;
    
    gl_Position = P * V * M * vertex;
}