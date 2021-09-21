/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.
Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.
Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include "headers.h"
#include "wine.h"
std::vector<Model*> models;


Wine wine;

float speed_x = 0; //[radiany/s]
float speed_y = 0; //[radiany/s]
float walk_speed = 0;

glm::vec3 pos = glm::vec3(0, 1, 0);

int height = 720;
int width = 1280;

using namespace std;

glm::vec3 calcDir(float kat_x, float kat_y) {
	glm::vec4 dir = glm::vec4(0, 0, 1, 0);
	glm::mat4 M = glm::rotate(glm::mat4(1.0f), kat_y, glm::vec3(0, 1, 0));
	M = glm::rotate(M, kat_x, glm::vec3(1, 0, 0));
	dir = M * dir;
	return glm::vec3(dir);
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_y = 1;
		if (key == GLFW_KEY_RIGHT) speed_y = -1;
		if (key == GLFW_KEY_PAGE_UP) speed_x = -1;
		if (key == GLFW_KEY_PAGE_DOWN) speed_x = 1;
		if (key == GLFW_KEY_UP) walk_speed = 10;
		if (key == GLFW_KEY_DOWN) walk_speed = -10;

	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_PAGE_UP) speed_x = 0;
		if (key == GLFW_KEY_PAGE_DOWN) speed_x = 0;
		if (key == GLFW_KEY_UP) walk_speed = 0;
		if (key == GLFW_KEY_DOWN) walk_speed = 0;
	}
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glfwSetKeyCallback(window, key_callback);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową

	glm::mat4 M1 = M;
	M1 = glm::scale(M1, glm::vec3(0.1, 0.1, 0.1));

	models.push_back(new Model("floor.fbx", M1)); //git

	glm::mat4 M2 = M1;
	M2 = glm::translate(M2, glm::vec3(-20, -150, 250));
	M2 = glm::rotate(M2, PI, glm::vec3(0.0f, 1.0f, 0.0f));
	M2 = glm::rotate(M2, -PI/2, glm::vec3(1.0f, 0.0f, 0.0f));

	models.push_back(new Model("sofa.fbx", M2)); //git

	glm::mat4 M3 = M1;
	M3 = glm::translate(M3, glm::vec3(-170, -90, 100));
	M3 = glm::rotate(M3, PI/2, glm::vec3(1.0f, 0.0f, 0.0f));
	M3 = glm::scale(M3, glm::vec3(60, 60, 60));

	models.push_back(new Model("barrel.fbx", M3)); //git

	glm::mat4 M4 = M1;
	M4 = glm::translate(M4, glm::vec3(-240, -150, 0));
	M4 = glm::rotate(M4, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M4 = glm::rotate(M4, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M4 = glm::scale(M4, glm::vec3(50, 50, 70));

	models.push_back(new Model("shelf.fbx", M4)); //git

	glm::mat4 M5 = M1;
	M5 = glm::translate(M5, glm::vec3(190, -120, 250));
	M5 = glm::rotate(M5, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M5 = glm::scale(M5, glm::vec3(8, 8, 8));

	models.push_back(new Model("monstera.fbx", M5)); //git

	glm::mat4 M6 = M1;
	M6 = glm::translate(M6, glm::vec3(140, -150, -250));
	M6 = glm::rotate(M6, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M6 = glm::rotate(M6, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M6 = glm::scale(M6, glm::vec3(2, 2, 2));

	models.push_back(new Model("distiller.fbx", M6)); //git

	glm::mat4 M7 = M1;
	M7 = glm::translate(M7, glm::vec3(0, 90, 0));
	M7 = glm::rotate(M7, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M7 = glm::scale(M7, glm::vec3(5, 5, 12));

	models.push_back(new Model("lamp.fbx", M7)); //git

	glm::mat4 M8 = M;
	M8 = glm::scale(M8, glm::vec3(200, 200, 200));
	M8 = glm::rotate(M8, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));

	models.push_back(new Model("sphere.fbx", M8));

	glm::mat4 M9 = M;
	M9 = glm::translate(M9, glm::vec3(0.0f, -20.0f, 0.0f));
	M9 = glm::scale(M9, glm::vec3(1000.0f, 0.1f, 1000.0f));

	models.push_back(new Model("cube.fbx", M9));

	std::vector<glm::mat4> M_wines = { M4, M4, M4, M4, M4, M4, M4};
	int it = -12;

	for (auto& m : M_wines) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 26)); //12
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		it += 4;
		models.push_back(new Model("bottle_wine.fbx", m));
	}

	std::vector<glm::mat4> M_beers = {M4, M4, M4, M4, M4, M4, M4, M4, M4};
	float it_f = -0.42;

	for (auto& m : M_beers) {
		m = glm::scale(m, glm::vec3(2, 2, 2));
		m = glm::translate(m, glm::vec3(it_f, 0, 0.45));
		m = glm::rotate(m, PI , glm::vec3(0.0f, 0.0f, 1.0f));

		it_f += 0.10;
		models.push_back(new Model("bottle_beer.fbx", m));
	}

	std::vector<glm::mat4> M_gins = {M4, M4, M4, M4, M4, M4, M4, M4};
	it = -70;

	for (auto& m : M_gins) {
		m = glm::scale(m, glm::vec3(0.012, 0.012, 0.012));
		m = glm::translate(m, glm::vec3(it, 3, 43)); //-70 i 70
		m = glm::rotate(m, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
		m = glm::rotate(m, PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));

		it += 20;
		models.push_back(new Model("gin.fbx", m));
	}



	glm::mat4 M10 = M1;
	M10 = glm::rotate(M10, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M10 = glm::rotate(M10, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M10 = glm::translate(M10, glm::vec3(-330, 22, 50));
	M10 = glm::scale(M10, glm::vec3(2, 2, 2));

	models.push_back(new Model("painting.fbx", M10));

	glm::mat4 M11 = M1;
	M11 = glm::rotate(M11, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M11 = glm::rotate(M11, 3 * PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M11 = glm::translate(M11, glm::vec3(-330, -170, 50));
	M11 = glm::scale(M11, glm::vec3(2, 1, 2));

	models.push_back(new Model("painting_2.fbx", M11));


	//glm::mat4 M10 = M1;
	////M10 = glm::rotate(M10, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	////M10 = glm::scale(M10, glm::vec3(0.10, 0.10, 0.10));

	//models.push_back(new Model("glass_bottle.fbx", M10));




	//wine.readTexture("./textures/barrel_2/black.png");
	//wine.loadModel("./barrel_2.fbx");
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	glDeleteTextures(1, &wine.texture);
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float kat_x, float kat_y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(pos, pos + calcDir(kat_x, kat_y), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 5000.0f); //Wylicz macierz rzutowania

	spLambertTextured->use();

	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));

	glm::mat4 M = glm::mat4(1.0f);

	//M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	//M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));

	//wine.drawModel(M);


	for (auto model : models) {
		model->draw(glm::value_ptr(V), glm::value_ptr(P));
	}

	glfwSwapBuffers(window);
}

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, "Alcohol Gallery", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);

	float angle = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float kat_x = 0;
	float kat_y = 0;
	glfwSetTime(0); //Wyzeruj licznik czasu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		kat_x += speed_x * glfwGetTime();
		kat_y += speed_y * glfwGetTime();
		pos += (float)(walk_speed * glfwGetTime()) * calcDir(kat_x, kat_y);
		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window, kat_x, kat_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}