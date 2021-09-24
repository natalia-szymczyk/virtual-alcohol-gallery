#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


layout (location=0) in vec3 vertex;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 icNorm;
out vec3 icFragPos;

void main()
{
    vec4 vert = vec4(vertex, 1);
    TexCoord = texCoord;
    icNorm = mat3(transpose(inverse(M))) * normal;
    icFragPos = vec3(M * vec4(vertex, 1));

    gl_Position = P * V * M * vert;
}
