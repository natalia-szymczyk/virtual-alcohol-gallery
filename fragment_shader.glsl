#version 330


uniform sampler2D tex;
uniform vec3 lightColor = vec3(0.9, 0.9, 0.9);
uniform vec3 lightPos1 = vec3(100, 100, 100);
uniform vec3 lightPos2 = vec3(100, 100, -100);
uniform vec3 lightPos3 = vec3(-100, 100, 100);
uniform vec3 lightPos4 = vec3(-100, 100, -100);
uniform vec3 lightPos5 = vec3(0, -10, 0);

in vec2 TexCoord;
in vec3 icNorm;
in vec3 icFragPos;

out vec4 pxColor;

void main()
{
    //light that is already present on the scence
    vec4 ambient = vec4(lightColor * 0.1, 1);

    vec3 norm = normalize(icNorm);

    vec3 lightDir1 = normalize(vec3(-10, 0, -10));
    vec4 diffuse1 = vec4( max(dot(norm, lightDir1), 0) * lightColor, 1 );
    
    vec3 lightDir2 = normalize(vec3(-10, 0, 10));
    vec4 diffuse2 = vec4( max(dot(norm, lightDir2), 0) * lightColor, 1 );

    vec3 lightDir3 = normalize(vec3(10, 0, -10));
    vec4 diffuse3 = vec4( max(dot(norm, lightDir3), 0) * lightColor, 1 );
    
    vec3 lightDir4 = normalize(vec3(10, 0, 10));
    vec4 diffuse4 = vec4( max(dot(norm, lightDir4), 0) * lightColor, 1 );

    vec3 lightDir5 = normalize(lightPos5 - icFragPos);
    vec4 diffuse5 = vec4( max(dot(norm, lightDir5), 0) * lightColor, 1);

	pxColor = texture(tex, TexCoord) * ( ambient + ((diffuse1 + diffuse2 + diffuse3 + diffuse4 + diffuse5) * 0.8) );
}
