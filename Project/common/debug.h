#pragma once

#include "common/opengl.h"

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