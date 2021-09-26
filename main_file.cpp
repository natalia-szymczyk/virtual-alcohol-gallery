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

std::vector<Model*> models;

glm::vec3 cameraPosition = glm::vec3(0, 1, 0);

int currentDrink;
int counter			= 0;
int drinkingStatus	= 0;
int height			= 720;
int width			= 1280;

float distortion	= 0.0f;
float speed_x		= 0; //[radiany/s]
float speed_y		= 0; //[radiany/s]
float walk_speed	= 0;
float ratio			= width / height;

using namespace std;

Model* findModel(string modelName) {
	for (auto model : models) {
		if (model->name == modelName) {
			return model;
		}
	}
}

//Funkcja obsługi kamery
glm::vec3 rotateCamera(float angle_x, float angle_y) {
	glm::vec4 direction	= glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	glm::mat4 M			= glm::mat4(1.0f);
		
	M = glm::rotate(glm::mat4(1.0f), angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));

	direction = M * direction;

	return glm::vec3(direction);
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			speed_y = 1;
		}
		if (key == GLFW_KEY_RIGHT) {
			speed_y = -1;
		}
		if (key == GLFW_KEY_PAGE_UP) {
			speed_x = -1;
		}
		if (key == GLFW_KEY_PAGE_DOWN) {
			speed_x = 1;
		}
		if (key == GLFW_KEY_UP) {
			walk_speed = 10;
		}
		if (key == GLFW_KEY_DOWN) {
			walk_speed = -10;
		}
		if (key == GLFW_KEY_P && cameraPosition.x <= -12 && cameraPosition.z >= 14) {
			currentDrink	= 7;
			counter			= counter + 1;
			drinkingStatus	= 1;
		}
		if (key == GLFW_KEY_K && cameraPosition.x <= -12 && cameraPosition.z >= 14) {
			currentDrink	= 6;
			counter			= counter + 1;
			drinkingStatus	= 1;
		}
		if (key == GLFW_KEY_W) {
			cout << cameraPosition.x << " " << cameraPosition.y << " " << cameraPosition.z << endl;
		}
		if (key == GLFW_KEY_R) {
			counter		= 0;
			distortion  = 0.0f;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) {
			speed_y = 0;
		}
		if (key == GLFW_KEY_RIGHT) {
			speed_y = 0;
		}
		if (key == GLFW_KEY_PAGE_UP) {
			speed_x = 0;
		}
		if (key == GLFW_KEY_PAGE_DOWN) {
			speed_x = 0;
		}
		if (key == GLFW_KEY_UP) {
			walk_speed = 0;
		}
		if (key == GLFW_KEY_DOWN) {
			walk_speed = 0;
		}
		if (key == GLFW_KEY_P && cameraPosition.x <= -12 && cameraPosition.z >= 14) {
			drinkingStatus = 2;
		}
		if (key == GLFW_KEY_K && cameraPosition.x <= -12 && cameraPosition.z >= 14) {
			drinkingStatus = 2;
		}
	}
}

//Procedura obsługi zmiany rozmiaru okna
void window_resize_callback(GLFWwindow* window, int width, int height) {
	if (height == 0) {
		return;
	}

	ratio = (float)width / (float)height;

	glViewport(0, 0, width, height);
}

//Procedura inicjująca modele
void initModels() {
	glm::mat4 M = glm::mat4(1.0f);

	glm::mat4 M0 = M;

	M0 = glm::scale(M0, glm::vec3(0.1, 0.1, 0.1));

	Model* floor = new Model("floor.fbx", M0, "");

	models.push_back(floor);

	glm::mat4 M1 = M;

	M1 = glm::scale(M1, glm::vec3(200, 200, 200));
	M1 = glm::translate(M1, glm::vec3(0, -0.15f, 0));

	Model* sphere = new Model("sphere.fbx", M1, "sphere");

	models.push_back(sphere);

	glm::mat4 M2 = M;

	M2 = glm::translate(M2, glm::vec3(0.0f, -20.0f, 0.0f));
	M2 = glm::scale(M2, glm::vec3(500.0f, 0.1f, 500.0f));

	Model* cube = new Model("cube.fbx", M2, "");

	models.push_back(cube);

	glm::mat4 M3 = M;

	M3 = glm::rotate(M3, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M3 = glm::scale(M3, glm::vec3(1.0f, 1.0f, 3.0f));
	M3 = glm::translate(M3, glm::vec3(50.0f, 30.0f, -7.0f));

	Model* tree = new Model("tree.fbx", M3, "");

	models.push_back(tree);

	glm::mat4 M4 = M0;

	M4 = glm::translate(M4, glm::vec3(-20, -150, 250));
	M4 = glm::rotate(M4, PI, glm::vec3(0.0f, 1.0f, 0.0f));
	M4 = glm::rotate(M4, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));

	Model* sofa = new Model("sofa.fbx", M4, "");

	models.push_back(sofa);

	glm::mat4 M5 = M0;

	M5 = glm::translate(M5, glm::vec3(-220, -50, 230));
	M5 = glm::rotate(M5, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M5 = glm::scale(M5, glm::vec3(60, 60, 100));

	Model* barrel = new Model("barrel.fbx", M5, "");

	models.push_back(barrel);

	glm::mat4 M6 = M5;

	M6 = glm::scale(M6, glm::vec3(0.02, 0.02, 0.02));
	M6 = glm::translate(M6, glm::vec3(8, -8, 1));
	M6 = glm::rotate(M6, PI / 4, glm::vec3(0.0f, 0.0f, 1.0f));
	M6 = glm::rotate(M6, -PI, glm::vec3(1.0f, 0.0f, 0.0f));

	Model* glass = new Model("glass.FBX", M6, "glass");

	models.push_back(glass);

	glm::mat4 M7 = M5;

	M7 = glm::scale(M7, glm::vec3(2, 2, 1.7));
	M7 = glm::translate(M7, glm::vec3(-0.05, -0.05, 0.02));
	M7 = glm::rotate(M7, PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M7 = glm::rotate(M7, -PI / 4, glm::vec3(0.0f, 0.0f, 1.0f));

	Model* bottle_beer = new Model("bottle_beer.fbx", M7, "bottle_beer");

	models.push_back(bottle_beer);

	glm::mat4 M8 = M5;

	M8 = glm::scale(M8, glm::vec3(0.065, 0.065, 0.065));
	M8 = glm::translate(M8, glm::vec3(1.5, 2, -0.4));
	M8 = glm::rotate(M8, -PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M8 = glm::rotate(M8, -55 * PI / 180, glm::vec3(0.0f, 0.0f, 1.0f));

	Model* bottle_wine = new Model("bottle_wine.fbx", M8, "");

	models.push_back(bottle_wine);

	glm::mat4 M9 = M0;

	M9 = glm::translate(M9, glm::vec3(190, -120, 250));
	M9 = glm::rotate(M9, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M9 = glm::scale(M9, glm::vec3(8, 8, 8));

	Model* monstera = new Model("monstera.fbx", M9, "");

	models.push_back(monstera);

	glm::mat4 M10 = M0;

	M10 = glm::translate(M10, glm::vec3(160, -150, -290));
	M10 = glm::rotate(M10, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M10 = glm::rotate(M10, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M10 = glm::scale(M10, glm::vec3(2, 2, 2));

	Model* distiller = new Model("distiller.fbx", M10, "");

	models.push_back(distiller);

	glm::mat4 M11 = M0;

	M11 = glm::translate(M11, glm::vec3(0, 90, 0));
	M11 = glm::rotate(M11, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M11 = glm::scale(M11, glm::vec3(5, 5, 12));

	Model* lamp = new Model("lamp.fbx", M11, "");

	models.push_back(lamp);

	glm::mat4 M12 = M0;

	M12 = glm::rotate(M12, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M12 = glm::rotate(M12, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M12 = glm::translate(M12, glm::vec3(-330, 22, 50));
	M12 = glm::scale(M12, glm::vec3(2, 2, 2));

	Model* painting = new Model("painting.fbx", M12, "");

	models.push_back(painting);

	glm::mat4 M13 = M0;

	M13 = glm::rotate(M13, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M13 = glm::rotate(M13, 3 * PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M13 = glm::translate(M13, glm::vec3(-330, -170, 50));
	M13 = glm::scale(M13, glm::vec3(2, 1, 2));

	Model* painting_2 = new Model("painting_2.fbx", M13, "");

	models.push_back(painting_2);

	glm::mat4 M14 = M0;

	M14 = glm::translate(M14, glm::vec3(-240, -150, 0));
	M14 = glm::rotate(M14, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M14 = glm::rotate(M14, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M14 = glm::scale(M14, glm::vec3(50, 50, 70));

	Model* shelf = new Model("shelf.fbx", M14, "");

	models.push_back(shelf);

	glm::mat4 M15 = M0;

	M15 = glm::translate(M15, glm::vec3(240, -150, 0));
	M15 = glm::rotate(M15, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M15 = glm::rotate(M15, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M15 = glm::scale(M15, glm::vec3(50, 50, 70));

	Model* shelf_2 = new Model("shelf.fbx", M15, "");

	models.push_back(shelf_2);

	std::vector<glm::mat4> M_beers = { M14, M14, M14, M14, M14, M14, M14, M14, M14 };
	float it_f = -0.42;

	for (auto& m : M_beers) {
		m = glm::scale(m, glm::vec3(2, 2, 2));
		m = glm::translate(m, glm::vec3(it_f, 0, 0.45));
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		Model* tmp = new Model("bottle_beer.fbx", m, "");

		models.push_back(tmp);

		it_f = it_f + 0.10;
	}

	std::vector<glm::mat4> M_gins = { M14, M14, M14, M14, M14, M14, M14, M14 };
	int it = -70;

	for (auto& m : M_gins) {
		m = glm::scale(m, glm::vec3(0.012, 0.012, 0.012));
		m = glm::translate(m, glm::vec3(it, 3, 43));
		m = glm::rotate(m, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
		m = glm::rotate(m, PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));

		Model* tmp = new Model("gin.fbx", m, "");

		models.push_back(tmp);

		it = it + 20;
	}

	std::vector<glm::mat4> M_wines = { M14, M14, M14, M14, M14, M14, M14 };
	it = -12;

	for (auto& m : M_wines) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 26));
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		Model* tmp = new Model("bottle_wine.fbx", m, "");

		models.push_back(tmp);

		it = it + 4;
	}

	std::vector<glm::mat4> M_wines_1 = { M15, M15, M15, M15, M15, M15, M15, M15, M15 };
	it = -12;

	for (auto& m : M_wines_1) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 26));
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		Model* tmp = new Model("bottle_wine_1.fbx", m, "");

		models.push_back(tmp);

		it = it + 3;
	}

	std::vector<glm::mat4> M_wines_2 = { M15, M15, M15, M15, M15, M15, M15, M15, M15 };
	it = -12;

	for (auto& m : M_wines_2) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 15));
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		Model* tmp = new Model("bottle_wine_2.fbx", m, "");

		models.push_back(tmp);

		it = it + 3;
	}

	std::vector<glm::mat4> M_wines_3 = { M15, M15, M15, M15, M15, M15, M15, M15, M15 };
	it = -12;

	for (auto& m : M_wines_3) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 4.5));
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		Model* tmp = new Model("bottle_wine_3.fbx", m, "");

		models.push_back(tmp);

		it = it + 3;
	}
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_resize_callback);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	initShaders();
	initModels();
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float distortion, float angle_x, float angle_y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sp->use();

	glm::mat4 P = glm::perspective(
		glm::radians(60.0f),
		ratio,
		0.1f,
		500.0f
	);
	glm::mat4 V = glm::lookAt(
		cameraPosition,
		cameraPosition + rotateCamera(angle_x, angle_y),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));

	for (auto model : models) {
		model->draw(glm::value_ptr(V), glm::value_ptr(P));
	}

	glfwSwapBuffers(window);
}

//Funkcja obsługi kolizji
int tryToWalk(glm::vec3 step) {
	if (cameraPosition.x + step.x <= 18 && cameraPosition.x + step.x >= -21 && cameraPosition.z + step.z <= 16.7 && cameraPosition.z + step.z >= -22) {
		return 1;
	}
	else if (cameraPosition.x + step.x <= 5.5 && cameraPosition.x + step.x >= -23.5 && cameraPosition.z + step.z <= -6 && cameraPosition.z + step.z >= -29) {
		return 1;
	}
	else if (cameraPosition.x + step.x <= 23.5 && cameraPosition.x + step.x >= 18 && cameraPosition.z + step.z <= 16.7 && cameraPosition.z + step.z >= 5.8) {
		return 1;
	}
	else if (cameraPosition.x + step.x <= 23.5 && cameraPosition.x + step.x >= 18 && cameraPosition.z + step.z <= -6.7 && cameraPosition.z + step.z >= -22) {
		return 1;
	}
	else {
		return 0;
	}
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

	float it_K = 0.1f, step_K = 1.0f, end_K = 20.0f;
	float it_P = 0.1f, step_P = 1.0f, end_P = 0.4f;

	float angle		= 0;
	float angle_x	= 0;
	float angle_y	= 0;

	glm::vec3 step;

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window)) {
		distortion = distortion + counter;

		angle_x = angle_x + speed_x * glfwGetTime();
		angle_y = angle_y + speed_y * glfwGetTime();

		step = (float)(walk_speed * glfwGetTime()) * rotateCamera(angle_x, angle_y);

		if (tryToWalk(step)) {
			cameraPosition = cameraPosition + step;
		}

		cameraPosition.y = 1.0f;

		cameraPosition.x = cameraPosition.x + min(sin(distortion / 300) * counter / 8, 1.0f);
		cameraPosition.z = cameraPosition.z + min(cos(distortion / 400) * counter / 9, 1.0f);

		glfwSetTime(0);
		drawScene(window, distortion, angle_x, angle_y);

		cameraPosition.x = cameraPosition.x - min(sin(distortion / 300) * counter / 8, 1.0f);
		cameraPosition.z = cameraPosition.z - min(cos(distortion / 400) * counter / 9, 1.0f);

		findModel("sphere")->M = glm::rotate(findModel("sphere")->M, PI / 6000, glm::vec3(0.0f, 1.0f, 0.0f));

		if (currentDrink == 7 && drinkingStatus == 1) {
			if (it_P < end_P) {
				findModel("bottle_beer")->M = glm::rotate(findModel("bottle_beer")->M, -step_P / 30, glm::vec3(1, 0, 0));
				findModel("bottle_beer")->M = glm::translate(findModel("bottle_beer")->M, glm::vec3(0, 0, step_P / 100));

				it_P = it_P + step_P / 100;
			}
			else {
				drinkingStatus = 0;
			}
		}
		else if (currentDrink == 7 && drinkingStatus == 2) {
			if (it_P > 0.1f) {
				findModel("bottle_beer")->M = glm::translate(findModel("bottle_beer")->M, glm::vec3(0, 0, -step_P / 100));
				findModel("bottle_beer")->M = glm::rotate(findModel("bottle_beer")->M, step_P / 30, glm::vec3(1, 0, 0));

				it_P = it_P - step_P / 100;
			}
			else {
				drinkingStatus = 0;
			}
		}
		else if (currentDrink == 6 && drinkingStatus == 1) {
			if (it_K < end_K) {
				findModel("glass")->M = glm::rotate(findModel("glass")->M, -step_K / 20, glm::vec3(1, 0, 0));
				findModel("glass")->M = glm::translate(findModel("glass")->M, glm::vec3(0, 0, step_K));

				it_K = it_K + step_K;
			}
			else {
				drinkingStatus = 0;
			}
		}
		else if (currentDrink == 6 && drinkingStatus == 2) {
			if (it_K > 0.1f) {
				findModel("glass")->M = glm::translate(findModel("glass")->M, glm::vec3(0, 0, -step_K));
				findModel("glass")->M = glm::rotate(findModel("glass")->M, step_K / 20, glm::vec3(1, 0, 0));

				it_K = it_K - step_K;
			}
			else {
				drinkingStatus = 0;
			}
		}
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
