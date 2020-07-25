#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class					model
{
public:
						model(
							const vector<GLfloat> &vertices,
							const vector<GLfloat> &texture_coordinates,
							const vector<GLuint> &indices);
						model(
							const vector<GLfloat> &vertices,
							const vector<GLuint> &indices);

						model() = default;
						~model();

	void				bind(bool state) const;

	[[nodiscard]] int	get_number_of_indices() const;

	[[nodiscard]] vec3	get_scaling() const;
	[[nodiscard]] vec3	get_translation() const;
	[[nodiscard]] vec3	get_rotation() const;
	[[nodiscard]] mat4	get_transformation() const;

	void				set_scaling(float value);
	void				set_scaling(const vec3 &value);
	void				set_translation(const vec3 &value);
	void				set_rotation(const vec3 &value);

private:

	GLuint				vao = 0;
	vector<GLuint>		vbos;

	int					number_of_indices = 0;

	vec3 				translation = vec3(0.f);
	vec3 				rotation = vec3(0.f);
	vec3 				scaling = vec3(1.f);

	mat4 				transformation = mat4(1.f);

	void				add_vbo(int dimension, const vector<GLfloat> &data);
	void				add_ebo(const  vector<GLuint> &indices);

	void 				recalculate_transformation();
};