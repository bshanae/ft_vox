//#include "program.h"
//
//#include "engine/program/shader.h"
//
//using namespace		engine::program;
//
//					program::program(const path &vertex_source, const path &fragment_source)
//{
//	object = glCreateProgram();
//
//	shader			vertex_shader(shader::type::vertex, vertex_source);
//	shader			fragment_shader(shader::type::fragment, fragment_source);
//
//	glAttachShader(object, vertex_shader.object);
//	glAttachShader(object, fragment_shader.object);
//	glLinkProgram(object);
//
//	GLint			success;
//
//	glGetProgramiv(object, GL_LINK_STATUS, &success);
//
//#if DEBUG
//	GLchar			log[1024];
//
//	glGetProgramiv(object, GL_LINK_STATUS, &success);
//	if (not success)
//	{
//		glGetProgramInfoLog(object, 1024, nullptr, log);
//		cout << "DEBUG // GLSL OUTPUT" << endl << endl;
//		cout << log << endl << endl;
//		error::raise(error::id::program_compilation_error);
//	}
//#else
//	if (not success)
//		error::raise(error::id::program_compilation_error);
//#endif
//}
//
//					program::~program()
//{
//	glDeleteProgram(object);
//}
