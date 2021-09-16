#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
//tu
uniform vec4 lpos1;
uniform vec4 lpos2;
uniform vec4 lpos3;
uniform vec4 lpos4;


uniform vec4 lightDir=vec4(0,0,1,0);

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wsp�rz�dne teksturowania


//Zmienne interpolowane
//out vec2 i_tc;
//out float i_nl;
out vec4 n;
out vec4 v;
out vec4 l1;
out vec4 l2;
out vec4 l3;
out vec4 l4;
out vec2 iTexCoord0;

void main(void) {
    //gl_Position=P*V*M*vertex;

    //mat4 G=mat4(inverse(transpose(mat3(M))));
    //vec4 n=normalize(V*G*normal);

    //i_nl=clamp(dot(n,lightDir),0,1);
    //i_tc=texCoord;

    l1 = normalize(V*lpos1 - V*M*vertex);
    l2 = normalize(V*lpos2 - V*M*vertex);
    l3 = normalize(V*lpos3 - V*M*vertex);
    l4 = normalize(V*lpos4 - V*M*vertex);
    
    n = normalize(V*M*normal);
    v = normalize(vec4(0,0,0,1)-V*M*vertex);

    iTexCoord0=texCoord;

    gl_Position=P*V*M*vertex;
}
