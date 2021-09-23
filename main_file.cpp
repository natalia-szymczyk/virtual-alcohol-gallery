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

int counter = 0;
int canDrink = 0;
int currentDrink;

float speed_x = 0; //[radiany/s]
float speed_y = 0; //[radiany/s]
float walk_speed = 0;

glm::vec3 pos = glm::vec3(0, 1, 0);

int height = 720;
int width = 1280;
int tmp = 1;

float aspect = width / height;

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
		if (key == GLFW_KEY_LEFT)			speed_y = 1;
		if (key == GLFW_KEY_RIGHT)			speed_y = -1;
		if (key == GLFW_KEY_PAGE_UP)		speed_x = -1;
		if (key == GLFW_KEY_PAGE_DOWN)		speed_x = 1;
		if (key == GLFW_KEY_UP)				walk_speed = 10;
		if (key == GLFW_KEY_DOWN)			walk_speed = -10;
		if (key == GLFW_KEY_P && pos.x <= -12 && pos.z >= 14) {
			currentDrink = 7;
			counter = counter + 1;
			canDrink = 1;
		}
		if (key == GLFW_KEY_K && pos.x <= -12 && pos.z >= 14) {
			currentDrink = 6;
			counter = counter + 1;
			canDrink = 1;
		}
		if (key == GLFW_KEY_W) {
			cout << endl << tmp << ": " << pos.x << " " << pos.y << " " << pos.z << endl;
			cout << endl << "sin: " << pos.x / pos.z << endl;
			tmp++;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT)			speed_y = 0;
		if (key == GLFW_KEY_RIGHT)			speed_y = 0;
		if (key == GLFW_KEY_PAGE_UP)		speed_x = 0;
		if (key == GLFW_KEY_PAGE_DOWN)		speed_x = 0;
		if (key == GLFW_KEY_UP)				walk_speed = 0;
		if (key == GLFW_KEY_DOWN)			walk_speed = 0;
		if (key == GLFW_KEY_P && pos.x <= -12 && pos.z >= 14) canDrink = 2;
		if (key == GLFW_KEY_K && pos.x <= -12 && pos.z >= 14) canDrink = 2;
	}
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glfwSetKeyCallback(window, key_callback);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 M = glm::mat4(1.0f);

	glm::mat4 M0 = M;
	M0 = glm::scale(M0, glm::vec3(0.1, 0.1, 0.1));

	models.push_back(new Model("floor.fbx", M0));

	glm::mat4 M1 = M;
	M1 = glm::scale(M1, glm::vec3(200, 200, 200));
	M1 = glm::translate(M1, glm::vec3(0, -0.15f, 0));

	models.push_back(new Model("sphere.fbx", M1));

	glm::mat4 M2 = M;
	M2 = glm::translate(M2, glm::vec3(0.0f, -20.0f, 0.0f));
	M2 = glm::scale(M2, glm::vec3(500.0f, 0.1f, 500.0f));

	models.push_back(new Model("cube.fbx", M2));

	glm::mat4 M3 = M;
	M3 = glm::rotate(M3, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M3 = glm::scale(M3, glm::vec3(1.0f, 1.0f, 3.0f));
	M3 = glm::translate(M3, glm::vec3(50.0f, 30.0f, -7.0f));

	models.push_back(new Model("tree.fbx", M3));

	glm::mat4 M4 = M0;
	M4 = glm::translate(M4, glm::vec3(-20, -150, 250));
	M4 = glm::rotate(M4, PI, glm::vec3(0.0f, 1.0f, 0.0f));
	M4 = glm::rotate(M4, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));

	models.push_back(new Model("sofa.fbx", M4));

	glm::mat4 M5 = M0;
	M5 = glm::translate(M5, glm::vec3(-220, -50, 230));
	M5 = glm::rotate(M5, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M5 = glm::scale(M5, glm::vec3(60, 60, 100));

	models.push_back(new Model("barrel.fbx", M5));

	glm::mat4 M6 = M5;
	M6 = glm::scale(M6, glm::vec3(0.02, 0.02, 0.02));
	M6 = glm::translate(M6, glm::vec3(8, -8, 1));
	M6 = glm::rotate(M6, PI / 4, glm::vec3(0.0f, 0.0f, 1.0f));
	M6 = glm::rotate(M6, -PI, glm::vec3(1.0f, 0.0f, 0.0f));

	models.push_back(new Model("glass.FBX", M6));

	glm::mat4 M7 = M5;
	M7 = glm::scale(M7, glm::vec3(2, 2, 1.7));
	M7 = glm::translate(M7, glm::vec3(-0.05, -0.05, 0.02));
	M7 = glm::rotate(M7, PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M7 = glm::rotate(M7, -PI / 4, glm::vec3(0.0f, 0.0f, 1.0f));

	models.push_back(new Model("bottle_beer.fbx", M7));

	glm::mat4 M8 = M5;
	M8 = glm::scale(M8, glm::vec3(0.065, 0.065, 0.065));
	M8 = glm::translate(M8, glm::vec3(1.5, 2, -0.4));
	M8 = glm::rotate(M8, -PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M8 = glm::rotate(M8, -55 * PI / 180, glm::vec3(0.0f, 0.0f, 1.0f));

	models.push_back(new Model("bottle_wine.fbx", M8));

	glm::mat4 M9 = M0;
	M9 = glm::translate(M9, glm::vec3(190, -120, 250));
	M9 = glm::rotate(M9, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M9 = glm::scale(M9, glm::vec3(8, 8, 8));

	models.push_back(new Model("monstera.fbx", M9));

	glm::mat4 M10 = M0;
	M10 = glm::translate(M10, glm::vec3(160, -150, -290));
	M10 = glm::rotate(M10, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M10 = glm::rotate(M10, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M10 = glm::scale(M10, glm::vec3(2, 2, 2));

	models.push_back(new Model("distiller.fbx", M10));

	glm::mat4 M11 = M0;
	M11 = glm::translate(M11, glm::vec3(0, 90, 0));
	M11 = glm::rotate(M11, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M11 = glm::scale(M11, glm::vec3(5, 5, 12));

	models.push_back(new Model("lamp.fbx", M11));

	glm::mat4 M12 = M0;
	M12 = glm::rotate(M12, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M12 = glm::rotate(M12, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M12 = glm::translate(M12, glm::vec3(-330, 22, 50));
	M12 = glm::scale(M12, glm::vec3(2, 2, 2));

	models.push_back(new Model("painting.fbx", M12));

	glm::mat4 M13 = M0;
	M13 = glm::rotate(M13, 3 * PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M13 = glm::rotate(M13, 3 * PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M13 = glm::translate(M13, glm::vec3(-330, -170, 50));
	M13 = glm::scale(M13, glm::vec3(2, 1, 2));

	models.push_back(new Model("painting_2.fbx", M13));

	glm::mat4 M14 = M0;
	M14 = glm::translate(M14, glm::vec3(-240, -150, 0));
	M14 = glm::rotate(M14, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M14 = glm::rotate(M14, PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M14 = glm::scale(M14, glm::vec3(50, 50, 70));

	models.push_back(new Model("shelf.fbx", M14));

	glm::mat4 M15 = M0;
	M15 = glm::translate(M15, glm::vec3(240, -150, 0));
	M15 = glm::rotate(M15, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M15 = glm::rotate(M15, -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));
	M15 = glm::scale(M15, glm::vec3(50, 50, 70));

	models.push_back(new Model("shelf.fbx", M15));

	std::vector<glm::mat4> M_beers = { M14, M14, M14, M14, M14, M14, M14, M14, M14 };
	float it_f = -0.42;

	for (auto& m : M_beers) {
		m = glm::scale(m, glm::vec3(2, 2, 2));
		m = glm::translate(m, glm::vec3(it_f, 0, 0.45));
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		it_f += 0.10;
		models.push_back(new Model("bottle_beer.fbx", m));
	}

	std::vector<glm::mat4> M_gins = { M14, M14, M14, M14, M14, M14, M14, M14 };
	int it = -70;

	for (auto& m : M_gins) {
		m = glm::scale(m, glm::vec3(0.012, 0.012, 0.012));
		m = glm::translate(m, glm::vec3(it, 3, 43)); //-70 i 70
		m = glm::rotate(m, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
		m = glm::rotate(m, PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));

		it += 20;
		models.push_back(new Model("gin.fbx", m));
	}

	std::vector<glm::mat4> M_wines = { M14, M14, M14, M14, M14, M14, M14 };
	it = -12;

	for (auto& m : M_wines) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 26)); //12
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		it += 4;
		models.push_back(new Model("bottle_wine.fbx", m));
	}

	std::vector<glm::mat4> M_wines_1 = { M15, M15, M15, M15, M15, M15, M15, M15, M15 };
	it = -12;

	for (auto& m : M_wines_1) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 26)); //12
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		it += 3;
		models.push_back(new Model("bottle_wine_1.fbx", m));
	}

	std::vector<glm::mat4> M_wines_2 = { M15, M15, M15, M15, M15, M15, M15, M15, M15 };
	it = -12;

	for (auto& m : M_wines_2) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 15)); //12
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		it += 3;
		models.push_back(new Model("bottle_wine_2.fbx", m));
	}

	std::vector<glm::mat4> M_wines_3 = { M15, M15, M15, M15, M15, M15, M15, M15, M15 };
	it = -12;

	for (auto& m : M_wines_3) {
		m = glm::scale(m, glm::vec3(0.065, 0.065, 0.065));
		m = glm::translate(m, glm::vec3(it, 0, 4.5)); //12
		m = glm::rotate(m, PI, glm::vec3(0.0f, 0.0f, 1.0f));

		it += 3;
		models.push_back(new Model("bottle_wine_3.fbx", m));
	}
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float distortion, float kat_x, float kat_y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(pos, pos + calcDir(kat_x, kat_y), glm::vec3(0.0f, 1.0f, 0.0f));	// Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 500.0f);					// Wylicz macierz rzutowania

	spLambertTextured->use();

	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));

	for (auto model : models) {
		model->draw(glm::value_ptr(V), glm::value_ptr(P));
	}

	glfwSwapBuffers(window);
}

int tryToWalk(glm::vec3 step) {
	if (pos.x + step.x <= 18 && pos.x + step.x >= -21 && pos.z + step.z <= 16.7 && pos.z + step.z >= -22) {
		return 1;
	}
	else if (pos.x + step.x <= 5.5 && pos.x + step.x >= -25 && pos.z + step.z <= -6 && pos.z + step.z >= -29) {
		return 1;
	}
	else if (pos.x + step.x <= 23.5 && pos.x + step.x >= 18 && pos.z + step.z <= 16.7 && pos.z + step.z >= 5.8) {
		return 1;
	}
	else if (pos.x + step.x <= 23.5 && pos.x + step.x >= 18 && pos.z + step.z <= -6.7 && pos.z + step.z >= -22) {
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

	float distortion = 0.1f;

	float angle = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float kat_x = 0;
	float kat_y = 0;

	glm::vec3 tmp_step;

	glfwSetTime(0);

	while (!glfwWindowShouldClose(window)) {
		distortion = distortion + counter;

		kat_x += speed_x * glfwGetTime();
		kat_y += speed_y * glfwGetTime();
		tmp_step = (float)(walk_speed * glfwGetTime()) * calcDir(kat_x, kat_y);
		if (tryToWalk(tmp_step))	pos += tmp_step;

		if (canDrink == 0) {
			pos.x += sin(distortion / 300) * counter / 8;
			pos.z += cos(distortion / 400) * counter / 9;
		}

		glfwSetTime(0);
		drawScene(window, distortion, kat_x, kat_y);

		if (canDrink == 0) {
			pos.x -= sin(distortion / 300) * counter / 8;
			pos.z -= cos(distortion / 400) * counter / 9;
		}

		models[1]->M = glm::rotate(models[1]->M, -PI / 6000, glm::vec3(0.0f, 1.0f, 0.0f));

		if (currentDrink == 7 && canDrink == 1) {
			if (it_P < end_P) {
				models[currentDrink]->M = glm::rotate(models[currentDrink]->M, -step_P / 30, glm::vec3(1, 0, 0));
				models[currentDrink]->M = glm::translate(models[currentDrink]->M, glm::vec3(0, 0, step_P / 100));

				it_P = it_P + step_P / 100;
			}
			else {
				canDrink = 0;
			}
		}
		else if (currentDrink == 7 && canDrink == 2) {
			if (it_P > 0.1f) {
				models[currentDrink]->M = glm::translate(models[currentDrink]->M, glm::vec3(0, 0, -step_P / 100));
				models[currentDrink]->M = glm::rotate(models[currentDrink]->M, step_P / 30, glm::vec3(1, 0, 0));

				it_P = it_P - step_P / 100;
			}
			else {
				canDrink = 0;
			}
		}
		else if (currentDrink == 6 && canDrink == 1) {
			if (it_K < end_K) {
				models[currentDrink]->M = glm::rotate(models[currentDrink]->M, -step_K / 20, glm::vec3(1, 0, 0));
				models[currentDrink]->M = glm::translate(models[currentDrink]->M, glm::vec3(0, 0, step_K));

				it_K = it_K + step_K;
			}
			else {
				canDrink = 0;
			}
		}
		else if (currentDrink == 6 && canDrink == 2) {
			if (it_K > 0.1f) {
				models[currentDrink]->M = glm::translate(models[currentDrink]->M, glm::vec3(0, 0, -step_K));
				models[currentDrink]->M = glm::rotate(models[currentDrink]->M, step_K / 20, glm::vec3(1, 0, 0));

				it_K = it_K - step_K;
			}
			else {
				canDrink = 0;
			}
		}
		glfwPollEvents();
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}