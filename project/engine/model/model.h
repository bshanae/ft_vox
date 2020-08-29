#pragma once

#include "common/opengl.h"
#include "common/glm.h"
#include "common/aliases.h"
#include "common/property.h"

class										model
{
public:

	property<read_only, int, model>			number_of_indices;

	property<read_write, vec3, model>		scaling;
	property<read_write, vec3, model>		translation;
	property<read_write, vec3, model>		rotation;
	property<read_only, mat4, model>		transformation;

	enum class								draw_mode
	{
		triangles,
		lines
	};

	explicit								model(draw_mode mode = draw_mode::triangles);
											~model();

	void									add_vbo(int dimension, const vector<GLfloat> &data);
	void									add_ebo(const vector<GLuint> &indices);

	void									bind(bool state) const;

	void									render() const;

private :

	const draw_mode							draw_mode;

	GLuint									vao = 0;
	vector<GLuint>							vbos;

	void 									recalculate_transformation();
};