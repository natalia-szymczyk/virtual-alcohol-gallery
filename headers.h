#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <vector>

#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>