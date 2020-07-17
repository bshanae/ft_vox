#include "shader.h"

#include <sstream>
#include <fstream>

							shader::shader(type type, const std::filesystem::path &source)
{
	auto					write_file_to_stream = [](std::stringstream &stream, const std::filesystem::path &path)
	{
		std::ifstream		file;

		file.open(path);
		if (not file.is_open());
//			error::raise(error::id::shader_file_error);

		stream << file.rdbuf();

		file.close();
	};

	std::stringstream		stream;

	write_file_to_stream(stream, source);

	const std::string		string = stream.str();
	const char				*raw_string = string.data();

	value = glCreateShader(static_cast<GLuint>(type));
	glShaderSource(value, 1, &raw_string, nullptr);
	glCompileShader(value);

	GLint					success;

	glGetShaderiv(value, GL_COMPILE_STATUS, &success);

#if DEBUG
	GLchar					log[1024];

	if (not success)
	{
		glGetShaderInfoLog(value, 1024, nullptr, log);
		cout << "DEBUG // GLSL SHADER" << endl << endl;
		cout << raw_string << endl << endl;
		cout << "DEBUG // GLSL OUTPUT" << endl << endl;
		cout << log << endl << endl;
		error::raise(error::id::shader_compilation_error);
	}
#else
	if (not success)
	{
//		error::raise(error::id::shader_compilation_error);
		std::terminate();
	}
#endif
}
shader::~shader()
{
	glDeleteShader(value);
}