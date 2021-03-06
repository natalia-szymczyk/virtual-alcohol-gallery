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

#include <Model.h>

std::unordered_map<std::string, GLuint> Model::tex_global;
std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> Model::mesh_vec_global;
std::unordered_map<std::string, std::vector<std::vector<glm::vec4>>> Model::mesh_norm_global;
std::unordered_map<std::string, std::vector<std::vector<glm::vec2>>> Model::mesh_tex_global;
std::unordered_map<std::string, std::vector<std::vector<unsigned int>>> Model::mesh_indices_global;

Model::Model(std::string filename, glm::mat4 ModelMatrix, std::string ModelName) {
	M = ModelMatrix;
	name = ModelName;
	auto it = mesh_vec_global.find(filename);

	if (it != mesh_vec_global.end()) {
		mesh_vec = &(it->second);
		mesh_norm = &(mesh_norm_global.find(filename)->second);
		mesh_tex = &(mesh_tex_global.find(filename)->second);
		mesh_indices = &(mesh_indices_global.find(filename)->second);

		std::string str = filename.substr(0, filename.find("."));

		loadTextures(str, mesh_vec->size(), "texture.ini", &tex);

		return;
	}

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	std::cout << importer.GetErrorString() << std::endl;

	auto mesh_vec_ptr = &(mesh_vec_global.insert(std::make_pair(filename, std::vector<std::vector<glm::vec4>>())).first->second);
	auto mesh_norm_ptr = &(mesh_norm_global.insert(std::make_pair(filename, std::vector<std::vector<glm::vec4>>())).first->second);
	auto mesh_tex_ptr = &(mesh_tex_global.insert(std::make_pair(filename, std::vector<std::vector<glm::vec2>>())).first->second);
	auto mesh_indices_ptr = &(mesh_indices_global.insert(std::make_pair(filename, std::vector<std::vector<unsigned int>>())).first->second);

	for (int k = 0; k < scene->mNumMeshes; k++) {
		mesh_vec_ptr->push_back(std::vector < glm::vec4>());
		mesh_norm_ptr->push_back(std::vector < glm::vec4>());
		mesh_tex_ptr->push_back(std::vector < glm::vec2>());
		mesh_indices_ptr->push_back(std::vector<unsigned int>());

		auto mesh = scene->mMeshes[k];

		for (int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D vertex = mesh->mVertices[i];
			(*mesh_vec_ptr)[k].push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

			vertex = mesh->mNormals[i];
			(*mesh_norm_ptr)[k].push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 0));

			vertex = mesh->mTextureCoords[0][i];
			(*mesh_tex_ptr)[k].push_back(glm::vec2(vertex.x, vertex.y));
		}

		for (int l = 0; l < mesh->mNumFaces; l++) {
			aiFace& face = mesh->mFaces[l];

			for (int j = 0; j < face.mNumIndices; j++) {
				(*mesh_indices_ptr)[k].push_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		aiString mat_str;

		material->GetTexture(aiTextureType_SPECULAR, 0, &mat_str);
	}

	std::string str = filename.substr(0, filename.find("."));

	loadTextures(str, scene->mNumMeshes, "texture.ini", &tex);

	mesh_vec = mesh_vec_ptr;
	mesh_norm = mesh_norm_ptr;
	mesh_tex = mesh_tex_ptr;
	mesh_indices = mesh_indices_ptr;
}

void Model::draw(glm::mat4 P, glm::mat4 V) {
	for (int i = 0; i < mesh_vec->size(); i++) {
		sp->use();

		glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
		glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, (*mesh_vec)[i].data());

		glEnableVertexAttribArray(sp->a("normal"));
		glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, (*mesh_norm)[i].data());

		glEnableVertexAttribArray(sp->a("texCoord"));
		glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, (*mesh_tex)[i].data());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex[i]);
		glUniform1i(sp->u("tex"), 0);

		glDrawElements(GL_TRIANGLES, (*mesh_indices)[i].size(), GL_UNSIGNED_INT, (*mesh_indices)[i].data());

		glDisableVertexAttribArray(sp->a("vertex"));
		glDisableVertexAttribArray(sp->a("normal"));
		glDisableVertexAttribArray(sp->a("texCoord"));
	}
}

GLuint Model::readTexture(const char* filename) {
	GLuint tex;

	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;		// Alokuj wektor do wczytania obrazka
	unsigned width, height;					// Zmienne do których wczytamy wymiary obrazka

	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex);					// Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex);		// Uaktywnij uchwyt

	//Wczytaj obrazek do pamięci GPU skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void Model::loadTextures(std::string filename, int maxIndex, std::string ini_file, std::vector<GLuint>* vec) {
	std::vector<std::pair<int, std::string>> file_names, file_names_final;
	std::string filename1 = ".\\textures\\";

	filename1 += filename;
	filename1 += "\\";
	filename1 += ini_file;

	std::ifstream input(filename1);

	if (!input.is_open()) {
		for (int i = 0; i < maxIndex; i++) {
			vec->push_back(-1);
		}

		return;
	}

	std::string str1, str2, var;
	int index;

	while (!input.eof()) {
		std::getline(input, var);

		var = var.substr(0, var.find("#"));

		int pos = var.find("=");

		if (pos == std::string::npos) {
			continue;
		}

		str1 = var.substr(0, pos);
		str2 = var.substr(pos + 1, std::string::npos);

		while (str2[0] == ' ') {
			str2 = str2.substr(1, std::string::npos);
		}

		if (str2 == "\n" || str2.size() == 0) {
			continue;
		}

		index = std::atoi(str1.c_str());
		file_names.push_back(std::pair<int, std::string>{index, str2});

	}

	input.close();

	std::sort(file_names.begin(), file_names.end());

	int j = 0;

	for (int i = 0; i < maxIndex; i++) {
		if (j != file_names.size() && file_names[j].first == i) {
			std::string tex_file = "textures/" + filename + "/" + file_names[j].second;
			j++;

			auto it1 = tex_global.find(tex_file);

			if (it1 == tex_global.end()) {
				auto it = tex_global.insert(std::make_pair(tex_file.c_str(), readTexture((tex_file).c_str())));

				vec->push_back(it.first->second);
			}
			else {
				vec->push_back(it1->second);
			}
		}
		else {
			vec->push_back(-1);
		}
	}
}
