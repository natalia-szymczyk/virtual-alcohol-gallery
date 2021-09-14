#ifndef wine_h
#define wine_h

#include "headers.h"

class Wine {
public:	
	GLuint texture;

	// wektory modelu
	std::vector<glm::vec4> vertexes;
	std::vector<glm::vec4> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;

	glm::mat4 position;

	//Procedura wczytuj¹ca teksture
	void readTexture(const char* filename);

	// zaladowanie modelu
	void loadModel(std::string plik);

	// rysowanie modelu
	void drawModel(glm::mat4 M);

};

#endif