#include "shader.h"

#include "application/common/debug/debug.h"

using namespace			engine;

						shader::shader(type type, const path &source)
{
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
		debug::raise_error("[engine::shader] Compilation error");
	}
}

						shader::~shader()
{
	glDeleteShader(value);
}

void					shader::write_file_to_stream(stringstream &stream, const path &path)
{
	ifstream			file;

	file.open(path);
	debug::check_critical(file.is_open(), "[engine::shader] Can't read file at '%s'", path.c_str());

	stream << file.rdbuf();
	file.close();
}

void					shader::log_error(const string &shader_string) const
{
	GLchar				log[1024];

	glGetShaderInfoLog(value, 1024, nullptr, log);

	debug::log("DEBUG // GLSL SHADER\n");
	debug::log(shader_string);

	debug::log("DEBUG // GLSL OUTPUT\n");
	debug::log(log);
}