//Niniejszy program jest wolnym oprogramowaniem; możesz go
//rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
//Licencji Publicznej GNU, wydanej przez Fundację Wolnego
//Oprogramowania - według wersji 2 tej Licencji lub(według twojego
//wyboru) którejś z późniejszych wersji.
//
//Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
//użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
//gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
//ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
//Powszechnej Licencji Publicznej GNU.
//
//Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
//Powszechnej Licencji Publicznej GNU(GNU General Public License);
//jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
//Place, Fifth Floor, Boston, MA  02110 - 1301  USA

#pragma once

#include "headers.h"

class Model {
private:
	//wektor współrzędnych wierzchołków
	std::vector<std::vector<glm::vec4>>* mesh_vec;
	std::vector<std::vector<glm::vec4>>* mesh_norm;
	std::vector<std::vector<glm::vec2>>* mesh_tex;
	std::vector<std::vector<unsigned int>>* mesh_indices;

	std::vector<GLuint> tex;

public:
	glm::mat4 M;
	std::string name;
	static std::unordered_map<std::string, GLuint> tex_global;
	static std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> mesh_vec_global;
	static std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> mesh_norm_global;
	static std::unordered_map<std::string, std::vector<std::vector<glm::vec2>>> mesh_tex_global;
	static std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> mesh_indices_global;

	Model(std::string filename, glm::mat4 ModelMatrix, std::string ModelName);
	GLuint readTexture(const char* filename);
	void draw(glm::mat4 P, glm::mat4 V);
	void loadTextures(std::string filename, int maxIndex, std::string ini_file, std::vector<GLuint>* vec);
};
