#pragma once

#include "application/common/imports/opengl.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace				engine
{
	class 				model;
}

class					engine::model
{
public:

	enum				draw_mode
	{
		triangles,
		lines
	};

	explicit			model(draw_mode mode = triangles);
						~model();

	int					get_number_of_indices() const;
	vec3				get_scaling() const;
	vec3				get_translation() const;
	vec3				get_rotation() const;
	mat4				get_transformation() const;

	void				set_scaling(const vec3 &value);
	void				set_translation(const vec3 &value);
	void				set_rotation(const vec3 &value);

	void				add_vbo(int dimension, const vector<GLfloat> &data);
	void				add_ebo(const vector<GLuint> &indices);

	void				bind(bool state) const;

	void				render() const;

private :

	const draw_mode		draw_mode;

	GLuint				vao = 0;
	vector<GLuint>		vbos;
	int					number_of_indices;
	vec3				scaling;
	vec3				translation;
	vec3				rotation;
	mat4				transformation;

	void 				recalculate_transformation();
};