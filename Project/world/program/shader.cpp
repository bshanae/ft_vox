#include "shader.h"

#include "common/debug.h"

						shader::shader(type type, const path &source)
{
	auto				write_file_to_stream = [](stringstream &stream, const path &path)
	{
		ifstream	file;

		file.open(path);
		assert(file.is_open() and "Can't read shader file");

		stream << file.rdbuf();

		file.close();
	};

	stringstream	stream;

	write_file_to_stream(stream, source);

	const string	string = stream.str();
	const char			*raw_string = string.data();

	value = glCreateShader(static_cast<GLuint>(type));
	glShaderSource(value, 1, &raw_string, nullptr);
	glCompileShader(value);

	GLint				success;

	glGetShaderiv(value, GL_COMPILE_STATUS, &success);

#if VOX_DEBUG
	GLchar				log[1024];

	if (not success)
	{
		glGetShaderInfoLog(value, 1024, nullptr, log);
		cout << "DEBUG // GLSL SHADER" << endl << endl;
		cout << raw_string << endl << endl;
		cout << "DEBUG // GLSL OUTPUT" << endl << endl;
		cout << log << endl << endl;

	}
#else
	assert(success and "Can't compile shader");
#endif
}

						shader::~shader()
{
	glDeleteShader(value);
}