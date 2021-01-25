#include "program.h"

#include "engine/main/rendering/program/shader/shader.h"

#include "application/common/debug/debug.h"

using namespace		engine;

					program::program(const path &vertex_source, const path &fragment_source)
{
	value = glCreateProgram();

	shader			vertex_shader(shader::vertex, vertex_source);
	shader			fragment_shader(shader::fragment, fragment_source);
	GLint			success;

	glAttachShader(value, vertex_shader.value);
	glAttachShader(value, fragment_shader.value);
	glLinkProgram(value);

	glGetProgramiv(value, GL_LINK_STATUS, &success);

	if (not success)
	{
		log_error();
		debug::raise_error("[engine::program] Compilation error");
	}
}

					program::~program()
{
	glDeleteProgram(value);
}

void				program::bind(bool state)
{
	glUseProgram(state ? value : 0);
}

void				program::log_error() const
{
	GLchar		log[1024];

	glGetProgramInfoLog(value, 1024, nullptr, log);
	cout << "DEBUG // GLSL OUTPUT" << endl << endl;
	cout << log << endl << endl;
}