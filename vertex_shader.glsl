#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;
in vec4 normal;         
in vec2 texCoord;       

out vec4 fView;         // Wektor do obserwatora
out vec4 fVertex;       // Wspolrzedne wierzcholka
out vec4 fNormal;       // Wektor normalny
out vec2 fTexCoord;     // Wspolrzedne teksturowania

void main(void) {
    fView       = normalize(vec4(0.0f, 0.0f, 0.0f, 1.0f) - V * M * vertex);
    fVertex     = vertex;
    fNormal     = normal;
    fTexCoord   = texCoord;
    
    gl_Position = P * V * M * vertex;
}