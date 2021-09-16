#version 330


uniform sampler2D tex;
uniform vec3 lightColor = vec3(1, 1, 1);
//first light source position in world coord
uniform vec3 lightPos1 = vec3(10, 5, -18);
//second light source position in world coord
uniform vec3 lightPos2 = vec3(10, 5, -6);

in vec2 TexCoord;
in vec3 icNorm;
in vec3 icFragPos;

out vec4 pxColor;

void main()
{
    //light that is already present on the scence
    vec4 ambient = vec4(lightColor * 0.1, 1);

    vec3 norm = normalize(icNorm);

    vec3 lightDir1 = normalize(lightPos1 - icFragPos);
    vec4 diffuse1 = vec4( max(dot(norm, lightDir1), 0) * lightColor, 1 );

    vec3 lightDir2 = normalize(lightPos2 - icFragPos);
    vec4 diffuse2 = vec4( max(dot(norm, lightDir2), 0) * lightColor, 1 );

	pxColor = texture(tex, TexCoord) * ( ambient + ((diffuse1 + diffuse2) * 0.8) );
}
