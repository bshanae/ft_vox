#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class				model
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

	void			bind(bool state) const;

	GLuint			get_number_of_indices() const;

private:

	vector<GLuint>	buffers;

	GLuint			vao = 0;
	GLuint			number_of_vbos = 0;
	GLuint			number_of_indices = 0;

	void			add_vbo(int dimension, const vector<GLfloat> &data);
	void			add_ebo(const  vector<GLuint> &indices);
};