//
// Created by Oles Gedz on 16/07/2020.
//

#ifndef FT_VOX_PROJECT_DEBUG_DEBUG_GL_H_
#define FT_VOX_PROJECT_DEBUG_DEBUG_GL_H_
#include "Libraries/glad/include/glad/glad.h"
#include "Libraries/glfw/include/GLFW/glfw3.h"
#include "Libraries/glm/glm/glm.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char *file, int line);

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message, void *userParam);


#endif //FT_VOX_PROJECT_DEBUG_DEBUG_GL_H_
