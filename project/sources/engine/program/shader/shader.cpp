#include "shader.h"

#include "common/debug/logger/logger.h"

using namespace			debug;
using namespace			engine;

						shader::shader(type type, const path &source)
{
	auto				write_file_to_stream = [](stringstream &stream, const path &path)
	{
		ifstream		file;

		file.open(path);
		assert(file.is_open() and "Can't read shader file");

		stream << file.rdbuf();

		file.close();
	};

	auto 				log_error = [this](const string &shader_string)
	{
		GLchar			log[1024];

		glGetShaderInfoLog(value, 1024, nullptr, log);

		logger::log(logger::engine, "DEBUG // GLSL SHADER\n");
		logger::log(logger::engine, shader_string);

		logger::log(logger::engine, "DEBUG // GLSL OUTPUT\n");
		logger::log(logger::engine, log);
	};

	stringstream		stream;
	string				string = stream.str();
	char				*raw_string = string.data();
	GLint				success;

	write_file_to_stream(stream, source);

	string = stream.str();
	raw_string = string.data();

	value = glCreateShader(static_cast<GLuint>(type));
	glShaderSource(value, 1, &raw_string, nullptr);
	glCompileShader(value);

	glGetShaderiv(value, GL_COMPILE_STATUS, &success);

	if (not success)
	{
		log_error(raw_string);
		assert(success and "Can't compile shader");
	}
}

						shader::~shader()
{
	glDeleteShader(value);
}