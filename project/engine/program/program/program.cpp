#include "program.h"

#include "engine/program/shader/shader.h"

using namespace		engine;

					program::program(const path &vertex_source, const path &fragment_source)
{
	value = glCreateProgram();

	shader			vertex_shader(shader::type::vertex, vertex_source);
	shader			fragment_shader(shader::type::fragment, fragment_source);

	glAttachShader(value, vertex_shader.value);
	glAttachShader(value, fragment_shader.value);
	glLinkProgram(value);

	GLint			success;

	glGetProgramiv(value, GL_LINK_STATUS, &success);

#if VOX_DEBUG_ENGINE
	GLchar			log[1024];

	glGetProgramiv(value, GL_LINK_STATUS, &success);
	if (not success)
	{
		glGetProgramInfoLog(value, 1024, nullptr, log);
		cout << "DEBUG // GLSL OUTPUT" << endl << endl;
		cout << log << endl << endl;
		assert(false and "Program compilation error");
	}
#else
	assert(success and "Program compilation error");
#endif
}

					program::~program()
{
	glDeleteProgram(value);
}
