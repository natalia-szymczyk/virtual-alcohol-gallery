#version 330

#define NUMBER_OF_LIGHTS 5

struct Light {
	vec4 color;
	vec4 direction;
	vec4 position;
	float diffuseStrength;
	float specularStrength;
};

uniform sampler2D textureMap;
uniform Light lights[NUMBER_OF_LIGHTS] = {
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(-10.0f, 0.0f, -10.0f, 0.0f),
		vec4(100.0f, 100.0f, 100.0f, 1.0f),
		1.0f,
		1.0f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(-10.0f, 0.0f, 10.0f, 0.0f),
		vec4(100.0f, 100.0f, -100.0f, 1.0f),
		1.0f,
		1.0f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(10.0f, 0.0f, -10.0f, 0.0f),
		vec4(-100.0f, 100.0f, 100.0f, 1.0f),
		1.0f,
		1.0f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(10.0f, 0.0f, 10.0f, 0.0f),
		vec4(-100.0f, 100.0f, -100.0f, 1.0f),
		1.0f,
		1.0f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.0f, 1.0f, 0.0f, 0.0f),
		vec4(0.0f, 10.0f, 0.0f, 1.0f),
		1.0f,
		1.0f
	}
};

in vec4 fViewDir;
in vec4 fVertex;
in vec4 fNormal;
in vec2 fTexCoord;

out vec4 pixelColor;

void main(void) {
	vec4 nfNormal	= normalize(fNormal);
	vec4 diffuse	= vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 specular	= vec4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < NUMBER_OF_LIGHTS; i++) {
		vec4  lightDirection	= normalize(lights[i].direction);
		vec4  lightColor		= normalize(lights[i].color);
		float diffuseStrength	= lights[i].diffuseStrength;
		float specularStrength	= lights[i].specularStrength;

		diffuse		= diffuse + max(dot(nfNormal, lightDirection), 0.0f) * lightColor * diffuseStrength;
		specular	= specular + pow(max(dot(fViewDir, reflect(-lightDirection, nfNormal)), 0.0f), 32.0f) * lightColor * specularStrength;
	}

	pixelColor = texture(textureMap, fTexCoord) * (diffuse + specular);
}
