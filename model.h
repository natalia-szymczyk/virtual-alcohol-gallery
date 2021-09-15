///*
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
//*/
//
//#ifndef MODEL_H
//#define MODEL_H
//
//
//#include <GL/glew.h>
//#include <vector>
//#include <glm/glm.hpp>
//#include <GLFW/glfw3.h>
//#include "constants.h"
//
//namespace Models {
//
//	class Model {
//		public:
//			int vertexCount;
//			float *vertices;
//			float *normals;
//			float *vertexNormals;
//			float *texCoords;
//			float *colors;
//
//			virtual void drawSolid(bool smooth)=0;
//			virtual void drawWire(bool smooth=false);
//	};
//}
//
//#endif

#pragma once
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <iostream>
#include <shaderprogram.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <GL/glew.h>
#include <utility>
#include <algorithm>
#include "lodepng.h"

#include <fstream>
#include <unordered_map>

//#include "btBulletDynamicsCommon.h"
//#include "btBulletCollisionCommon.h"

//extern ShaderProgram* sp_color;
//extern ShaderProgram* sp_textured;
//extern ShaderProgram* sp_normals;
//extern ShaderProgram* sp_normals_file;
//extern ShaderProgram* sp_spec_file;
//extern ShaderProgram* sp_spec;
//extern ShaderProgram* sp_tex_norm_height;

//extern glm::vec4 light_source1;
//extern glm::vec4 light_source2;

class Model {
private:
	//wektor współrzędnych wierzchołków
	std::vector<std::vector<glm::vec4>>* mesh_vec;
	std::vector<std::vector<glm::vec4>>* mesh_norm;
	std::vector<std::vector<glm::vec2>>* mesh_tex;
	std::vector<std::vector<unsigned int>>* mesh_indices;
	//std::vector<std::vector<glm::vec4>>* mesh_tangent;
	//std::vector<std::vector<glm::vec4>>* mesh_bitangent;

	std::vector<GLuint> tex;
	std::vector<GLuint> specular;
	std::vector<GLuint> norm;
	std::vector<GLuint> height;

	//to do
	//parallel mapping
	//height
	glm::mat4 M;
	//btRigidBody* body;

public:
	static std::unordered_map<std::string, GLuint> tex_global;
	static std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> mesh_vec_global;
	static std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> mesh_norm_global;
	static std::unordered_map<std::string, std::vector<std::vector<glm::vec2>>> mesh_tex_global;
	static std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> mesh_indices_global;
	//static std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> mesh_tangent_global;
	//static std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> mesh_bitangent_global;





	Model(std::string filename, glm::mat4 ModelMatrix);

	void draw(glm::f32* V, glm::f32* P);
	GLuint readTexture(const char* filename);
	void loadTextures(std::string filename, int maxIndex, std::string ini_file, std::vector<GLuint>* vec);

	//void generateRigitBodies(btDiscreteDynamicsWorld* dynamicsWorld);
};
