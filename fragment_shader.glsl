#version 330

#define NUMBER_OF_LIGHTS_INSIDE  1
#define NUMBER_OF_LIGHTS_OUTSIDE 5

struct Light {
	vec4 color;
	vec4 direction;
	vec4 position;
	float diffuseStrength;
	float specularStrength;
};

uniform sampler2D textureMap;
uniform Light lights_inside[NUMBER_OF_LIGHTS_INSIDE] = {
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 10.0f, 0.0f, 1.0f),
		1.0f,
		1.0f
	}
};
uniform Light lights_outside[NUMBER_OF_LIGHTS_OUTSIDE] = {
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 0.0f, 1.0f, 0.0f),
		vec4(100.0f, 100.0f, 100.0f, 1.0f),
		1.0f,
		0.5f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(1.0f, 0.0f, -1.0f, 0.0f),
		vec4(100.0f, 100.0f, -100.0f, 1.0f),
		1.0f,
		0.5f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(-1.0f, 0.0f, 1.0f, 0.0f),
		vec4(-100.0f, 100.0f, 100.0f, 1.0f),
		1.0f,
		0.5f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(-1.0f, 0.0f, -1.0f, 0.0f),
		vec4(-100.0f, 100.0f, -100.0f, 1.0f),
		1.0f,
		0.5f
	},
	{
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.0f, -1.0f, 0.0f, 0.0f),
		vec4(0.0f, 100.0f, 0.0f, 1.0f),
		0.5f,
		0.5f
	}
};

in vec4 fView;
in vec4 fVertex;
in vec4 fNormal;
in vec2 fTexCoord;

out vec4 pixelColor;

void main(void) {
	vec4 normal		= normalize(fNormal);
	vec4 diffuse	= vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 specular	= vec4(0.0f, 0.0f, 0.0f, 0.0f);	

	for (int i = 0; i < NUMBER_OF_LIGHTS_INSIDE; i++) {
		vec4  lightDirection	= normalize(lights_inside[i].position - fVertex);
		vec4  lightColor		= normalize(lights_inside[i].color);
		float diffuseStrength	= lights_inside[i].diffuseStrength;
		float specularStrength	= lights_inside[i].specularStrength;

		diffuse		= diffuse + clamp(dot(normal, lightDirection), 0.0f, 1.0f) * lightColor * diffuseStrength;
		specular	= specular + pow(max(dot(fView, reflect(-lightDirection, normal)), 0.0f), 32.0f) * lightColor * specularStrength;
	}

	for (int i = 0; i < NUMBER_OF_LIGHTS_OUTSIDE; i++) {
		vec4  lightDirection	= normalize(lights_outside[i].direction);
		vec4  lightColor		= normalize(lights_outside[i].color);
		float diffuseStrength	= lights_outside[i].diffuseStrength;
		float specularStrength	= lights_outside[i].specularStrength;

		diffuse		= diffuse + clamp(dot(normal, lightDirection), 0.0f, 1.0f) * lightColor * diffuseStrength;
		specular	= specular + pow(max(dot(fView, reflect(-lightDirection, normal)), 0.0f), 32.0f) * lightColor * specularStrength;
	}

	pixelColor = texture(textureMap, fTexCoord) * (diffuse + specular);
}
