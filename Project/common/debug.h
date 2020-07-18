#pragma once

#include "libraries/glad/include/glad/glad.h"
#include "libraries/glfw/include/GLFW/glfw3.h"
#include "libraries/glm/glm/glm.hpp"

#define VOX_DEBUG		1

#define glCheckError()	glCheckError_(__FILE__, __LINE__)

GLenum					glCheckError_(const char *file, int line);

void APIENTRY			glDebugOutput(
							GLenum source,
							GLenum type,
							GLuint id,
							GLenum severity,
							GLsizei length,
							const GLchar *message,
							void *userParam);