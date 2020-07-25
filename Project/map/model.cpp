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
	glDeleteBuffers(vbos.size(), vbos.data());
}

void				model::bind(bool state) const
{
	glBindVertexArray(state ? vao : 0);
}

int					model::get_number_of_indices() const
{
	return (number_of_indices);
}

vec3				model::get_scaling() const
{
	return (scaling);
}

vec3				model::get_translation() const
{
	return (translation);
}

vec3				model::get_rotation() const
{
	return (rotation);
}

mat4				model::get_transformation() const
{
	return (transformation);
}

void				model::set_translation(const vec3 &value)
{
	translation = value;
	recalculate_transformation();
}

void				model::set_rotation(const vec3 &value)
{
	rotation = value;
	recalculate_transformation();
}

void				model::set_scaling(float value)
{
	scaling = vec3(value);
	recalculate_transformation();
}

void				model::set_scaling(const vec3 &value)
{
	scaling = value;
	recalculate_transformation();
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
		vbos.size(),
		dimension,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid *)nullptr);
	glEnableVertexAttribArray(vbos.size());
	vbos.push_back(vbo);
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
	vbos.push_back(ebo);
}

void 				model::recalculate_transformation()
{
	vec3 			rotation;

	rotation.x = radians(this->rotation.x);
	rotation.y = radians(this->rotation.y);
	rotation.z = radians(this->rotation.z);

	transformation = mat4(1.f);
	transformation *= translate(translation);
	transformation *= eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
	transformation *= scale(scaling);
}