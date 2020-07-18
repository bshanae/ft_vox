#include "debug.h"

#include "common/aliases.h"

void APIENTRY		glDebugOutput(
						GLenum source,
						GLenum type,
						GLuint id,
						GLenum severity,
						GLsizei length,
						const GLchar *message,
						const void *userParam)
{
//						Ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	cout << "---------------" << endl;
	cout << "debug message (" << id << "): " << message << endl;

	switch (source)
	{
		case GL_DEBUG_SOURCE_API:
			cout << "Source: API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			cout << "Source: Window System";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			cout << "Source: Shader Compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			cout << "Source: Third Party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			cout << "Source: Application";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			cout << "Source: Other";
			break;
	}
	cout << endl;

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:
			cout << "Type: Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			cout << "Type: Deprecated Behaviour";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			cout << "Type: Undefined Behaviour";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			cout << "Type: Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			cout << "Type: Performance";
			break;
		case GL_DEBUG_TYPE_MARKER:
			cout << "Type: Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			cout << "Type: Push Group";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			cout << "Type: Pop Group";
			break;
		case GL_DEBUG_TYPE_OTHER:
			cout << "Type: Other";
			break;
	}
	cout << endl;

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			cout << "Severity: high";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			cout << "Severity: medium";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			cout << "Severity: low";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			cout << "Severity: notification";
			break;
	}
	cout << endl;
	cout << endl;
}

GLenum				glCheckError_(const char *file, int line)
{
	GLenum			error_code;

	while ((error_code = glGetError()) != GL_NO_ERROR)
	{
		string		error;

		switch (error_code)
		{
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "INVALID_FRAMEBUFFER_OPERATION";
				break;
		}

		cout << error << " | " << file << " (" << line << ")" << endl;
	}
	return error_code;
}