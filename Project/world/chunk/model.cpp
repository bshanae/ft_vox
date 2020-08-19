#include "model.h"

					model::model()
{
	glGenVertexArrays(1, &vao);

	translation.setter = [this](const vec3 &value)
	{
		translation.value = value;
		recalculate_transformation();
	};
	translation.prohibit_direct_access();

	rotation.setter = [this](const vec3 &value)
	{
		rotation.value = value;
		recalculate_transformation();
	};
	rotation.prohibit_direct_access();

	scaling.setter = [this](const vec3 &value)
	{
		scaling.value = value;
		recalculate_transformation();
	};
	scaling.prohibit_direct_access();

	transformation.prohibit_direct_access();

	translation = vec3(0.f);
	rotation = vec3(0.f);
	scaling = vec3(1.f);
	transformation = mat4(1.f);

	number_of_indices = 0;
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

	assert(number_of_indices == 0 and "Can't add EBO more than once");

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(indices[0]),
		indices.data(),
		GL_STATIC_DRAW);
	vbos.push_back(ebo);

	number_of_indices = indices.size();
}

void 				model::recalculate_transformation()
{
	vec3 			rotation;

	rotation.x = radians(this->rotation.value.x);
	rotation.y = radians(this->rotation.value.y);
	rotation.z = radians(this->rotation.value.z);

	transformation = mat4(1.f);
	transformation.value *= translate(translation.value);
	transformation.value *= eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
	transformation.value *= scale(scaling.value);
}