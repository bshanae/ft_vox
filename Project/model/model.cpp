#include "model.h"

					model::model(
						const vector<GLfloat> &vertices,
			 			const vector<GLfloat> &texture_coordinates,
			 			const vector<GLuint> &indices) :
						number_of_indices(indices.size())
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	add_vbo(3, vertices);
	add_vbo(2, texture_coordinates);
	add_ebo(indices);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

					model::model(
						const vector<GLfloat> &vertices,
	  					const vector<GLuint> &indices) :
						number_of_indices(indices.size())
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	add_vbo(3, vertices);
	add_ebo(indices);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

					model::~model()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(buffers.size(), buffers.data());
}

void				model::bind(bool state) const
{
	glBindVertexArray(state ? vao : 0);
}

void				model::add_vbo(int dimension, const vector<GLfloat> &data)
{
	GLuint			vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		data.size() * sizeof(data[0]),
		data.data(),
		GL_STATIC_DRAW);
	glVertexAttribPointer(
		number_of_vbos,
		dimension,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid *)nullptr);
	glEnableVertexAttribArray(number_of_vbos++);
	buffers.push_back(vbo);
}

void				model::add_ebo(const vector<GLuint> &indices)
{
	GLuint			ebo;

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(indices[0]),
		indices.data(),
		GL_STATIC_DRAW);
	buffers.push_back(ebo);
}

GLuint				model::get_number_of_indices() const
{
	return (number_of_indices);
}