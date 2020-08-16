#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/property.h"
#include "application/object_template.h"

class									model
{
public:

	property<read_only, int, model>		number_of_indices;

	property<read_write, vec3, model>	scaling;
	property<read_write, vec3, model>	translation;
	property<read_write, vec3, model>	rotation;
	property<read_only, mat4, model>	transformation;

										model();
										~model();

	void								add_vbo(int dimension, const vector<GLfloat> &data);
	void								add_ebo(const vector<GLuint> &indices);

	void								bind(bool state) const;

private :

	GLuint								vao = 0;
	vector<GLuint>						vbos;

	void 								recalculate_transformation();
};