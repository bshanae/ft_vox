#pragma once

#include "epsilon.h"

vector<GLfloat>		front_texture_coordinates =
{
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};

vector<GLfloat>		back_texture_coordinates =
{
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
};

vector<GLfloat>		top_texture_coordinates =
{
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
};

vector<GLfloat>		bottom_texture_coordinates =
{
	0.f + epsilon, 0.f + epsilon,
	0.f + epsilon, 1.f - epsilon,
	1.f - epsilon, 1.f - epsilon,
	1.f - epsilon, 0.f + epsilon,
};

vector<GLfloat>		right_texture_coordinates =
{
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
};

vector<GLfloat>		left_texture_coordinates =
{
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon
};

vector<GLfloat>		first_diagonal_texture_coordinates =
{
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};

vector<GLfloat>		second_diagonal_texture_coordinates =
{
	1.f - epsilon, 1.f - epsilon,
	0.f + epsilon, 1.f - epsilon,
	0.f + epsilon, 0.f + epsilon,
	1.f - epsilon, 0.f + epsilon,
};